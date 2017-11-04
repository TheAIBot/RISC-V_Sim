#include "Processor.h"
#include <iostream>
#include <string>
#include <iomanip>


Processor::Processor()
{
	memory = new uint8_t[Processor::MEMORY_SIZE];
}

void Processor::Run(uint32_t* rawInstructions, uint64_t instructionCount)
{
	Instruction* instructions = DecodeInstructions(rawInstructions, instructionCount);

	//set stack pointer
	registers[2].dword = Processor::MEMORY_SIZE;

	while (true)
	{
		const uint64_t instructionIndex = pc / 4;
		if (instructionIndex >= instructionCount)
		{
			throw new std::runtime_error("Index out of bounds.\nTried to access instruction: " + std::to_string(instructionIndex));
		}

		const Instruction instruction = instructions[pc / 4];

		bool stopProgram = false;
		RunInstruction(instruction, &stopProgram);

		if (debugEnabled)
		{
			PrintRegisters();
			std::cin.get();
		}


		if (stopProgram)
		{
			break;
		}
	}

	PrintRegisters();
}

void Processor::EnvironmentCall(bool* stopProgram)
{
	if (registers[10].dword == 10)
	{
		*stopProgram = true;
	}
}

void Processor::RunInstruction(Instruction instruction, bool* stopProgram)
{
	int64_t x;
	switch (instruction.type)
	{
		case lb:
			registers[instruction.rd].dword = static_cast<int64_t>(static_cast<int8_t>(GetByteFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate))));
			pc += 4;
			break;
		case lh:
			registers[instruction.rd].dword = static_cast<int64_t>(static_cast<int16_t>(GetHalfWordFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate))));
			pc += 4;
			break;
		case lw:
			registers[instruction.rd].dword = static_cast<int64_t>(static_cast<int32_t>(GetWordFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate))));
			pc += 4;
			break;
		case ld:
			registers[instruction.rd].dword = static_cast<int64_t>(GetDoubleWordFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate)));
			pc += 4;
			break;
		case lbu:
			registers[instruction.rd].udword = static_cast<uint64_t>(GetByteFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate)));
			pc += 4;
			break;
		case lhu:
			registers[instruction.rd].udword = static_cast<uint64_t>(GetHalfWordFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate)));
			pc += 4;
			break;
		case lwu:
			registers[instruction.rd].udword = static_cast<uint64_t>(GetWordFromMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate)));
			pc += 4;
			break;
		case fence:
		case fence_i:
			throw new std::runtime_error("Instruction not implemented yet.");
		case addi:
			x = static_cast<int64_t>(instruction.immediate);
			registers[instruction.rd].dword = registers[instruction.rs1].dword + x;
			//registers[instruction.rd].dword = registers[instruction.rs1].dword + static_cast<int64_t>(static_cast<int32_t>(instruction.immediate));
			pc += 4;
			break;
		case slli:
			registers[instruction.rd].dword = registers[instruction.rs1].dword << static_cast<int64_t>(instruction.immediate);
			pc += 4;
			break;
		case slti:
			registers[instruction.rd].dword = (registers[instruction.rs1].dword < static_cast<int64_t>(instruction.immediate)) ? 1 : 0;
			pc += 4;
			break;
		case sltiu:
			registers[instruction.rd].dword = (registers[instruction.rs1].udword < static_cast<uint64_t>(instruction.immediate)) ? 1 : 0;
			pc += 4;
			break;
		case xori:
			registers[instruction.rd].dword = registers[instruction.rs1].dword ^ static_cast<int64_t>(instruction.immediate);
			pc += 4;
			break;
		case srli:
			registers[instruction.rd].udword = registers[instruction.rs1].udword >> static_cast<uint64_t>(instruction.immediate);
			pc += 4;
			break;
		case srai:
			registers[instruction.rd].dword = registers[instruction.rs1].dword >> static_cast<int64_t>(instruction.immediate);
			pc += 4;
			break;
		case ori:
			registers[instruction.rd].dword = registers[instruction.rs1].dword | static_cast<int64_t>(instruction.immediate);
			pc += 4;
			break;
		case andi:
			registers[instruction.rd].dword = registers[instruction.rs1].dword & static_cast<int64_t>(instruction.immediate);
			pc += 4;
			break;
		case auipc:
			registers[instruction.rd].udword = pc + static_cast<uint64_t>(instruction.immediate);
			pc += 4;
			break;
		case addiw:
			registers[instruction.rd].word = registers[instruction.rs1].word + static_cast<int32_t>(instruction.immediate);
			pc += 4;
			break;
		case slliw:
			registers[instruction.rd].word = registers[instruction.rs1].word << static_cast<int32_t>(instruction.immediate);
			pc += 4;
			break;
		case srliw:
			registers[instruction.rd].uword = registers[instruction.rs1].uword >> instruction.immediate;
			pc += 4;
			break;
		case sraiw:
			registers[instruction.rd].word = registers[instruction.rs1].word >> static_cast<int32_t>(instruction.immediate);
			pc += 4;
			break;
		case sb:
			StoreByteInMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate), registers[instruction.rs2].byte);
			pc += 4;
			break;
		case sh:
			StoreHalfWordInMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate), registers[instruction.rs2].half);
			pc += 4;
			break;
		case sw:
			StoreWordInMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate), registers[instruction.rs2].word);
			pc += 4;
			break;
		case sd:
			StoreDoubleWordInMemory(registers[instruction.rs1].dword + static_cast<int64_t>(instruction.immediate), registers[instruction.rs2].dword);
			pc += 4;
			break;
		case add:
			registers[instruction.rd].dword = registers[instruction.rs1].dword + registers[instruction.rs2].dword;
			pc += 4;
			break;
		case sub:
			registers[instruction.rd].dword = registers[instruction.rs1].dword - registers[instruction.rs2].dword;
			pc += 4;
			break;
		case sll:
			registers[instruction.rd].dword = registers[instruction.rs1].dword << registers[instruction.rs2].dword;
			pc += 4;
			break;
		case slt:
			registers[instruction.rd].dword = (registers[instruction.rs1].dword < registers[instruction.rs2].dword) ? 1 : 0;
			pc += 4;
			break;
		case sltu:
			registers[instruction.rd].dword = (registers[instruction.rs1].udword < registers[instruction.rs2].udword) ? 1 : 0;
			pc += 4;
			break;
		case xor_:
			registers[instruction.rd].dword = registers[instruction.rs1].dword ^ registers[instruction.rs2].dword;
			pc += 4;
			break;
		case srl:
			registers[instruction.rd].udword = registers[instruction.rs1].udword >> registers[instruction.rs2].udword;
			pc += 4;
			break;
		case sra:
			registers[instruction.rd].dword = registers[instruction.rs1].dword >> registers[instruction.rs2].dword;
			pc += 4;
			break;
		case or_:
			registers[instruction.rd].dword = registers[instruction.rs1].dword | registers[instruction.rs2].dword;
			pc += 4;
			break;
		case and_:
			registers[instruction.rd].dword = registers[instruction.rs1].dword & registers[instruction.rs2].dword;
			pc += 4;
			break;
		case lui:
			x = static_cast<int64_t>(static_cast<int32_t>(instruction.immediate));
			registers[instruction.rd].dword = x;
			//registers[instruction.rd].dword = static_cast<int64_t>(static_cast<int32_t>(instruction.immediate));
			pc += 4;
			break;
		case addw://(*) Ask if sign bit should be at position 32 or 64
			registers[instruction.rd].word = registers[instruction.rs1].word + registers[instruction.rs2].word;
			pc += 4;
			break;
		case subw:
			registers[instruction.rd].word = registers[instruction.rs1].word - registers[instruction.rs2].word;
			pc += 4;
			break;
		case sllw:
			registers[instruction.rd].word = registers[instruction.rs1].word << registers[instruction.rs2].word;
			pc += 4;
			break;
		case srlw:
			registers[instruction.rd].uword = registers[instruction.rs1].uword >> registers[instruction.rs2].uword;
			pc += 4;
			break;
		case sraw:
			registers[instruction.rd].word = registers[instruction.rs1].word >> registers[instruction.rs2].word;
			pc += 4;
			break;
		case beq:
			pc = (registers[instruction.rs1].dword ==  registers[instruction.rs2].dword)  ? pc + static_cast<uint64_t>(instruction.immediate << 1) : pc;
			break;
		case bne:
			pc = (registers[instruction.rs1].dword !=  registers[instruction.rs2].dword)  ? pc + static_cast<uint64_t>(instruction.immediate << 1) : pc;
			break;
		case blt:
			pc = (registers[instruction.rs1].dword <   registers[instruction.rs2].dword)  ? pc + static_cast<uint64_t>(instruction.immediate << 1) : pc;
			break;
		case bge:
			pc = (registers[instruction.rs1].dword >=  registers[instruction.rs2].dword)  ? pc + static_cast<uint64_t>(instruction.immediate << 1) : pc;
			break;
		case bltu:
			pc = (registers[instruction.rs1].udword <  registers[instruction.rs2].udword) ? pc + static_cast<uint64_t>(instruction.immediate << 1) : pc;
			break;
		case bgeu:
			pc = (registers[instruction.rs1].udword >= registers[instruction.rs2].udword) ? pc + static_cast<uint64_t>(instruction.immediate << 1) : pc;
			break;
		case jalr: //(*) ask about 3
			registers[instruction.rd].dword = pc + 4;
			pc = registers[instruction.rs1].udword + static_cast<uint64_t>(instruction.immediate);
			break;
		case jal:
			registers[instruction.rd].dword = pc + 4;
			pc = pc + static_cast<uint64_t>(instruction.immediate << 1);
			break;
		case ecall:
			EnvironmentCall(stopProgram);
			pc += 4;
			break;
		case ebreak:
			PrintRegisters();
			std::cin.get();
			pc += 4;
			break;
		case csrrw:
		case csrrs:
		case csrrc:
		case csrrwi:
		case csrrsi:
		case csrrci:
			throw new std::runtime_error("Instruction not implemented yet.");
		default:
			throw std::runtime_error("instruction identifier not recognized. iid: " + NumberToBits(static_cast<uint32_t>(instruction.type)));
			break;
	}
}

