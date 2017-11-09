#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "InstructionEncode.h"
#include "Register.h"
#include "Processor.h"

class RISCV_Program
{
private:
	std::vector<uint32_t> Instructions;
	uint32_t Registers[32];

	void WrongProgramResult(Processor& processor, const std::string& filepath, bool fromFile);

public:
	RISCV_Program();

	void SetRegister(Regs reg, uint32_t value);
	void ExpectRegisterValue(Regs reg, uint32_t expected);
	void AddInstruction(uint32_t rawInstruction);
	void AddInstruction(MultiInstruction mInstruction);
	void EndProgram();
	void SaveAndTest(const std::string& filepath);
};

