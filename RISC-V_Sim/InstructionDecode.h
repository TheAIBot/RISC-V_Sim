#pragma once

#include <cstdint>
#include <string>
#include "Instruction.h"

int32_t SignExtend_uint12_t(int32_t toExtend);
Instruction DecodeInstruction(const uint32_t rawInstruction);
Instruction* DecodeInstructions(const uint32_t* rawInstructions, const uint32_t instructionsCount);
std::string GetProgramAsString(const uint32_t* rawInstructions, const uint32_t instructionCount);