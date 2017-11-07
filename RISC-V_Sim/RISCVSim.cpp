#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include "Processor.h"
#include "TestEncodeDecode.h"
#include "TestInstructions.h"
#include "ReadTest.h"

void testFile(std::string filePath)
{
	uint32_t instructionCount;
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
	//TestAllEncodeDecode();
	TestAllInstructions();
	try
	{
		/*
		testFile("tests/task1/addlarge");
		testFile("tests/task1/addneg");
		testFile("tests/task1/addpos");
		testFile("tests/task1/shift");

		testFile("tests/task2/branchcnt");
		testFile("tests/task2/branchmany");
		*/
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

