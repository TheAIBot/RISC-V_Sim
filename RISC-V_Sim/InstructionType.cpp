#include "InstructionType.h"
#include <cstdint>

uint32_t InstructionTypeGetOpCode(InstructionType type)
{
	return static_cast<uint32_t>(type) & 127;
}

uint32_t InstructionTypeFunct3(InstructionType type)
{
	return (static_cast<uint32_t>(type) >> 7) & 7;
}

uint32_t InstructionTypeFunct7(InstructionType type)
{
	return static_cast<uint32_t>(type) >> 10;
}