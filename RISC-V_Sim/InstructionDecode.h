#pragma once

#include <cstdint>
#include "Instruction.h"

Instruction DecodeInstruction(const uint32_t rawInstruction);
Instruction* DecodeInstructions(const uint32_t* rawInstructions, const uint64_t instructionsCount);