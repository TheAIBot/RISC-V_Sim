#include "Instruction.h"
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <iomanip>

struct RType
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t funct7 : 7;
};
union URType
{
	uint32_t rawInstruction;
	RType type;
};

struct IType
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t immediate : 12;
};
union UIType
{
	uint32_t rawInstruction;
	IType type;
};

struct SType
{
	uint32_t opcode : 7;
	uint32_t immediate1 : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t immediate2 : 7;
};
union USType
{
	uint32_t rawInstruction;
	SType type;
};

struct SBType
{
	uint32_t opcode : 7;
	uint32_t immediate1 : 1;
	uint32_t immediate2 : 4;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t immediate3 : 6;
	uint32_t immediate4 : 1;
};
union USBType
{
	uint32_t rawInstruction;
	SBType type;
};

struct UJType
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t immediate1 : 8;
	uint32_t immediate2 : 1;
	uint32_t immediate3 : 10;
	uint32_t immediate4 : 1;
};
union UUJType
{
	uint32_t rawInstruction;
	UJType type;
};

struct UType
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t immediate : 20;
};
union UUType
{
	uint32_t rawInstruction;
	UType type;
};

static uint16_t GetInstructionIdentifierMask(uint16_t instructionIdentifier)
{
	const uint16_t onlyOpCodeAndFunct3 = 0b000000'111'1111111;
	const uint16_t wholeidentifier     = 0b111111'111'1111111;
	switch (instructionIdentifier & onlyOpCodeAndFunct3)
	{
		case 0b000000'001'0010011:
		case 0b000000'101'0010011:
		case 0b000000'001'0011011:
		case 0b000000'101'0011011:
		case 0b000000'000'0110011:
		case 0b000000'001'0110011:
		case 0b000000'010'0110011:
		case 0b000000'011'0110011:
		case 0b000000'100'0110011:
		case 0b000000'101'0110011:
		case 0b000000'110'0110011:
		case 0b000000'111'0110011:
		case 0b000000'000'0111011:
		case 0b000000'001'0111011:
		case 0b000000'101'0111011:
		case 0b000000'000'1110011:
			return wholeidentifier;
		default:
			return onlyOpCodeAndFunct3;
	}
}

static InstructionType GetInstructionType(const uint32_t opcode, const uint32_t funct3, const uint32_t funct7OrImmediate)
{
	const uint16_t instructionIdentifier = static_cast<uint16_t>((opcode            <<  0) |
																 (funct3            <<  7) |
																 (funct7OrImmediate << 10));
	const uint16_t mask = GetInstructionIdentifierMask(instructionIdentifier);

	const uint16_t instructionType = instructionIdentifier & mask;
	return static_cast<InstructionType>(instructionType);
}

static uint32_t SignExtend_uint12_t(uint32_t toExtend)
{
	return (toExtend & 0b1000'0000'0000) ? toExtend | 0xff'ff'f0'00 : toExtend;
}
static uint32_t SignExtend_uint20_t(uint32_t toExtend)
{
	return (toExtend & 0b1000'0000'0000'0000'0000) ? toExtend | 0xff'f0'00'00 : toExtend;
}

static Instruction DecodeRType(const uint32_t rawInstruction)
{
	const URType rType = { rawInstruction };

	Instruction decoded = { 0 };
	decoded.rd = rType.type.rd;
	decoded.rs1 = rType.type.rs1;
	decoded.rs2 = rType.type.rs2;
	decoded.type = GetInstructionType(rType.type.opcode, rType.type.funct3, rType.type.funct7);

	return decoded;
}

static Instruction DecodeIType(const uint32_t rawInstruction)
{
	const UIType iType = { rawInstruction };

	Instruction decoded = { 0 };
	decoded.rd = iType.type.rd;
	decoded.rs1 = iType.type.rs1;
	decoded.immediate = SignExtend_uint12_t(iType.type.immediate);
	decoded.type = GetInstructionType(iType.type.opcode, iType.type.funct3, iType.type.immediate);

	return decoded;
}