void Processor::SetDebugMode(bool useDebugMode)
{
	debugEnabled = useDebugMode;
}

static std::string RegisterName(uint32_t registerIndex)
{
	std::string registerNames[32] = 
	{
		"zero",
		"ra  ",
		"sp  ",
		"qp  ",
		"tp  ",
		"t0  ",
		"t1  ",
		"t2  ",
		"s0  ",
		"s1  ",
		"a0  ",
		"a1  ",
		"a2  ",
		"a3  ",
		"a4  ",
		"a5  ",
		"a6  ",
		"a7  ",
		"s2  ",
		"s3  ",
		"s4  ",
		"s5  ",
		"s6  ",
		"s7  ",
		"s8  ",
		"s9  ",
		"s10 ",
		"s11 ",
		"t3  ",
		"t4  ",
		"t5  ",
		"t6  "
	};

	return	registerNames[registerIndex];
}

void Processor::PrintRegisters()
{
	std::cout << "Registers:" << std::endl;
	uint32_t index = 0;
	for(Register x : registers)
	{
		std::cout << RegisterName(index) << "  " << std::setw(19) << std::to_string(x.dword) << "  " << NumberToBits64(x.udword) << std::endl;
		index++;
	}
	std::cout << std::endl;
}

void Processor::VerifyMemorySpace(int64_t index, int64_t size)
{
	if (index < 0 || index + size > Processor::MEMORY_SIZE)
	{
		throw new std::runtime_error("Memory access out of range.\nTried to access memory address " + std::to_string(index));
	}
}

