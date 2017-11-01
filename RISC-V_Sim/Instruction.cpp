#include "Instruction.h"
#include <cstdint>
#include <stdexcept>
#include <string>

typedef struct
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t funct7 : 7;
} RType;

typedef struct
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t immediate : 12;
} IType;

typedef struct
{
	uint32_t opcode : 7;
	uint32_t immediate1 : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t immediate2 : 7;
} SType;

typedef struct
{
	uint32_t opcode : 7;
	uint32_t immediate1 : 1;
	uint32_t immediate2 : 4;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t immediate3 : 6;
	uint32_t immediate4 : 1;
} SBType;

typedef struct
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t immediate1 : 8;
	uint32_t immediate2 : 1;
	uint32_t immediate3 : 10;
	uint32_t immediate4 : 1;
} UJType;

typedef struct
{
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t immediate : 20;
} UType;

Instruction DecodeRType(const uint32_t rawInstruction)
{
	const RType rType = { rawInstruction };

	Instruction decoded;
	decoded.opcode = rType.opcode;
	decoded.rd = rType.rd;
	decoded.funct3 = rType.funct3;
	decoded.rs1 = rType.rs1;
	decoded.rs2 = rType.rs2;
	decoded.funct7 = rType.funct7;

	return decoded;
}

Instruction DecodeIType(const uint32_t rawInstruction)
{
	const IType iType = { rawInstruction };

	Instruction decoded;
	decoded.opcode = iType.opcode;
	decoded.rd = iType.rd;
	decoded.funct3 = iType.funct3;
	decoded.rs1 = iType.rs1;
	decoded.immediate = iType.immediate;

	return decoded;
}

Instruction DecodeSType(const uint32_t rawInstruction)
{
	const SType sType = { rawInstruction };

	Instruction decoded;
	decoded.opcode = sType.opcode;
	decoded.funct3 = sType.funct3;
	decoded.rs1 = sType.rs1;
	decoded.rs2 = sType.rs2;
	decoded.immediate = (sType.immediate2 << 5) | sType.immediate1;

	return decoded;
}

Instruction DecodeSBType(const uint32_t rawInstruction)
{
	const SBType sbType = { rawInstruction };

	Instruction decoded;
	decoded.opcode = sbType.opcode;
	decoded.funct3 = sbType.funct3;
	decoded.rs1 = sbType.rs1;
	decoded.rs2 = sbType.rs2;
	decoded.immediate = (sbType.immediate1 << 11) |
		(sbType.immediate2 << 1) |
		(sbType.immediate3 << 5) |
		(sbType.immediate4 << 12);

	return decoded;
}

Instruction DecodeUJType(const uint32_t rawInstruction)
{
	const UJType ujType = { rawInstruction };

	Instruction decoded;
	decoded.opcode = ujType.opcode;
	decoded.rd = ujType.rd;
	decoded.immediate = (ujType.immediate1 << 12) |
		(ujType.immediate2 << 11) |
		(ujType.immediate3 << 1) |
		(ujType.immediate4 << 20);

	return decoded;
}

Instruction DecodeUType(const uint32_t rawInstruction)
{
	const UType uType = { rawInstruction };

	Instruction decoded;
	decoded.opcode = uType.opcode;
	decoded.rd = uType.rd;
	decoded.immediate = uType.immediate;

	return decoded;
}

Instruction* DecodeInstructions(uint32_t* rawInstructions, uint64_t instructionsCount)
{
	Instruction* instructions = new Instruction[instructionsCount];

	for (int32_t i = 0; i < instructionsCount; i++)
	{
		const uint32_t rawInstruction = rawInstructions[i];
		//opcode is the first 7 bits
		const uint32_t opcode = rawInstruction & 127;

		Instruction instruction;
		switch (opcode)
		{
		case 3:
		case 15:
		case 19:
		case 27:
		case 103:
		case 115:
			instruction = DecodeIType(rawInstruction);
			break;
		case 23:
		case 55:
			instruction = DecodeUType(rawInstruction);
			break;
		case 35:
			instruction = DecodeSType(rawInstruction);
			break;
		case 51:
		case 59:
			instruction = DecodeRType(rawInstruction);
			break;
		case 99:
			instruction = DecodeSBType(rawInstruction);
			break;
		case 111:
			instruction = DecodeUJType(rawInstruction);
			break;
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(opcode));
		}

		instructions[i] = instruction;
	}

	return instructions;
}
