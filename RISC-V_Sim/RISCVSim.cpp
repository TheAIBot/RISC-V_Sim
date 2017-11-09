#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include "Processor.h"
#include "TestEncodeDecode.h"
#include "TestInstructions.h"
#include "ReadTest.h"

std::string sdf(Processor& processor, const uint32_t* Registers)
{
	std::string registerSum = "\nExpected : Actual\n";
	for(uint32_t i = 0; i < 32; i++)
	{
		//don't show stack pointer register
		//as it isn't checked
		if (i == static_cast<uint32_t>(Regs::sp))
		{
			registerSum += "sp 0 : 0";
		}
		else
		{
			registerSum += RegisterName(i);
			registerSum += " ";
			registerSum += std::to_string(Registers[i]);
			registerSum += " : ";
			registerSum += std::to_string(processor.GetRegister(static_cast<Regs>(i)));
		}

		registerSum += "\n";
	}

	return registerSum;
}

void testFile(std::string filePath)
{
	uint32_t instructionCount = 95;
	//const uint32_t* rawInstructions = ReadInstructions(filePath, &instructionCount);
	const uint32_t rawInstructions[95] = 
	{
		0xfd010113,
		0x02112623,
		0x02812423,
		0x02912223,
		0x03010413,
		0x00010513,
		0x00050493,
		0x06400513,
		0xfea42423,
		0xfe842503,
		0xfff50893,
		0xff142223,
		0x00050893,
		0x00088313,
		0x00000393,
		0x01b35893,
		0x00539713,
		0x00e8e733,
		0x00531693,
		0x00050713,
		0x00070593,
		0x00000613,
		0x01b5d713,
		0x00561813,
		0x01076833,
		0x00559793,
		0x00050793,
		0x00279793,
		0x00378793,
		0x00f78793,
		0x0047d793,
		0x00479793,
		0x40f10133,
		0x00010793,
		0x00378793,
		0x0027d793,
		0x00279793,
		0xfef42023,
		0xfe042623,
		0x0940006f,
		0xfd010113,
		0x02812623,
		0x03010413,
		0xfca42e23,
		0xfcb42c23,
		0xfe042623,
		0xfe042423,
		0x0300006f,
		0xfe842783,
		0x00279793,
		0xfdc42703,
		0x00f707b3,
		0x0007a783,
		0xfec42703,
		0x00f707b3,
		0xfef42623,
		0xfe842783,
		0x00178793,
		0xfef42423,
		0xfe842703,
		0xfd842783,
		0xfcf746e3,
		0xfec42783,
		0x00078513,
		0x02c12403,
		0x03010113,
		0x00008067,
		0xfe042703,
		0xfec42783,
		0x00279793,
		0x00f707b3,
		0xfec42703,
		0x00e7a023,
		0xfec42783,
		0x00178793,
		0xfef42623,
		0xfec42703,
		0xfe842783,
		0xfcf74ae3,
		0xfe042783,
		0xfe842583,
		0x00078513,
		0x00000317,
		0xf58300e7,
		0xfca42e23,
		0x00a00513,
		0x00000073,
		0x00048113,
		0x00000013,
		0xfd040113,
		0x02c12083,
		0x02812403,
		0x02412483,
		0x03010113,
		0x00008067
	};
	const uint32_t* registers = ReadRegisters(filePath);

	Processor processor;
	processor.SetDebugMode(false);
	processor.Run(rawInstructions, instructionCount);
	//processor.PrintRegisters();
	//processor.PrintInstructions(rawInstructions, instructionCount);

	if (!processor.CompareRegisters(registers))
	{
		//processor.PrintRegisters();
		std::cout << sdf(processor, registers);
		std::cout << "FUCKING FAILED" << std::endl;
	}
	else
	{
		std::cout << "SUCCESS" << std::endl;
	}

	//delete[] rawInstructions;
	delete[] registers;
}

int main()
{	
	TestAllEncodeDecode();
	TestAllInstructions();
	try
	{
		
		//testFile("tests/task1/addlarge");
		//testFile("tests/task1/addneg");
		//testFile("tests/task1/addpos");
		//testFile("tests/task1/shift");

		//testFile("tests/task2/branchcnt");
		//testFile("tests/task2/branchmany");
		
		testFile("tests/task3/loop");
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		return -1;
	}
	
	std::cin.get();
    return 0;
}

