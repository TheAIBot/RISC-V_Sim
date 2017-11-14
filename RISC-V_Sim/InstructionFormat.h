#pragma once

#include <cstdint>

struct RType
{
	uint32_t opcode;
	uint32_t rd;
	uint32_t funct3;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t funct7;

	static const uint32_t opcode_mask = 0b0000'0000'0000'0000'0000'0000'0111'1111;
	static const uint32_t rd_mask     = 0b0000'0000'0000'0000'0000'1111'1000'0000;
	static const uint32_t funct3_mask = 0b0000'0000'0000'0000'0111'0000'0000'0000;
	static const uint32_t rs1_mask    = 0b0000'0000'0000'1111'1000'0000'0000'0000;
	static const uint32_t rs2_mask    = 0b0000'0001'1111'0000'0000'0000'0000'0000;
	static const uint32_t funct7_mask = 0b1111'1110'0000'0000'0000'0000'0000'0000;

	static const uint32_t opcode_length = 7;
	static const uint32_t rd_length     = 5;
	static const uint32_t funct3_length = 3;
	static const uint32_t rs1_length    = 5;
	static const uint32_t rs2_length    = 5;
	static const uint32_t funct7_length = 7;

	static const uint32_t opcode_shift = 0;
	static const uint32_t rd_shift     = opcode_shift + opcode_length;
	static const uint32_t funct3_shift = rd_shift     + rd_length;
	static const uint32_t rs1_shift    = funct3_shift + funct3_length;
	static const uint32_t rs2_shift    = rs1_shift    + rs1_length;
	static const uint32_t funct7_shift = rs2_shift    + rs2_length;

	RType(const uint32_t rawInstruction)
	{
		opcode = (rawInstruction & opcode_mask) >> opcode_shift;
		rd     = (rawInstruction & rd_mask    ) >> rd_shift;
		funct3 = (rawInstruction & funct3_mask) >> funct3_shift;
		rs1    = (rawInstruction & rs1_mask   ) >> rs1_shift;
		rs2    = (rawInstruction & rs2_mask   ) >> rs2_shift;
		funct7 = (rawInstruction & funct7_mask) >> funct7_shift;
	}
	RType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return (opcode << opcode_shift) |
			   (rd     << rd_shift    ) |
			   (funct3 << funct3_shift) |
			   (rs1    << rs1_shift   ) |
			   (rs2    << rs2_shift   ) |
			   (funct7 << funct7_shift);
	}
};

struct IType
{
	uint32_t opcode;
	uint32_t rd;
	uint32_t funct3;
	uint32_t rs1;
	uint32_t immediate;

	static const uint32_t opcode_mask    = 0b0000'0000'0000'0000'0000'0000'0111'1111;
	static const uint32_t rd_mask        = 0b0000'0000'0000'0000'0000'1111'1000'0000;
	static const uint32_t funct3_mask    = 0b0000'0000'0000'0000'0111'0000'0000'0000;
	static const uint32_t rs1_mask       = 0b0000'0000'0000'1111'1000'0000'0000'0000;
	static const uint32_t immediate_mask = 0b1111'1111'1111'0000'0000'0000'0000'0000;

	static const uint32_t opcode_length    =  7;
	static const uint32_t rd_length        =  5;
	static const uint32_t funct3_length    =  3;
	static const uint32_t rs1_length       =  5;
	static const uint32_t immediate_length = 12;

	static const uint32_t opcode_shift    = 0;
	static const uint32_t rd_shift        = opcode_shift + opcode_length;
	static const uint32_t funct3_shift    = rd_shift     + rd_length;
	static const uint32_t rs1_shift       = funct3_shift + funct3_length;
	static const uint32_t immediate_shift = rs1_shift    + rs1_length;

	IType(const uint32_t rawInstruction)
	{
		opcode    = (rawInstruction & opcode_mask   ) >> opcode_shift;
		rd        = (rawInstruction & rd_mask       ) >> rd_shift;
		funct3    = (rawInstruction & funct3_mask   ) >> funct3_shift;
		rs1       = (rawInstruction & rs1_mask      ) >> rs1_shift;
		immediate = (rawInstruction & immediate_mask) >> immediate_shift;
	}
	IType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return (opcode    << opcode_shift) |
			   (rd        << rd_shift)     |
			   (funct3    << funct3_shift) |
			   (rs1       << rs1_shift)    |
			   (immediate << immediate_shift);
	}
};

struct SType
{
	uint32_t opcode     : 7;
	uint32_t immediate1 : 5;
	uint32_t funct3     : 3;
	uint32_t rs1        : 5;
	uint32_t rs2        : 5;
	uint32_t immediate2 : 7;
};
union USType
{
	uint32_t rawInstruction;
	SType type;
};
static_assert(sizeof(SType) == sizeof(uint32_t), "SType isn't 4 bytes long");

struct SBType
{
	uint32_t opcode     : 7;
	uint32_t immediate1 : 1;
	uint32_t immediate2 : 4;
	uint32_t funct3     : 3;
	uint32_t rs1        : 5;
	uint32_t rs2        : 5;
	uint32_t immediate3 : 6;
	uint32_t immediate4 : 1;
};
union USBType
{
	uint32_t rawInstruction;
	SBType type;
};
static_assert(sizeof(SBType) == sizeof(uint32_t), "SBType isn't 4 bytes long");

struct UJType
{
	uint32_t opcode     : 7;
	uint32_t rd         : 5;
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
static_assert(sizeof(UJType) == sizeof(uint32_t), "UJType isn't 4 bytes long");

struct UType
{
	uint32_t opcode    :  7;
	uint32_t rd        :  5;
	uint32_t immediate : 20;
};
union UUType
{
	uint32_t rawInstruction;
	UType type;
};
static_assert(sizeof(UType) == sizeof(uint32_t), "UType isn't 4 bytes long");