uint8_t Processor::GetByteFromMemory(int64_t index)
{
	VerifyMemorySpace(index, 1);

	return memory[index];
}
uint16_t Processor::GetHalfWordFromMemory(int64_t index)
{
	VerifyMemorySpace(index, 2);

	const uint16_t t1 = static_cast<uint16_t>(memory[index + 0]);
	const uint16_t t2 = static_cast<uint16_t>(memory[index + 1]);

	return (t1 << 8) |
		   (t2 << 0);
}
uint32_t Processor::GetWordFromMemory(int64_t index)
{
	VerifyMemorySpace(index, 4);

	const uint32_t t1 = static_cast<uint32_t>(memory[index + 0]);
	const uint32_t t2 = static_cast<uint32_t>(memory[index + 1]);
	const uint32_t t3 = static_cast<uint32_t>(memory[index + 2]);
	const uint32_t t4 = static_cast<uint32_t>(memory[index + 3]);

	return (t1 << 24) |
		   (t2 << 16) |
		   (t3 <<  8) |
		   (t4 <<  0);
}
uint64_t Processor::GetDoubleWordFromMemory(int64_t index)
{
	VerifyMemorySpace(index, 8);

	const uint64_t t1 = static_cast<uint64_t>(memory[index + 0]);
	const uint64_t t2 = static_cast<uint64_t>(memory[index + 1]);
	const uint64_t t3 = static_cast<uint64_t>(memory[index + 2]);
	const uint64_t t4 = static_cast<uint64_t>(memory[index + 3]);
	const uint64_t t5 = static_cast<uint64_t>(memory[index + 4]);
	const uint64_t t6 = static_cast<uint64_t>(memory[index + 5]);
	const uint64_t t7 = static_cast<uint64_t>(memory[index + 6]);
	const uint64_t t8 = static_cast<uint64_t>(memory[index + 7]);

	return (t1 << 56) |
		   (t2 << 48) |
		   (t3 << 40) |
		   (t4 << 32) |
		   (t5 << 24) |
		   (t6 << 16) |
		   (t7 <<  8) |
		   (t8 <<  0);
}

