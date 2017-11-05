#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Processor.h"

static char* ReadFileContent(std::string filename, uint64_t* fileSize)
{
	std::ifstream fileStream(filename, std::ios::binary | std::ios::ate);
	if (!fileStream)
	{
		throw new std::runtime_error("Failed to open file: " + std::string(filename));
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

uint32_t* char_to_uint32_t(char* chars, uint64_t fileSize)
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
uint64_t* char_to_uint64_t(char* chars, uint64_t fileSize)
{
	uint64_t* uints = new uint64_t[fileSize / 8];
	for (uint64_t i = 0; i < fileSize; i += 8)
	{
		const uint64_t t1 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 0]));
		const uint64_t t2 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 1]));
		const uint64_t t3 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 2]));
		const uint64_t t4 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 3]));
		const uint64_t t5 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 4]));
		const uint64_t t6 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 5]));
		const uint64_t t7 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 6]));
		const uint64_t t8 = static_cast<uint64_t>(static_cast<uint8_t>(chars[i + 7]));
		uints[i / 8] = (t1 <<  0) |
					   (t2 <<  8) |
					   (t3 << 16) |
					   (t4 << 24) |
					   (t1 << 32) |
					   (t2 << 40) |
					   (t3 << 48) |
					   (t4 << 56);
	}

	return uints;
}

uint32_t* ReadInstructions(std::string filePath, uint64_t* instructionCount)
{
	std::string instructionsFile = filePath + ".bin";
	uint64_t fileSize;
	char* fileContent = ReadFileContent(instructionsFile, &fileSize);

	//make sure file can be converted to integer array
	if (fileSize % 4 != 0 || fileSize  == 0)
	{
		throw std::runtime_error("File doesn't have the correct length. Length: " + std::to_string(fileSize));
	}

	uint32_t* instructions = char_to_uint32_t(fileContent, fileSize);
	delete[] fileContent;

	*instructionCount = fileSize / 4;
	return instructions;
}

uint32_t* ReadRegisters(std::string filePath)
{
	std::string registerFile = filePath + ".res";
	uint64_t fileSize;
	char* fileContent = ReadFileContent(registerFile, &fileSize);

	//have read exactly 32 double word registers
	if (fileSize != 4 * 32)
	{
		throw std::runtime_error("File doesn't have the correct length. Length: " + std::to_string(fileSize));
	}

	uint32_t* registers = char_to_uint32_t(fileContent, fileSize);
	delete[] fileContent;

	return registers;
}

void testFile(std::string filePath)
{
	uint64_t instructionCount;
	const uint32_t* rawInstructions = ReadInstructions(filePath, &instructionCount);
	const uint32_t* registers = ReadRegisters(filePath);

	Processor processor;
	processor.SetDebugMode(false);
	processor.Run(rawInstructions, instructionCount);
	//processor.PrintRegisters();
	//processor.PrintInstructions(rawInstructions, instructionCount);

	if (!processor.CompareRegisters(registers))
	{
		std::cout << "FUCKING FAILED" << std::endl;
	}
	else
	{
		std::cout << "SUCCESS" << std::endl;
	}

	delete[] rawInstructions;
	delete[] registers;
}

int main()
{	
	try
	{
		testFile("tests/task1/addlarge");
		testFile("tests/task1/addneg");
		testFile("tests/task1/addpos");
		//testFile("tests/task1/shift");

		testFile("tests/task2/branchcnt");
		testFile("tests/task2/branchmany");

		//testFile("tests/task3/loop");
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		return -1;
	}
	
	std::cin.get();
    return 0;
}

