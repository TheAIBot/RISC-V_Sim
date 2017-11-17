#pragma once

#include <cstdint>

template<uint32_t MASK>
constexpr uint32_t Shift_From_Mask()
{
	if (MASK & 1 || MASK == 0)
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
		return opcode.GetField() | 
			   rd.GetField()     | 
			   funct3.GetField() | 
			   rs1.GetField()    | 
			   rs2.GetField()    | 
			   funct7.GetField();
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
		return opcode.GetField() | 
			   rd.GetField()     | 
			   funct3.GetField() | 
			   rs1.GetField()    | 
			   immediate.GetField();
	}
};

struct SType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> immediate1;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b0000'0001'1111'0000'0000'0000'0000'0000> rs2;
	BitField<0b1111'1110'0000'0000'0000'0000'0000'0000> immediate2;

	SType(const uint32_t rawInstruction)
	{
		opcode    .FromRawInstruction(rawInstruction);
		immediate1.FromRawInstruction(rawInstruction);
		funct3    .FromRawInstruction(rawInstruction);
		rs1       .FromRawInstruction(rawInstruction);
		rs2       .FromRawInstruction(rawInstruction);
		immediate2.FromRawInstruction(rawInstruction);
	}
	SType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return opcode.GetField()     | 
			   immediate1.GetField() | 
			   funct3.GetField()     | 
			   rs1.GetField()        | 
			   rs2.GetField()        | 
			   immediate2.GetField();
	}
};

struct SBType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'0000'1000'0000> immediate1;
	BitField<0b0000'0000'0000'0000'0000'1111'0000'0000> immediate2;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b0000'0001'1111'0000'0000'0000'0000'0000> rs2;
	BitField<0b0111'1110'0000'0000'0000'0000'0000'0000> immediate3;
	BitField<0b1000'0000'0000'0000'0000'0000'0000'0000> immediate4;

	SBType(const uint32_t rawInstruction)
	{
		opcode    .FromRawInstruction(rawInstruction);
		immediate1.FromRawInstruction(rawInstruction);
		immediate2.FromRawInstruction(rawInstruction);
		funct3    .FromRawInstruction(rawInstruction);
		rs1       .FromRawInstruction(rawInstruction);
		rs2       .FromRawInstruction(rawInstruction);
		immediate3.FromRawInstruction(rawInstruction);
		immediate4.FromRawInstruction(rawInstruction);
	}
	SBType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return opcode.GetField()     | 
			   immediate1.GetField() | 
			   immediate2.GetField() | 
			   funct3.GetField()     | 
			   rs1.GetField()        | 
			   rs2.GetField()        | 
			   immediate3.GetField() | 
			   immediate4.GetField();
	}
};

struct UJType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b0000'0000'0000'1111'1111'0000'0000'0000> immediate1;
	BitField<0b0000'0000'0001'0000'0000'0000'0000'0000> immediate2;
	BitField<0b0111'1111'1110'0000'0000'0000'0000'0000> immediate3;
	BitField<0b1000'0000'0000'0000'0000'0000'0000'0000> immediate4;

	UJType(const uint32_t rawInstruction)
	{
		opcode    .FromRawInstruction(rawInstruction);
		rd        .FromRawInstruction(rawInstruction);
		immediate1.FromRawInstruction(rawInstruction);
		immediate2.FromRawInstruction(rawInstruction);
		immediate3.FromRawInstruction(rawInstruction);
		immediate4.FromRawInstruction(rawInstruction);
	}
	UJType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return opcode.GetField()     | 
			   rd.GetField()         | 
			   immediate1.GetField() | 
			   immediate2.GetField() | 
			   immediate3.GetField() | 
			   immediate4.GetField();
	}
};

struct UType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b1111'1111'1111'1111'1111'0000'0000'0000> immediate;

	UType(const uint32_t rawInstruction)
	{
		opcode   .FromRawInstruction(rawInstruction);
		rd       .FromRawInstruction(rawInstruction);
		immediate.FromRawInstruction(rawInstruction);
	}
	UType()
	{ }

	const uint32_t ToRawInstruction() const
	{
		return opcode.GetField() | 
			   rd.GetField()     | 
			   immediate.GetField();
	}
};