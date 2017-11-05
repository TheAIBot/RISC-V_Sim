#pragma once

#include <cstdint>

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