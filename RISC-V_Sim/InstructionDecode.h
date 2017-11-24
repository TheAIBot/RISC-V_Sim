#pragma once

#include <cstdint>
#include <string>
#include "Instruction.h"

Instruction DecodeInstruction(const uint32_t rawInstruction);
const Instruction* DecodeInstructions(const uint32_t* rawInstructions, const uint32_t instructionsCount);
std::string GetProgramAsString(const uint32_t* rawInstructions, const uint32_t instructionCount);