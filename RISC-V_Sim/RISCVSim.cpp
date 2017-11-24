#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Processor.h"
#include "TestEncodeDecode.h"
#include "TestInstructions.h"
#include "ReadTest.h"

std::string sdf(Processor& processor, const uint32_t* Registers)
{
	std::string registerSum = "\nExpected : Actual\n";
	for(uint32_t i = 0; i < 32; i++)
	{
		//don't show stack pointer register
		//as it isn't checked
		if (i == static_cast<uint32_t>(Regs::sp))
		{
			registerSum += "sp 0 : 0";
		}
		else
		{
			registerSum += RegisterName(i);
			registerSum += " ";
			registerSum += std::to_string(Registers[i]);
			registerSum += " : ";
			registerSum += std::to_string(processor.GetRegister(static_cast<Regs>(i)));
		}

		registerSum += "\n";
	}

	return registerSum;
}

void testFile(std::string filePath)
{
	const std::unique_ptr<Test> test = LoadTest(filePath);

	Processor processor;
	processor.SetDebugMode(false);
	processor.Run(test->instructions, test->instructionCount);
	//processor.PrintRegisters();
	//processor.PrintInstructions(test->instructions, test->instructionCount);

	if (!processor.CompareRegisters(test->registers))
	{
		//processor.PrintRegisters();
		std::cout << sdf(processor, test->registers);
		std::cout << "FUCKING FAILED" << std::endl;
	}
	else
	{
		std::cout << "SUCCESS" << std::endl;
	}
}

int main()
{	
	TestAllEncodeDecode();
	TestAllInstructions();
	try
	{
		
		testFile("tests/task1/addlarge");
		testFile("tests/task1/addneg");
		testFile("tests/task1/addpos");
		testFile("tests/task1/shift");

		testFile("tests/task2/branchcnt");
		testFile("tests/task2/branchmany");
		
		//testFile("tests/task3/loop");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		return -1;
	}
	
	std::cin.get();
    return 0;
}

