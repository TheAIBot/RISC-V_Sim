#pragma once

#include <cstdint>
#include <string>

union Register
{
	int8_t byte;
	uint8_t ubyte;
	int16_t half;
	uint16_t uhalf;
	int32_t word;
	uint32_t uword;
	int64_t dword;
	uint64_t udword;
};

std::string RegisterName(uint32_t registerIndex);