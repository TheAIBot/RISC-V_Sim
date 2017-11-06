#include "InstructionDecode.h"
#include <cstdint>
#include <stdexcept>
#include "Instruction.h"
#include "InstructionFormat.h"

static uint32_t GetImmediateMask(uint16_t instructionIdentifier)
{
	const uint32_t removefunct7    = 0b00000000'00000000'00000000'00011111;
	const uint32_t wholeidentifier = 0b11111111'11111111'11111111'11111111;
	switch (instructionIdentifier)
	{
		case 0b000000'001'0010011:
		case 0b000000'101'0010011:
		case 0b000000'001'0011011:
		case 0b000000'101'0011011:
			return removefunct7;
		default:
			return wholeidentifier;
	}
}

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
	decoded.type = GetInstructionType(iType.type.opcode, iType.type.funct3, iType.type.immediate >> 5);
	decoded.immediate &= GetImmediateMask((iType.type.funct3 << 7) | iType.type.opcode);

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

Instruction DecodeInstruction(const uint32_t rawInstruction)
{
	//opcode is the first 7 bits
	const uint32_t opcode = rawInstruction & 127;

	switch (opcode)
	{
		case 0b0000'0011:
		case 0b0000'1111:
		case 0b0001'0011:
		case 0b0001'1011:
		case 0b0110'0111:
		case 0b0111'0011:
			return DecodeIType(rawInstruction);
		case 0b0001'0111:
		case 0b0011'0111:
			return DecodeUType(rawInstruction);
		case 0b0010'0011:
			return DecodeSType(rawInstruction);
		case 0b0011'0011:
		case 0b0011'1011:
			return DecodeRType(rawInstruction);
		case 0b0110'0011:
			return DecodeSBType(rawInstruction);
		case 0b0110'1111:
			return DecodeUJType(rawInstruction);
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(opcode));
	}
}

Instruction* DecodeInstructions(const uint32_t* rawInstructions, const uint64_t instructionsCount)
{
	Instruction* instructions = new Instruction[instructionsCount];

	for (uint64_t i = 0; i < instructionsCount; i++)
	{
		const uint32_t rawInstruction = rawInstructions[i];
		instructions[i] = DecodeInstruction(rawInstruction);
		//PrintInstruction(instructions[i]);
	}

	return instructions;
}