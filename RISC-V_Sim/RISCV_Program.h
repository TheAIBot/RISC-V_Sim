#pragma once

#include <cstdint>
#include "InstructionEncode.h"

class RISCV_Program
{
public:
	RISCV_Program();

	void AddInstruction(uint32_t rawInstruction);
	void AddInstruction(MultiInstruction mInstruction);

	~RISCV_Program();
};

