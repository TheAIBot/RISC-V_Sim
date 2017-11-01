#pragma once
#include<cstdint>

class Processor
{
private:
	uint64_t pc = 0;
	uint64_t registers[32];
	uint64_t memory[32768];

public:
	Processor();
	void Run(uint32_t* instructions);


	~Processor();
};

