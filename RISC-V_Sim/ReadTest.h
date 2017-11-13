#pragma once

#include <cstdint>
#include <string>
#include <memory>

struct Test
{
	const uint32_t* instructions;
	const uint32_t* registers;
	const uint32_t instructionCount;

	Test(const uint32_t* instruc, const uint32_t* regs, const uint32_t instrucCount) : 
		instructions(instruc), 
		registers(regs), 
		instructionCount(instrucCount)
	{ }

	~Test()
	{
		delete[] instructions;
		delete[] registers;
	}
};

std::unique_ptr<Test> LoadTest(const std::string& filePath);