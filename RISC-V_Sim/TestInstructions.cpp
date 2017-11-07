#include "TestInstructions.h"
#include <stdexcept>
#include <iostream>
#include "InstructionEncode.h"
#include "Register.h"
#include "Processor.h"
#include "InstructionDecode.h"
#include "Instruction.h"

static void AssertTrue(bool value)
{
    if (!value)
    {
        throw std::runtime_error("\nValue was not true.\n");
    }
}

static void Success()
{
    std::cout << "Test Success!" << std::endl;
}

static bool RunInstruction(Processor& processor, uint32_t rawInstruction)
{
	Instruction instruction = DecodeInstruction(rawInstruction);
	return processor.RunInstruction(instruction);
}

static bool RunInstruction(Processor& processor, MultiInstruction mInstruction)
{
	RunInstruction(processor, mInstruction.instruction1);
	return RunInstruction(processor, mInstruction.instruction2);
}

static void Test_lb()
{

}
static void Test_lh()
{

}
static void Test_lw()
{

}
static void Test_lbu()
{

}
static void Test_lhu()
{

}
static void Test_fence()
{

}
static void Test_fence_i()
{

}
static void Test_addi()
{
    Processor processor; 
	RunInstruction(processor, Create_addi(Regs::t1, Regs::x0, 125));
    AssertTrue(processor.CompareRegister(Regs::t1, 125));

	RunInstruction(processor, Create_addi(Regs::t2, Regs::t1, 35));
    AssertTrue(processor.CompareRegister(Regs::t2, 160));

	RunInstruction(processor, Create_addi(Regs::t3, Regs::t2, -100));
    AssertTrue(processor.CompareRegister(Regs::t3, 60));

    Success();
}
static void Test_slli()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x0f'00'ff'00);
	RunInstruction(processor, Create_slli(Regs::t1, Regs::t0, 4));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xf0'0f'f0'00));

	RunInstruction(processor, Create_slli(Regs::t1, Regs::t0, 16));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xff'00'00'00));

	Success();
}
static void Test_slti()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 20);
	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, 21));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, 20));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, 19));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, -19));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t0, -20);
	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, -19));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, -20));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	RunInstruction(processor, Create_slti(Regs::t1, Regs::t0, -21));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	Success();
}
static void Test_sltiu()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 20);
	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, 21));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, 20));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, 19));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, -19));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	processor.SetRegister(Regs::t0, -20);
	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, -19));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, -20));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	RunInstruction(processor, Create_sltiu(Regs::t1, Regs::t0, -21));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	Success();
}
static void Test_xori()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x0f'00'ff'f0);
	RunInstruction(processor, Create_xori(Regs::t1, Regs::t0, 0x00'00'07'0f));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x0f'00'f8'ff));

	Success();
}
static void Test_srli()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	RunInstruction(processor, Create_srli(Regs::t1, Regs::t0, 4));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x0f'0f'f0'0f));

	RunInstruction(processor, Create_srli(Regs::t1, Regs::t0, 12));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'0f'0f'f0));

	Success();
}
static void Test_srai()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	RunInstruction(processor, Create_srai(Regs::t1, Regs::t0, 4));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xff'0f'f0'0f));

	RunInstruction(processor, Create_srai(Regs::t1, Regs::t0, 12));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xff'ff'0f'f0));

	processor.SetRegister(Regs::t0, 0x00'f0'ff'f0);
	RunInstruction(processor, Create_srai(Regs::t1, Regs::t0, 4));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'0f'0f'ff));

	RunInstruction(processor, Create_srai(Regs::t1, Regs::t0, 12));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'00'0f'0f));

	Success();
}
static void Test_ori()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x8f'00'ff'f1);
	RunInstruction(processor, Create_ori(Regs::t1, Regs::t0, 0x00'00'07'00));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x8f'00'ff'f1));

	Success();
}
static void Test_andi()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x0f'00'ff'f1);
	RunInstruction(processor, Create_andi(Regs::t1, Regs::t0, 0x00'00'07'01));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'00'07'01));

	Success();
}
static void Test_auipc()
{
	Processor processor;
	RunInstruction(processor, Create_auipc(Regs::t0, 0x00'00'04'00));
	AssertTrue(processor.CompareRegister(Regs::t0,   0x00'00'04'00 << 12));

	processor.SetPC(256 << 12);
	RunInstruction(processor, Create_auipc(Regs::t0, -64));
	AssertTrue(processor.CompareRegister(Regs::t0, 192 << 12));

	Success();
}
static void Test_sb()
{

}
static void Test_sh()
{

}
static void Test_sw()
{

}
static void Test_add()
{
	Processor processor; 
	processor.SetRegister(Regs::t0, 125);
	RunInstruction(processor, Create_add(Regs::t1, Regs::x0, Regs::t0));
	AssertTrue(processor.CompareRegister(Regs::t1, 125));

	processor.SetRegister(Regs::t0, 35);
	RunInstruction(processor, Create_add(Regs::t2, Regs::t1, Regs::t0));
	AssertTrue(processor.CompareRegister(Regs::t2, 160));

	processor.SetRegister(Regs::t0, -100);
	RunInstruction(processor, Create_add(Regs::t3, Regs::t2, Regs::t0));
	AssertTrue(processor.CompareRegister(Regs::t3, 60));

	Success();
}
static void Test_sub()
{
	Processor processor; 
	processor.SetRegister(Regs::t0, 125);
	RunInstruction(processor, Create_sub(Regs::t1, Regs::x0, Regs::t0));
	AssertTrue(processor.CompareRegister(Regs::t1, -125));

	processor.SetRegister(Regs::t0, 35);
	RunInstruction(processor, Create_sub(Regs::t2, Regs::t1, Regs::t0));
	AssertTrue(processor.CompareRegister(Regs::t2, -160));

	processor.SetRegister(Regs::t0, -100);
	RunInstruction(processor, Create_sub(Regs::t3, Regs::t2, Regs::t0));
	AssertTrue(processor.CompareRegister(Regs::t3, -60));

	Success();
}
static void Test_sll()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x0f'00'ff'00);
	processor.SetRegister(Regs::t1, 4);
	RunInstruction(processor, Create_sll(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xf0'0f'f0'00));

	processor.SetRegister(Regs::t1, 16);
	RunInstruction(processor, Create_sll(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xff'00'00'00));

	Success();
}
static void Test_slt()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 20);
	processor.SetRegister(Regs::t1, 21);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	processor.SetRegister(Regs::t1, 20);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t1, 19);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t1, -19);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t0, -20);
	processor.SetRegister(Regs::t1, -19);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	processor.SetRegister(Regs::t1, -20);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t1, -21);
	RunInstruction(processor, Create_slt(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	Success();
}
static void Test_sltu()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 20);
	processor.SetRegister(Regs::t1, 21);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	processor.SetRegister(Regs::t1, 20);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t1, 19);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t1, -19);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	processor.SetRegister(Regs::t0, -20);
	processor.SetRegister(Regs::t1, -19);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 1));

	processor.SetRegister(Regs::t1, -20);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	processor.SetRegister(Regs::t1, -21);
	RunInstruction(processor, Create_sltu(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0));

	Success();
}
static void Test_xor()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x0f'00'ff'f0);
	processor.SetRegister(Regs::t1, 0x00'00'07'0f);
	RunInstruction(processor, Create_xor(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x0f'00'f8'ff));

	Success();
}
static void Test_srl()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	processor.SetRegister(Regs::t1, 4);
	RunInstruction(processor, Create_srl(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x0f'0f'f0'0f));

	processor.SetRegister(Regs::t1, 12);
	RunInstruction(processor, Create_srl(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'0f'0f'f0));

	Success();
}
static void Test_sra()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	processor.SetRegister(Regs::t1, 4);
	RunInstruction(processor, Create_sra(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xff'0f'f0'0f));

	processor.SetRegister(Regs::t1, 12);
	RunInstruction(processor, Create_sra(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0xff'ff'0f'f0));

	processor.SetRegister(Regs::t0, 0x00'f0'ff'f0);
	processor.SetRegister(Regs::t1, 4);
	RunInstruction(processor, Create_sra(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'0f'0f'ff));

	processor.SetRegister(Regs::t1, 12);
	RunInstruction(processor, Create_sra(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'00'0f'0f));

	Success();
}
static void Test_or()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x8f'00'ff'f1);
	processor.SetRegister(Regs::t1, 0x00'00'07'00);
	RunInstruction(processor, Create_or(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x8f'00'ff'f1));

	Success();
}
static void Test_and()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 0x0f'00'ff'f1);
	processor.SetRegister(Regs::t1, 0x00'00'07'01);
	RunInstruction(processor, Create_and(Regs::t1, Regs::t0, Regs::t1));
	AssertTrue(processor.CompareRegister(Regs::t1, 0x00'00'07'01));

	Success();
}
static void Test_lui()
{
	Processor processor;
	RunInstruction(processor, Create_lui(Regs::t0, 0x00'00'04'00));
	AssertTrue(processor.CompareRegister(Regs::t0, 0x00'00'04'00 << 12));

	RunInstruction(processor, Create_lui(Regs::t0, -64));
	AssertTrue(processor.CompareRegister(Regs::t0, -64 << 12));

	Success();
}
static void Test_beq()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_beq(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);
	
	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_beq(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 10);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_beq(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, -5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_beq(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, -10);
	RunInstruction(processor, Create_beq(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	Success();
}
static void Test_bne()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bne(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bne(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 10);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bne(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, -5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bne(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, -10);
	RunInstruction(processor, Create_bne(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	Success();
}
static void Test_blt()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_blt(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_blt(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 10);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_blt(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, -5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_blt(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, -10);
	RunInstruction(processor, Create_blt(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	Success();
}
static void Test_bge()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bge(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bge(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 10);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bge(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, -5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bge(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, -10);
	RunInstruction(processor, Create_bge(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	Success();
}
static void Test_bltu()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bltu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bltu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 10);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bltu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);
	
	processor.SetPC(0);
	processor.SetRegister(Regs::t0, -5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bltu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, -10);
	RunInstruction(processor, Create_bltu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	Success();
}
static void Test_bgeu()
{
	Processor processor;
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bgeu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bgeu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 10);
	processor.SetRegister(Regs::t1, 5);
	RunInstruction(processor, Create_bgeu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, -5);
	processor.SetRegister(Regs::t1, 10);
	RunInstruction(processor, Create_bgeu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 52);

	processor.SetPC(0);
	processor.SetRegister(Regs::t0, 5);
	processor.SetRegister(Regs::t1, -10);
	RunInstruction(processor, Create_bgeu(Regs::t0, Regs::t1, 52));
	AssertTrue(processor.GetPC() == 4);

	Success();
}
static void Test_jalr()
{

}
static void Test_jal()
{

}
static void Test_ecall()
{

}
static void Test_ebreak()
{

}
static void Test_csrrw()
{

}
static void Test_csrrs()
{

}
static void Test_csrrc()
{

}
static void Test_csrrwi()
{

}
static void Test_csrrsi()
{

}
static void Test_csrrci()
{

}
static void Test_li()
{
	Processor processor;
	RunInstruction(processor, Create_li(Regs::t0,  0xff'ff'ff'ff));
	AssertTrue(processor.CompareRegister(Regs::t0, 0xff'ff'ff'ff));

	RunInstruction(processor, Create_li(Regs::t0,  29'154'821));
	AssertTrue(processor.CompareRegister(Regs::t0, 29'154'821));

	RunInstruction(processor, Create_li(Regs::t0,  2'993'781'092));
	AssertTrue(processor.CompareRegister(Regs::t0, 2'993'781'092));

	RunInstruction(processor, Create_li(Regs::t0,  -12));
	AssertTrue(processor.CompareRegister(Regs::t0, -12));

	RunInstruction(processor, Create_li(Regs::t0,  -1'125'213'234));
	AssertTrue(processor.CompareRegister(Regs::t0, -1'125'213'234));

	Success();
}

void TestAllInstructions()
{
	try
	{
		Test_lb();
		Test_lh();
		Test_lw();
		Test_lbu();
		Test_lhu();
		Test_fence();
		Test_fence_i();
		Test_addi();
		Test_slli();
		Test_slti();
		Test_sltiu();
		Test_xori();
		Test_srli();
		Test_srai();
		Test_ori();
		Test_andi();
		Test_auipc();
		Test_sb();
		Test_sh();
		Test_sw();
		Test_add();
		Test_sub();
		Test_sll();
		Test_slt();
		Test_sltu();
		Test_xor();
		Test_srl();
		Test_sra();
		Test_or();
		Test_and();
		Test_lui();
		Test_beq();
		Test_bne();
		Test_blt();
		Test_bge();
		Test_bltu();
		Test_bgeu();
		Test_jalr();
		Test_jal();
		Test_ecall();
		Test_ebreak();
		Test_csrrw();
		Test_csrrs();
		Test_csrrc();
		Test_csrrwi();
		Test_csrrsi();
		Test_csrrci();
		Test_li();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}