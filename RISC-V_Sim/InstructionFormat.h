#pragma once

#include <cstdint>
#include "BitField.h"

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
		opcode.FromField(rawInstruction);
		rd    .FromField(rawInstruction);
		funct3.FromField(rawInstruction);
		rs1   .FromField(rawInstruction);
		rs2   .FromField(rawInstruction);
		funct7.FromField(rawInstruction);
	}
	RType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode.GetField() | 
			   rd    .GetField() | 
			   funct3.GetField() | 
			   rs1   .GetField() | 
			   rs2   .GetField() | 
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
		opcode   .FromField(rawInstruction);
		rd       .FromField(rawInstruction);
		funct3   .FromField(rawInstruction);
		rs1      .FromField(rawInstruction);
		immediate.FromField(rawInstruction);
	}
	IType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode   .GetField() | 
			   rd       .GetField() | 
			   funct3   .GetField() | 
			   rs1      .GetField() | 
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
		opcode    .FromField(rawInstruction);
		immediate1.FromField(rawInstruction);
		funct3    .FromField(rawInstruction);
		rs1       .FromField(rawInstruction);
		rs2       .FromField(rawInstruction);
		immediate2.FromField(rawInstruction);
	}
	SType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode    .GetField() | 
			   immediate1.GetField() | 
			   funct3    .GetField() | 
			   rs1       .GetField() | 
			   rs2       .GetField() | 
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
		opcode    .FromField(rawInstruction);
		immediate1.FromField(rawInstruction);
		immediate2.FromField(rawInstruction);
		funct3    .FromField(rawInstruction);
		rs1       .FromField(rawInstruction);
		rs2       .FromField(rawInstruction);
		immediate3.FromField(rawInstruction);
		immediate4.FromField(rawInstruction);
	}
	SBType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode    .GetField() | 
			   immediate1.GetField() | 
			   immediate2.GetField() | 
			   funct3    .GetField() | 
			   rs1       .GetField() | 
			   rs2       .GetField() | 
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
		opcode    .FromField(rawInstruction);
		rd        .FromField(rawInstruction);
		immediate1.FromField(rawInstruction);
		immediate2.FromField(rawInstruction);
		immediate3.FromField(rawInstruction);
		immediate4.FromField(rawInstruction);
	}
	UJType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode    .GetField() | 
			   rd        .GetField() | 
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
		opcode   .FromField(rawInstruction);
		rd       .FromField(rawInstruction);
		immediate.FromField(rawInstruction);
	}
	UType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode   .GetField() | 
			   rd       .GetField() | 
			   immediate.GetField();
	}
};