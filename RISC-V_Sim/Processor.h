#pragma once

#include<cstdint>
#include "Instruction.h"

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

class Processor
{
private:
	const static int64_t MEMORY_SIZE = 32768;

	uint64_t pc = 0;
	Register registers[32];
	uint8_t* memory;
	bool debugEnabled = false;

	void VerifyMemorySpace(int64_t index, int64_t size);
	uint8_t  GetByteFromMemory      (int64_t index);
	uint16_t GetHalfWordFromMemory  (int64_t index);
	uint32_t GetWordFromMemory      (int64_t index);
	uint64_t GetDoubleWordFromMemory(int64_t index);
	void StoreByteInMemory      (int64_t index, int8_t  byte      );
	void StoreHalfWordInMemory  (int64_t index, int16_t halfWord  );
	void StoreWordInMemory      (int64_t index, int32_t word      );
	void StoreDoubleWordInMemory(int64_t index, int64_t doubleWord);
	void EnvironmentCall(bool* stopProgram);
	void RunInstruction(Instruction instruction, bool* stopProgram);
	void PrintRegisters();

public:
	Processor();
	void Run(uint32_t* instructions, uint64_t instructionCount);
	void SetDebugMode(bool useDebugMode);

	~Processor();
};

