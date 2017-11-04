#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Processor.h"

static uint32_t* ReadInstructions(std::string filename, uint64_t* instructionsCount)
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

	//make sure file can be converted to integer array
	if (fileLength % 4 != 0 || fileLength  == 0)
	{
		fileStream.close();
		throw std::runtime_error("File doesn't have the correct length. Length: " + std::to_string(fileLength));
	}

	//Copy content into char array
	char* fileContent = new char[fileLength];
	fileStream.read(fileContent, fileLength);
		
	//don't need the filestream anymore
	fileStream.close();

	//convert char array into integer array
	uint32_t* rawInstructions = new uint32_t[fileLength / 4];
	for (uint32_t i = 0; i < fileLength; i += 4)
	{
		uint32_t t1 = static_cast<uint32_t>(static_cast<uint8_t>(fileContent[i + 0]));
		uint32_t t2 = static_cast<uint32_t>(static_cast<uint8_t>(fileContent[i + 1]));
		uint32_t t3 = static_cast<uint32_t>(static_cast<uint8_t>(fileContent[i + 2]));
		uint32_t t4 = static_cast<uint32_t>(static_cast<uint8_t>(fileContent[i + 3]));
		rawInstructions[i / 4] = (t1 <<  0) |
								 (t2 <<  8) |
								 (t3 << 16) |
								 (t4 << 24);
	}

	delete[] fileContent;
	*instructionsCount = fileLength / 4;

	return rawInstructions;
}

int main()
{
	uint8_t fish = 129;
	int32_t r = static_cast<int32_t>(static_cast<int8_t>(fish));
	std::cout << NumberToBits(static_cast<uint32_t>(fish)) << std::endl;
	std::cout << NumberToBits(r) << std::endl;

	
	try
	{
		uint64_t instructionCount;
		uint32_t* rawInstructions = ReadInstructions("addlarge.bin", &instructionCount);
	
		Processor processor;
		processor.SetDebugMode(true);
		processor.Run(rawInstructions, instructionCount);
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	
	std::cin.get();
    return 0;
}

