#pragma once

#include <cstdint>
#include <string>

uint32_t* ReadInstructions(std::string filePath, uint32_t* instructionCount);
uint32_t* ReadRegisters(std::string filePath);