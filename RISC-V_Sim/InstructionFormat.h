#pragma once

#include <cstdint>

template<uint32_t MASK>
constexpr uint32_t Shift_From_Mask()
{
	if constexpr (MASK & 1 || MASK == 0)
	{
		return 0;
	}
	const uint32_t newMask = MASK >> 1;
	return Shift_From_Mask<newMask>() + 1;
}

template<uint32_t MASK>
class BitField
{
private:
	uint32_t field;

public:
	void FromRawInstruction(const uint32_t rawInstruction)
	{
		field = rawInstruction & MASK;
	}

	void FromInt(const uint32_t value)
	{
		field = (value << Shift_From_Mask<MASK>()) & MASK;
	}

	uint32_t GetField() const
	{
		return field;
	}

	uint32_t GetAsInt() const
	{
		return field >> Shift_From_Mask<MASK>();
	}
};

struct RType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b0000'0001'1111'0000'0000'0000'0000'0000> rs2;
	BitField<0b1111'1110'0000'0000'0000'0000'0000'0000> funct7;

	RType(const uint32_t rawInstruction)
	{
		opcode.FromRawInstruction(rawInstruction);
		rd    .FromRawInstruction(rawInstruction);
		funct3.FromRawInstruction(rawInstruction);
		rs1   .FromRawInstruction(rawInstruction);
		rs2   .FromRawInstruction(rawInstruction);
		funct7.FromRawInstruction(rawInstruction);
	}
	RType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return opcode.GetField() | rd.GetField() | funct3.GetField() | rs1.GetField() | rs2.GetField() | funct7.GetField();
	}
};

struct IType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b1111'1111'1111'0000'0000'0000'0000'0000> immediate;

	IType(const uint32_t rawInstruction)
	{
		opcode   .FromRawInstruction(rawInstruction);
		rd       .FromRawInstruction(rawInstruction);
		funct3   .FromRawInstruction(rawInstruction);
		rs1      .FromRawInstruction(rawInstruction);
		immediate.FromRawInstruction(rawInstruction);
	}
	IType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return opcode.GetField() | rd.GetField() | funct3.GetField() | rs1.GetField() | immediate.GetField();
	}
};

struct SType
{
	uint32_t opcode;
	uint32_t immediate1;
	uint32_t funct3;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t immediate2;

	static const uint32_t opcode_mask     = 0b0000'0000'0000'0000'0000'0000'0111'1111;
	static const uint32_t immediate1_mask = 0b0000'0000'0000'0000'0000'1111'1000'0000;
	static const uint32_t funct3_mask     = 0b0000'0000'0000'0000'0111'0000'0000'0000;
	static const uint32_t rs1_mask        = 0b0000'0000'0000'1111'1000'0000'0000'0000;
	static const uint32_t rs2_mask        = 0b0000'0001'1111'0000'0000'0000'0000'0000;
	static const uint32_t immediate2_mask = 0b1111'1110'0000'0000'0000'0000'0000'0000;

	static const uint32_t opcode_length     = 7;
	static const uint32_t immediate1_length = 5;
	static const uint32_t funct3_length     = 3;
	static const uint32_t rs1_length        = 5;
	static const uint32_t rs2_length        = 5;
	static const uint32_t immediate2_length = 7;

	static const uint32_t opcode_shift     = 0;
	static const uint32_t immediate1_shift = opcode_shift     + opcode_length;
	static const uint32_t funct3_shift     = immediate1_shift + immediate1_length;
	static const uint32_t rs1_shift        = funct3_shift     + funct3_length;
	static const uint32_t rs2_shift        = rs1_shift        + rs1_length;
	static const uint32_t immediate2_shift = rs2_shift        + rs2_length;