static Instruction DecodeSType(const uint32_t rawInstruction)
{
	const USType sType = { rawInstruction };

	Instruction decoded = { 0 };
	decoded.rs1 = sType.type.rs1;
	decoded.rs2 = sType.type.rs2;
	decoded.immediate = (sType.type.immediate2 << 5) |
						(sType.type.immediate1 << 0);
	decoded.immediate = SignExtend_uint12_t(decoded.immediate);
	decoded.type = GetInstructionType(sType.type.opcode, sType.type.funct3, 0);

	return decoded;
}

static Instruction DecodeSBType(const uint32_t rawInstruction)
{
	const USBType sbType = { rawInstruction };

	Instruction decoded = { 0 };
	decoded.rs1 = sbType.type.rs1;
	decoded.rs2 = sbType.type.rs2;
	decoded.immediate = (sbType.type.immediate1 << 11) |
						(sbType.type.immediate2 <<  1) |
						(sbType.type.immediate3 <<  5) |
						(sbType.type.immediate4 << 12);
	decoded.immediate >>= 1;
	decoded.immediate = SignExtend_uint12_t(decoded.immediate);
	decoded.immediate <<= 1;
	decoded.type = GetInstructionType(sbType.type.opcode, sbType.type.funct3, 0);

	return decoded;
}

static Instruction DecodeUJType(const uint32_t rawInstruction)
{
	const UUJType ujType = { rawInstruction };

	Instruction decoded = { 0 };
	decoded.rd = ujType.type.rd;
	decoded.immediate = (ujType.type.immediate1 << 12) |
						(ujType.type.immediate2 << 11) |
						(ujType.type.immediate3 <<  1) |
						(ujType.type.immediate4 << 20);
	decoded.immediate = SignExtend_uint20_t(decoded.immediate);
	decoded.type = GetInstructionType(ujType.type.opcode, 0, 0);

	return decoded;
}

static Instruction DecodeUType(const uint32_t rawInstruction)
{
	const UUType uType = { rawInstruction };

	Instruction decoded = { 0 };
	decoded.rd = uType.type.rd;
	decoded.immediate = uType.type.immediate << 12;
	decoded.type = GetInstructionType(uType.type.opcode, 0, 0);

	return decoded;
}

std::string GetNameOfInstructionType(InstructionType type)
{
	switch (type)
	{
		case lb:
			return "lb";
		case lh:
			return "lh";
		case lw:
			return "lw";
		case ld:
			return "ld";
		case lbu:
			return "lbu";
		case lhu:
			return "lhu";
		case lwu:
			return "lwu";
		case fence:
			return "fence";
		case fence_i:
			return "fence_i";
		case addi:
			return "addi";
		case slli:
			return "slli";
		case slti:
			return "slti";
		case sltiu:
			return "sltiu";
		case xori:
			return "xori";
		case srli:
			return "srli";
		case srai:
			return "srai";
		case ori:
			return "ori";
		case andi:
			return "andi";
		case auipc:
			return "auipc";
		case addiw:
			return "addiw";
		case slliw:
			return "slliw";
		case srliw:
			return "srliw";
		case sraiw:
			return "sraiw";
		case sb:
			return "sb";
		case sh:
			return "sh";
		case sw:
			return "sw";
		case sd:
			return "sd";
		case add:
			return "add";
		case sub:
			return "sub";
		case sll:
			return "sll";
		case slt:
			return "slt";
		case sltu:
			return "sltu";
		case xor_:
			return "xor";
		case srl:
			return "srl";
		case sra:
			return "sra";
		case or_:
			return "or";
		case and_:
			return "and";
		case lui:
			return "lui";
		case addw:
			return "addw";
		case subw:
			return "subw";
		case sllw:
			return "sllw";
		case srlw:
			return "srlw";
		case sraw:
			return "sraw";
		case beq:
			return "beq";
		case bne:
			return "bne";
		case blt:
			return "blt";
		case bge:
			return "bge";
		case bltu:
			return "bltu";
		case bgeu:
			return "bgeu";
		case jalr:
			return "jalr";
		case jal:
			return "jal";
		case ecall:
			return "ecall";
		case ebreak:
			return "ebreak";
		case csrrw:
			return "csrrw";
		case csrrs:
			return "csrrs";
		case csrrc:
			return "csrrc";
		case csrrwi:
			return "csrrwi";
		case csrrsi:
			return "csrrsi";
		case csrrci:
			return "csrrci";
		default:
			throw new std::runtime_error("Invalid instruction type. Type: " + std::to_string(static_cast<uint16_t>(type)));
	}
}

