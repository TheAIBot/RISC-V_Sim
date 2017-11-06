#pragma once

#include<cstdint>
#include "Instruction.h"
#include "Register.h"

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

public:
	Processor();
	void Run(const uint32_t* instructions, const uint64_t instructionCount);
	bool RunInstruction(Instruction instruction);
	void Processor::PrintInstructions(const uint32_t* rawInstructions, const uint64_t instructionCount);
	void PrintRegisters();
	void SetDebugMode(const bool useDebugMode);
	bool CompareRegisters(const uint32_t* compareWith);

	~Processor();
};

