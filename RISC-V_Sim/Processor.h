#pragma once

#include<cstdint>
#include "Instruction.h"
#include "Register.h"

class Processor
{
private:
	const static int32_t MEMORY_SIZE = 32768;

	uint32_t pc = 0;
	Register registers[32];
	uint8_t* memory;
	bool debugEnabled = false;

	void VerifyMemorySpace(int32_t index, int32_t size);
	uint8_t  GetByteFromMemory      (int32_t index);
	uint16_t GetHalfWordFromMemory  (int32_t index);
	uint32_t GetWordFromMemory      (int32_t index);
	void StoreByteInMemory      (int32_t index, int8_t  byte      );
	void StoreHalfWordInMemory  (int32_t index, int16_t halfWord  );
	void StoreWordInMemory      (int32_t index, int32_t word      );
	void EnvironmentCall(bool* stopProgram);

public:
	Processor();
	void Run(const uint32_t* instructions, const uint32_t instructionCount);
	bool RunInstruction(Instruction instruction);
	void PrintInstructions(const uint32_t* rawInstructions, const uint32_t instructionCount);
	void PrintRegisters();
	void SetDebugMode(const bool useDebugMode);
	bool CompareRegister(const Regs reg, const uint32_t compareWith);
	bool CompareRegisters(const uint32_t* compareWith);
	void SetRegister(const Regs reg, const int32_t value);
	uint32_t GetPC();
	void SetPC(uint32_t value);

	~Processor();
};

