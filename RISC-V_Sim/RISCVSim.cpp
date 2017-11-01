#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

static uint32_t* ReadInstructions(char const* filename, uint64_t* instructionsCount)
{
	std::ifstream fileStream(filename, std::ios::binary | std::ios::ate);
	if (fileStream)
	{
		//get file length
		fileStream.seekg(0, fileStream.end);
		const uint64_t fileLength = fileStream.tellg();
		fileStream.seekg(0, fileStream.beg);

		//make sure file can be converted to integer array
		if (fileLength % 4 != 0)
		{
			fileStream.close();
			throw std::runtime_error("File doesn't have the correct length. Length: " + std::to_string(fileLength));
		}

		//Copy content into char array
		char* fileContent = new char[fileLength];
		fileStream.read(fileContent, fileLength);
		
		//don't need the filestream anymore
		fileStream.close();

		//convert to char array into an integer array
		uint32_t* rawInstructions = new uint32_t[fileLength / 4];
		for (uint32_t i = 0; i < fileLength; i += 4)
		{
			rawInstructions[i / 4] = (fileContent[i + 0] << 24) |
									 (fileContent[i + 1] << 16) |
									 (fileContent[i + 2] <<  8) |
									 (fileContent[i + 3] <<  0);
		}

		delete[] fileContent;
		*instructionsCount = fileLength / 4;

		return rawInstructions;
	}

}

int main()
{
	uint64_t instructionCount;
	uint32_t* rawInstructions = ReadInstructions("", &instructionCount);

	//std::cout << sizeof(RType) << std::endl;
	std::cin.get();
    return 0;
}