std::string NumberToBits(uint32_t n)
{
	//32 bits, 3 spaces and 1 null terminator
	char bits[32 + 4 + 1];
	uint32_t index = 0;
	for(int i = 0; i < 4; i++)
	{
		for(int x = 0; x < 8; x++)
		{
			const char bit = (n & 0x80000000) ? '1' : '0';
			bits[index] = bit;
			index++;

			n <<= 1;
		}
		bits[index] = ' ';
		index++;
	}
	bits[index] = '\0';
	return std::string(bits);
}

std::string NumberToBits64(uint64_t n)
{
	//32 bits, 3 spaces and 1 null terminator
	char bits[64 + 8 + 1];
	uint32_t index = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int x = 0; x < 8; x++)
		{
			const char bit = (n & 0x80'00'00'00'00'00'00'00) ? '1' : '0';
			bits[index] = bit;
			index++;

			n <<= 1;
		}
		bits[index] = ' ';
		index++;
	}
	bits[index] = '\0';
	return std::string(bits);
}

static void PrintInstruction(Instruction instruction) 
{
	std::cout << std::setfill(' ') << std::endl;
	std::cout << std::setw(10) << GetNameOfInstructionType(instruction.type);
	std::cout << "   " << NumberToBits(instruction.type) << std::endl;

	std::cout << std::setw(10) << instruction.immediate;  
	std::cout << "   " << NumberToBits(instruction.immediate) << std::endl;

	std::cout << std::setw(10) << static_cast<uint32_t>(instruction.rd);     
	std::cout << "   " << NumberToBits(instruction.rd) << std::endl;

	std::cout << std::setw(10) << static_cast<uint32_t>(instruction.rs1);    
	std::cout << "   " << NumberToBits(instruction.rs1) << std::endl;

	std::cout << std::setw(10) << static_cast<uint32_t>(instruction.rs2);   
	std::cout << "   " << NumberToBits(instruction.rs2) << std::endl;
	std::cout << std::endl;
}

Instruction* DecodeInstructions(uint32_t* rawInstructions, uint64_t instructionsCount)
{
	Instruction* instructions = new Instruction[instructionsCount];

	for (uint64_t i = 0; i < instructionsCount; i++)
	{
		const uint32_t rawInstruction = rawInstructions[i];
		//opcode is the first 7 bits
		const uint32_t opcode = rawInstruction & 127;

		Instruction instruction;
		switch (opcode)
		{
		case 0b0000'0011:
		case 0b0000'1111:
		case 0b0001'0011:
		case 0b0001'1011:
		case 0b0110'0111:
		case 0b0111'0011:
			instruction = DecodeIType(rawInstruction);
			break;
		case 0b0001'0111:
		case 0b0011'0111:
			instruction = DecodeUType(rawInstruction);
			break;
		case 0b0010'0011:
			instruction = DecodeSType(rawInstruction);
			break;
		case 0b0011'0011:
		case 0b0011'1011:
			instruction = DecodeRType(rawInstruction);
			break;
		case 0b0110'0011:
			instruction = DecodeSBType(rawInstruction);
			break;
		case 0b0110'1111:
			instruction = DecodeUJType(rawInstruction);
			break;
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(opcode));
		}

		PrintInstruction(instruction);
		instructions[i] = instruction;
	}

	return instructions;
}