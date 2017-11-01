#pragma once

#include <cstdint>

typedef struct
{
	uint32_t immediate;
	uint8_t opcode;
	uint8_t rd;
	uint8_t funct3;
	uint8_t rs1;
	uint8_t rs2;
	uint8_t funct7;
} Instruction;