void Processor::StoreByteInMemory(int64_t index, int8_t byte)
{
	VerifyMemorySpace(index, 1);

	memory[index] = static_cast<uint8_t>(byte);
}
void Processor::StoreHalfWordInMemory(int64_t index, int16_t halfWord)
{
	VerifyMemorySpace(index, 2);

	memory[index + 0] = static_cast<uint8_t>(static_cast<uint16_t>(halfWord) >> 8);
	memory[index + 1] = static_cast<uint8_t>(static_cast<uint16_t>(halfWord) >> 0);
}
void Processor::StoreWordInMemory(int64_t index, int32_t word)
{
	VerifyMemorySpace(index, 4);

	memory[index + 0] = static_cast<uint8_t>(static_cast<uint32_t>(word) >> 24);
	memory[index + 1] = static_cast<uint8_t>(static_cast<uint32_t>(word) >> 16);
	memory[index + 2] = static_cast<uint8_t>(static_cast<uint32_t>(word) >>  8);
	memory[index + 3] = static_cast<uint8_t>(static_cast<uint32_t>(word) >>  0);
}
void Processor::StoreDoubleWordInMemory(int64_t index, int64_t doubleWord)
{
	VerifyMemorySpace(index, 8);

	memory[index + 0] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >> 56);
	memory[index + 1] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >> 48);
	memory[index + 2] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >> 40);
	memory[index + 3] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >> 32);
	memory[index + 4] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >> 24);
	memory[index + 5] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >> 16);
	memory[index + 6] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >>  8);
	memory[index + 7] = static_cast<uint8_t>(static_cast<uint64_t>(doubleWord) >>  0);
}


Processor::~Processor()
{
	delete[] memory;
}
