#pragma once

#include <cstdint>
#include "Instruction.h"

Instruction* DecodeInstructions(const uint32_t* rawInstructions, const uint64_t instructionsCount);