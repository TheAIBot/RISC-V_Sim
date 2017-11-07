#include "RISCV_Program.h"
#include <stdexcept>
#include <fstream>
#include "InstructionEncode.h"
#include "InstructionDecode.h"
#include "Processor.h"
#include "ReadTest.h"


RISCV_Program::RISCV_Program()
{
    for(uint32_t i = 0; i < 32; i++)
    {
        Registers[i] = 0;
    }
}
void RISCV_Program::SetRegister(Regs reg, uint32_t value)
{
    MultiInstruction mInstruction = Create_li(reg, value);
    AddInstruction(mInstruction);
    ExpectRegisterValue(reg, value);
}

void RISCV_Program::ExpectRegisterValue(Regs reg, uint32_t expected)
{
    Registers[static_cast<uint32_t>(reg)] = expected;
}

void RISCV_Program::AddInstruction(uint32_t rawInstruction)
{
    Instructions.push_back(rawInstruction);
}
void RISCV_Program::AddInstruction(MultiInstruction mInstruction)
{
    if (mInstruction.instruction1 != 0)
    {
        AddInstruction(mInstruction.instruction1);
    }
    if (mInstruction.instruction2 != 0)
    {
        AddInstruction(mInstruction.instruction2);
    }
}

void RISCV_Program::EndProgram()
{
	SetRegister(Regs::a0, 10);
	ExpectRegisterValue(Regs::a0, 10);
	AddInstruction(Create_ecall());
}

static void WriteFile(std::string filepath, const char* toWrite, uint32_t size)
{
    std::ofstream file(filepath.c_str(), std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("Failed to create file: " + filepath);
	}
    file.write(toWrite, size);
    file.close(); 
}

void RISCV_Program::WrongProgramResult(Processor& processor, std::string filepath, bool fromFile)
{
	std::string registerSum = "";
	for(uint32_t i = 0; i < 32; i++)
	{
		//don't show stack pointer register
		//as it isn't checked
		if (i == static_cast<uint32_t>(Regs::sp))
		{
			registerSum += "0 : 0";
		}
		else
		{
			registerSum += std::to_string(processor.GetRegister(static_cast<Regs>(i)));
			registerSum += " : ";
			registerSum += std::to_string(Registers[i]);
		}

		registerSum += "\n";
	}
	if (!fromFile)
	{
		throw std::runtime_error("Incorrect program result for " + filepath + ".\nExpected : Actual\n" + registerSum);
	}
	else
	{
		throw std::runtime_error("Incorrect program result from loaded program: " + filepath + ".\nExpected : Actual\n" + registerSum);
	}

}

void RISCV_Program::SaveAndTest(std::string filepath)
{
    std::string binFile      = filepath + ".bin";
    std::string registerFile = filepath + ".res";
    std::string assemblyFile = filepath + ".s";

    WriteFile(binFile     , reinterpret_cast<char*>(&Instructions[0]), sizeof(uint32_t) * Instructions.size());
    WriteFile(registerFile, reinterpret_cast<char*>(&Registers[0])   , sizeof(uint32_t) * 32);

    std::string programAsText = GetProgramAsString(&Instructions[0], Instructions.size());
    WriteFile(assemblyFile, programAsText.c_str(), programAsText.length());

    Processor processor;
    processor.Run(&Instructions[0], Instructions.size());
    if (!processor.CompareRegisters(Registers))
    {
		WrongProgramResult(processor, filepath, false);
    }

	//now load program from the file we just wrote
	//and verify that the result is the same
	uint32_t instructionCount;
	const uint32_t* rawInstructions = ReadInstructions(filepath, &instructionCount);
	const uint32_t* registers = ReadRegisters(filepath);

	processor.Reset();
	processor.Run(rawInstructions, instructionCount);
	//verify what registers and Registers are the same
	//and that the program gave the correct result
	if (!processor.CompareRegisters(registers) && 
		!processor.CompareRegisters(Registers))
	{
		WrongProgramResult(processor, filepath, true);
	}

	delete[] rawInstructions;
	delete[] registers;
}

RISCV_Program::~RISCV_Program()
{
}
