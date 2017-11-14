#pragma once

#include <cstdint>

struct RType
{
	uint32_t opcode : 7;
	uint32_t rd     : 5;
	uint32_t funct3 : 3;
	uint32_t rs1    : 5;
	uint32_t rs2    : 5;
	uint32_t funct7 : 7;
};
union URType
{
	uint32_t rawInstruction;
	RType type;
};
static_assert(sizeof(RType) == sizeof(uint32_t), "RType isn't 4 bytes long");

struct IType
{
	uint32_t opcode    :  7;
	uint32_t rd        :  5;
	uint32_t funct3    :  3;
	uint32_t rs1       :  5;
	uint32_t immediate : 12;
};
union UIType
{
	uint32_t rawInstruction;
	IType type;
};
static_assert(sizeof(IType) == sizeof(uint32_t), "IType isn't 4 bytes long");

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