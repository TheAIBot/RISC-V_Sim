#pragma once

#include <cstdint>
#include <string>
#include "InstructionType.h"

struct Instruction
{
	uint32_t immediate;
	InstructionType type;
	uint8_t rd;
	uint8_t rs1;
	uint8_t rs2;
};

std::string NumberToBits(uint32_t n);
std::string InstructionToBits(uint32_t n);
std::string NumberToBits64(uint64_t n);
std::string InstructionAsString(Instruction instruction);