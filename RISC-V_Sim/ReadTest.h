#pragma once

#include <cstdint>
#include <string>

const uint32_t* ReadInstructions(const std::string& filePath, uint32_t* instructionCount);
const uint32_t* ReadRegisters(const std::string& filePath);