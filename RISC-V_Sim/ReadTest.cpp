#include "ReadTest.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <memory>

static const char* ReadFileContent(const std::string filename, uint64_t* fileSize)
{
	std::ifstream fileStream(filename, std::ios::binary | std::ios::ate);
	if (!fileStream)
	{
		throw std::runtime_error("Failed to open file: " + std::string(filename));
	}

	//get file length
	fileStream.seekg(0, fileStream.end);
	const uint64_t fileLength = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);

	//Copy content into char array
	char* fileContent = new char[fileLength];
	fileStream.read(fileContent, fileLength);

	//don't need the filestream anymore
	fileStream.close();

	*fileSize = fileLength;
	return fileContent;
}

static uint32_t* char_to_uint32_t(const char* chars, const uint64_t fileSize)
{
	uint32_t* uints = new uint32_t[fileSize / 4];
	for (uint32_t i = 0; i < fileSize; i += 4)
	{
		const uint32_t t1 = static_cast<uint32_t>(static_cast<uint8_t>(chars[i + 0]));
		const uint32_t t2 = static_cast<uint32_t>(static_cast<uint8_t>(chars[i + 1]));
		const uint32_t t3 = static_cast<uint32_t>(static_cast<uint8_t>(chars[i + 2]));
		const uint32_t t4 = static_cast<uint32_t>(static_cast<uint8_t>(chars[i + 3]));
		uints[i / 4] = (t1 <<  0) |
			(t2 <<  8) |
			(t3 << 16) |
			(t4 << 24);
	}
	return uints;
}

const uint32_t* ReadInstructions(const std::string& filePath, uint32_t* instructionCount)
{
	const std::string instructionsFile = filePath + ".bin";
	uint64_t fileSize;
	const char* fileContent = ReadFileContent(instructionsFile, &fileSize);

	//make sure file can be converted to integer array
	if (fileSize % 4 != 0 || fileSize  == 0)
	{
		throw std::runtime_error("File doesn't have the correct length. Length: " + std::to_string(fileSize));
	}

	const uint32_t* instructions = char_to_uint32_t(fileContent, fileSize);
	delete[] fileContent;

	*instructionCount = static_cast<uint32_t>(fileSize / 4);
	return instructions;
}

const uint32_t* ReadRegisters(const std::string& filePath)
{
	const std::string registerFile = filePath + ".res";
	uint64_t fileSize;
	const char* fileContent = ReadFileContent(registerFile, &fileSize);

	//have read exactly 32 word registers
	if (fileSize != 4 * 32)
	{
		throw std::runtime_error("File doesn't have the correct length. Length: " + std::to_string(fileSize));
	}

	const uint32_t* registers = char_to_uint32_t(fileContent, fileSize);
	delete[] fileContent;

	return registers;
}

std::unique_ptr<Test> LoadTest(const std::string& filePath)
{
	uint32_t instructionCount;
	const uint32_t* rawInstructions = ReadInstructions(filePath, &instructionCount);
	const uint32_t* registers = ReadRegisters(filePath);

	return std::make_unique<Test>(rawInstructions, registers, instructionCount);
}