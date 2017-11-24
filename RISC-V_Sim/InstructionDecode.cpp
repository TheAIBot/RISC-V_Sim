#include "InstructionDecode.h"
#include <cstdint>
#include <stdexcept>
#include "Instruction.h"
#include "InstructionFormat.h"
#include "ImmediateFormat.h"

static uint32_t GetImmediateMask(uint16_t instructionIdentifier)
{
	const uint32_t removefunct7    = 0b00000000'00000000'00000000'00011111;
	const uint32_t wholeidentifier = 0b11111111'11111111'11111111'11111111;
	switch (instructionIdentifier)
	{
		case 0b000000'001'0010011:
		case 0b000000'101'0010011:
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
		case 0b000000'000'0110011:
		case 0b000000'001'0110011:
		case 0b000000'010'0110011:
		case 0b000000'011'0110011:
		case 0b000000'100'0110011:
		case 0b000000'101'0110011:
		case 0b000000'110'0110011:
		case 0b000000'111'0110011:
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

static Instruction DecodeRType(const uint32_t rawInstruction)
{
	RType rType(rawInstruction);
	Instruction decoded;
	decoded.rd   = rType.rd.GetAsInt();
	decoded.rs1  = rType.rs1.GetAsInt();
	decoded.rs2  = rType.rs2.GetAsInt();
	decoded.type = GetInstructionType(rType.opcode.GetAsInt(), rType.funct3.GetAsInt(), rType.funct7.GetAsInt());

	return decoded;
}

static Instruction DecodeIType(const uint32_t rawInstruction)
{
	const IType iType(rawInstruction);

	Instruction decoded = { 0 };
	decoded.rd         = iType.rd.GetAsInt();
	decoded.rs1        = iType.rs1.GetAsInt();
	decoded.immediate  = SignExtend<12>(iType.immediate.GetAsInt());
	decoded.type       = GetInstructionType(iType.opcode.GetAsInt(), iType.funct3.GetAsInt(), iType.immediate.GetAsInt() >> 5);
	decoded.immediate &= GetImmediateMask((iType.funct3.GetAsInt() << 7) | iType.opcode.GetAsInt());

	return decoded;
}

static Instruction DecodeSType(const uint32_t rawInstruction)
{
	const SType sType(rawInstruction);

	SImmediate sImmediate;
	sImmediate.immediate1.FromInt(sType.immediate1.GetAsInt());
	sImmediate.immediate2.FromInt(sType.immediate2.GetAsInt());

	Instruction decoded = { 0 };
	decoded.rs1 = sType.rs1.GetAsInt();
	decoded.rs2 = sType.rs2.GetAsInt();
	decoded.immediate = sImmediate.ToImmediate();
	decoded.type = GetInstructionType(sType.opcode.GetAsInt(), sType.funct3.GetAsInt(), 0);

	return decoded;
}

static Instruction DecodeSBType(const uint32_t rawInstruction)
{
	const SBType sbType(rawInstruction);

	SBImmediate sbImmediate;
	sbImmediate.immediate1.FromInt(sbType.immediate2.GetAsInt());
	sbImmediate.immediate2.FromInt(sbType.immediate3.GetAsInt());
	sbImmediate.immediate3.FromInt(sbType.immediate1.GetAsInt());
	sbImmediate.immediate4.FromInt(sbType.immediate4.GetAsInt());

	Instruction decoded = { 0 };
	decoded.rs1 = sbType.rs1.GetAsInt();
	decoded.rs2 = sbType.rs2.GetAsInt();
	decoded.immediate = sbImmediate.ToImmediate();
	decoded.type = GetInstructionType(sbType.opcode.GetAsInt(), sbType.funct3.GetAsInt(), 0);

	return decoded;
}

static Instruction DecodeUJType(const uint32_t rawInstruction)
{
	const UJType ujType(rawInstruction);

	UJImmediate ujImmediate;
	ujImmediate.immediate1.FromInt(ujType.immediate3.GetAsInt());
	ujImmediate.immediate2.FromInt(ujType.immediate2.GetAsInt());
	ujImmediate.immediate3.FromInt(ujType.immediate1.GetAsInt());
	ujImmediate.immediate4.FromInt(ujType.immediate4.GetAsInt());

	Instruction decoded = { 0 };
	decoded.rd = ujType.rd.GetAsInt();
	decoded.immediate = ujImmediate.ToImmediate();
	decoded.type = GetInstructionType(ujType.opcode.GetAsInt(), 0, 0);

	return decoded;
}

static Instruction DecodeUType(const uint32_t rawInstruction)
{
	const UType uType(rawInstruction);

	UImmediate uImmediate;
	uImmediate.immediate1.FromInt(uType.immediate.GetAsInt());

	Instruction decoded = { 0 };
	decoded.rd = uType.rd.GetAsInt();
	decoded.immediate = uImmediate.ToImmediate();
	decoded.type = GetInstructionType(uType.opcode.GetAsInt(), 0, 0);

	return decoded;
}

Instruction DecodeInstruction(const uint32_t rawInstruction)
{
	//opcode is the first 7 bits
	const uint32_t opcode = rawInstruction & 127;

	switch (opcode)
	{
		case 0b00000011:
		case 0b00001111:
		case 0b00010011:
		case 0b01100111:
		case 0b01110011:
			return DecodeIType(rawInstruction);
		case 0b00010111:
		case 0b00110111:
			return DecodeUType(rawInstruction);
		case 0b00100011:
			return DecodeSType(rawInstruction);
		case 0b00110011:
			return DecodeRType(rawInstruction);
		case 0b01100011:
			return DecodeSBType(rawInstruction);
		case 0b01101111:
			return DecodeUJType(rawInstruction);
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(opcode));
	}
}

const Instruction* DecodeInstructions(const uint32_t* rawInstructions, const uint32_t instructionsCount)
{
	Instruction* instructions = new Instruction[instructionsCount];

	for (uint32_t i = 0; i < instructionsCount; i++)
	{
		const uint32_t rawInstruction = rawInstructions[i];
		instructions[i] = DecodeInstruction(rawInstruction);
		//PrintInstruction(instructions[i]);
	}

	return instructions;
}

std::string GetProgramAsString(const uint32_t* rawInstructions, const uint32_t instructionCount)
{
	std::string program;
	for(uint32_t i = 0; i < instructionCount; i++)
	{
		const Instruction& instruction = DecodeInstruction(rawInstructions[i]);
		program += InstructionAsString(instruction) + "\n";
	}

	return program;
}