	SType(const uint32_t rawInstruction)
	{
		opcode     = (rawInstruction & opcode_mask    ) >> opcode_shift;
		immediate1 = (rawInstruction & immediate1_mask) >> immediate1_shift;
		funct3     = (rawInstruction & funct3_mask    ) >> funct3_shift;
		rs1        = (rawInstruction & rs1_mask       ) >> rs1_shift;
		rs2        = (rawInstruction & rs2_mask       ) >> rs2_shift;
		immediate2 = (rawInstruction & immediate2_mask) >> immediate2_shift;
	}
	SType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return (opcode     << opcode_shift    ) |
			   (immediate1 << immediate1_shift) |
			   (funct3     << funct3_shift    ) |
			   (rs1        << rs1_shift       ) |
			   (rs2        << rs2_shift       ) |
			   (immediate2 << immediate2_shift);
	}
};

struct SBType
{
	uint32_t opcode;
	uint32_t immediate1;
	uint32_t immediate2;
	uint32_t funct3;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t immediate3;
	uint32_t immediate4;

	static const uint32_t opcode_mask     = 0b0000'0000'0000'0000'0000'0000'0111'1111;
	static const uint32_t immediate1_mask = 0b0000'0000'0000'0000'0000'0000'1000'0000;
	static const uint32_t immediate2_mask = 0b0000'0000'0000'0000'0000'1111'0000'0000;
	static const uint32_t funct3_mask     = 0b0000'0000'0000'0000'0111'0000'0000'0000;
	static const uint32_t rs1_mask        = 0b0000'0000'0000'1111'1000'0000'0000'0000;
	static const uint32_t rs2_mask        = 0b0000'0001'1111'0000'0000'0000'0000'0000;
	static const uint32_t immediate3_mask = 0b0111'1110'0000'0000'0000'0000'0000'0000;
	static const uint32_t immediate4_mask = 0b1000'0000'0000'0000'0000'0000'0000'0000;

	static const uint32_t opcode_length     = 7;
	static const uint32_t immediate1_length = 1;
	static const uint32_t immediate2_length = 4;
	static const uint32_t funct3_length     = 3;
	static const uint32_t rs1_length        = 5;
	static const uint32_t rs2_length        = 5;
	static const uint32_t immediate3_length = 6;
	static const uint32_t immediate4_length = 1;

	static const uint32_t opcode_shift     = 0;
	static const uint32_t immediate1_shift = opcode_shift     + opcode_length;
	static const uint32_t immediate2_shift = immediate1_shift + immediate1_length;
	static const uint32_t funct3_shift     = immediate2_shift + immediate2_length;
	static const uint32_t rs1_shift        = funct3_shift     + funct3_length;
	static const uint32_t rs2_shift        = rs1_shift        + rs1_length;
	static const uint32_t immediate3_shift = rs2_shift        + rs2_length;
	static const uint32_t immediate4_shift = immediate3_shift + immediate3_length;

	SBType(const uint32_t rawInstruction)
	{
		opcode     = (rawInstruction & opcode_mask    ) >> opcode_shift;
		immediate1 = (rawInstruction & immediate1_mask) >> immediate1_shift;
		immediate2 = (rawInstruction & immediate2_mask) >> immediate2_shift;
		funct3     = (rawInstruction & funct3_mask    ) >> funct3_shift;
		rs1        = (rawInstruction & rs1_mask       ) >> rs1_shift;
		rs2        = (rawInstruction & rs2_mask       ) >> rs2_shift;
		immediate3 = (rawInstruction & immediate3_mask) >> immediate3_shift;
		immediate4 = (rawInstruction & immediate4_mask) >> immediate4_shift;
	}
	SBType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return (opcode     << opcode_shift    ) |
			   (immediate1 << immediate1_shift) |
			   (immediate2 << immediate2_shift) |
			   (funct3     << funct3_shift    ) |
			   (rs1        << rs1_shift       ) |
			   (rs2        << rs2_shift       ) |
			   (immediate3 << immediate3_shift) |
			   (immediate4 << immediate4_shift);
	}
};

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