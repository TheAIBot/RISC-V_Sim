#include "TestInstructions.h"
#include <stdexcept>
#include <iostream>
#include "InstructionEncode.h"
#include "Register.h"
#include "Processor.h"
#include "InstructionDecode.h"
#include "Instruction.h"
#include "RISCV_Program.h"

static void Success()
{
    std::cout << "Test Success!" << std::endl;
}

static void Test_lb()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 102);
	program.AddInstruction(Create_sb(Regs::x0, Regs::s0, 10));
	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 10));
	program.ExpectRegisterValue(Regs::t0, 102);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sb(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lb(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'ff'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sb(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lb(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_lb");

	Success();
}
static void Test_lh()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 13302);
	program.AddInstruction(Create_sh(Regs::x0, Regs::s0, 10));
	program.AddInstruction(Create_lh(Regs::t0, Regs::x0, 10));
	program.ExpectRegisterValue(Regs::t0, 13302);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sh(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lh(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'80'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sh(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lh(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f'4f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_lh");

	Success();
}
static void Test_lw()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1338802);
	program.AddInstruction(Create_sw(Regs::x0, Regs::s0, 10));
	program.AddInstruction(Create_lw(Regs::t0, Regs::x0, 10));
	program.ExpectRegisterValue(Regs::t0, 1338802);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sw(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lw(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0x80'80'80'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sw(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lw(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f'4f'4f'4f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_lw");

	Success();
}
static void Test_lbu()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 102);
	program.AddInstruction(Create_sb(Regs::x0, Regs::s0, 10));
	program.AddInstruction(Create_lbu(Regs::t0, Regs::x0, 10));
	program.ExpectRegisterValue(Regs::t0, 102);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sb(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lbu(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'0080);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sb(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lbu(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_lbu");

	Success();
}
static void Test_lhu()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 13302);
	program.AddInstruction(Create_sh(Regs::x0, Regs::s0, 10));
	program.AddInstruction(Create_lhu(Regs::t0, Regs::x0, 10));
	program.ExpectRegisterValue(Regs::t0, 13302);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sh(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lhu(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'80'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sh(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lhu(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f'4f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_lhu");

	Success();
}
static void Test_fence()
{

}
static void Test_fence_i()
{

}
static void Test_addi()
{
    RISCV_Program program;
    program.AddInstruction(Create_addi(Regs::t1, Regs::x0, 125));
    program.ExpectRegisterValue(Regs::t1, 125);

    program.AddInstruction(Create_addi(Regs::t2, Regs::t1, 35));
    program.ExpectRegisterValue(Regs::t2, 160);

    program.AddInstruction(Create_addi(Regs::t3, Regs::t2, -100));
    program.ExpectRegisterValue(Regs::t3, 60);

	program.EndProgram();
    program.SaveAndTest("InstructionTests/test_addi");

    Success();
}
static void Test_slli()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x0f'00'ff'00);
	program.AddInstruction(Create_slli(Regs::t1, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t1, 0xf0'0f'f0'00);

	program.AddInstruction(Create_slli(Regs::t2, Regs::t0, 16));
	program.ExpectRegisterValue(Regs::t2, 0xff'00'00'00);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_slli");

	Success();
}
static void Test_slti()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 20);
	program.AddInstruction(Create_slti(Regs::t1, Regs::t0, 21));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.AddInstruction(Create_slti(Regs::t2, Regs::t0, 20));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.AddInstruction(Create_slti(Regs::t3, Regs::t0, 19));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.AddInstruction(Create_slti(Regs::t4, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t4, 0);

	program.SetRegister(Regs::t0, -20);
	program.AddInstruction(Create_slti(Regs::t5, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.AddInstruction(Create_slti(Regs::t6, Regs::t0, -20));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.AddInstruction(Create_slti(Regs::s1, Regs::t0, -21));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_slti");

	Success();
}
static void Test_sltiu()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 20);
	program.AddInstruction(Create_sltiu(Regs::t1, Regs::t0, 21));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.AddInstruction(Create_sltiu(Regs::t2, Regs::t0, 20));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.AddInstruction(Create_sltiu(Regs::t3, Regs::t0, 19));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.AddInstruction(Create_sltiu(Regs::t4, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t4, 1);

	program.SetRegister(Regs::t0, -20);
	program.AddInstruction(Create_sltiu(Regs::t5, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.AddInstruction(Create_sltiu(Regs::t6, Regs::t0, -20));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.AddInstruction(Create_sltiu(Regs::s1, Regs::t0, -21));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sltiu");

	Success();
}
static void Test_xori()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x0f'00'ff'f0);
	program.AddInstruction(Create_xori(Regs::t1, Regs::t0, 0x00'00'07'0f));
	program.ExpectRegisterValue(Regs::t1, 0x0f'00'f8'ff);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_xori");

	Success();
}
static void Test_srli()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.AddInstruction(Create_srli(Regs::t1, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t1, 0x0f'0f'f0'0f);

	program.AddInstruction(Create_srli(Regs::t2, Regs::t0, 12));
	program.ExpectRegisterValue(Regs::t2, 0x00'0f'0f'f0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_srli");

	Success();
}
static void Test_srai()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.AddInstruction(Create_srai(Regs::t1, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t1, 0xff'0f'f0'0f);

	program.AddInstruction(Create_srai(Regs::t2, Regs::t0, 12));
	program.ExpectRegisterValue(Regs::t2, 0xff'ff'0f'f0);

	program.SetRegister(Regs::t0, 0x00'f0'ff'f0);
	program.AddInstruction(Create_srai(Regs::t3, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t3, 0x00'0f'0f'ff);

	program.AddInstruction(Create_srai(Regs::t4, Regs::t0, 12));
	program.ExpectRegisterValue(Regs::t4, 0x00'00'0f'0f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_srai");

	Success();
}
static void Test_ori()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x8f'00'ff'f1);
	program.AddInstruction(Create_ori(Regs::t1, Regs::t0, 0x00'00'07'00));
	program.ExpectRegisterValue(Regs::t1, 0x8f'00'ff'f1);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_ori");

	Success();
}
static void Test_andi()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x0f'00'ff'f1);
	program.AddInstruction(Create_andi(Regs::t1, Regs::t0, 0x00'00'07'01));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'07'01);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_andi");

	Success();
}
static void Test_auipc()
{
	RISCV_Program program;
	program.AddInstruction(Create_auipc(Regs::t0, 0x00'00'04'00));
	program.ExpectRegisterValue(Regs::t0, 0x00'00'04'00 << 12);

	program.AddInstruction(Create_auipc(Regs::t1, 0x00'00'04'00));
	program.ExpectRegisterValue(Regs::t1, (0x00'00'04'00 << 12) + 4);

	program.AddInstruction(Create_auipc(Regs::t2, 0x00'07'04'00));
	program.ExpectRegisterValue(Regs::t2, (0x00'07'04'00 << 12) + 8);

	program.AddInstruction(Create_auipc(Regs::t3, 0));
	program.ExpectRegisterValue(Regs::t3, 12);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_auipc");

	Success();
}
static void Test_sb()
{
	//has already been tested in the lb tests
	RISCV_Program program;
	program.SetRegister(Regs::s0, 102);
	program.AddInstruction(Create_sb(Regs::x0, Regs::s0, 10));
	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 10));
	program.ExpectRegisterValue(Regs::t0, 102);

	program.SetRegister(Regs::s2, 102);
	program.SetRegister(Regs::s1, 50);
	program.AddInstruction(Create_sb(Regs::s1, Regs::s2, -23));
	program.AddInstruction(Create_lb(Regs::t1, Regs::s1, -23));
	program.ExpectRegisterValue(Regs::t1, 102);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sb");

	Success();
}
static void Test_sh()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 0xce'2d);
	program.AddInstruction(Create_sh(Regs::x0, Regs::s0, 10));

	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 10));
	program.AddInstruction(Create_lb(Regs::t1, Regs::x0, 11));
	program.ExpectRegisterValue(Regs::t0, 0x2d);
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'ff'ce);

	program.SetRegister(Regs::s2, 10232);
	program.SetRegister(Regs::s1, 50);
	program.AddInstruction(Create_sh(Regs::s1, Regs::s2, -23));
	program.AddInstruction(Create_lh(Regs::t1, Regs::s1, -23));
	program.ExpectRegisterValue(Regs::t1, 10232);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sh");

	Success();
}
static void Test_sw()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 0x3a'74'ce'2d);
	program.AddInstruction(Create_sw(Regs::x0, Regs::s0, 10));

	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 10));
	program.AddInstruction(Create_lb(Regs::t1, Regs::x0, 11));
	program.AddInstruction(Create_lb(Regs::t2, Regs::x0, 12));
	program.AddInstruction(Create_lb(Regs::t3, Regs::x0, 13));
	program.ExpectRegisterValue(Regs::t0, 0x2d);
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'ff'ce);
	program.ExpectRegisterValue(Regs::t2, 0x74);
	program.ExpectRegisterValue(Regs::t3, 0x3a);

	program.AddInstruction(Create_lh(Regs::t4, Regs::x0, 10));
	program.AddInstruction(Create_lh(Regs::t5, Regs::x0, 12));
	program.ExpectRegisterValue(Regs::t4, 0xff'ff'ce'2d);
	program.ExpectRegisterValue(Regs::t5, 0x3a'74);

	program.AddInstruction(Create_lh(Regs::t6, Regs::x0, 11));
	program.ExpectRegisterValue(Regs::t6, 0x74'ce);

	program.SetRegister(Regs::s2, 10232);
	program.SetRegister(Regs::s1, 50);
	program.AddInstruction(Create_sw(Regs::s1, Regs::s2, -23));
	program.AddInstruction(Create_lw(Regs::s3, Regs::s1, -23));
	program.ExpectRegisterValue(Regs::s3, 10232);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sw");

	Success();
}
static void Test_add()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 125);
	program.AddInstruction(Create_add(Regs::t1, Regs::x0, Regs::t0));
	program.ExpectRegisterValue(Regs::t1, 125);

	program.SetRegister(Regs::t0, 35);
	program.AddInstruction(Create_add(Regs::t2, Regs::t1, Regs::t0));
	program.ExpectRegisterValue(Regs::t2, 160);

	program.SetRegister(Regs::t0, -100);
	program.AddInstruction(Create_add(Regs::t3, Regs::t2, Regs::t0));
	program.ExpectRegisterValue(Regs::t3, 60);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_add");

	Success();
}
static void Test_sub()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 125);
	program.AddInstruction(Create_sub(Regs::t1, Regs::x0, Regs::t0));
	program.ExpectRegisterValue(Regs::t1, -125);

	program.SetRegister(Regs::t0, 35);
	program.AddInstruction(Create_sub(Regs::t2, Regs::t1, Regs::t0));
	program.ExpectRegisterValue(Regs::t2, -160);

	program.SetRegister(Regs::t0, -100);
	program.AddInstruction(Create_sub(Regs::t3, Regs::t2, Regs::t0));
	program.ExpectRegisterValue(Regs::t3, -60);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sub");

	Success();
}
static void Test_sll()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x0f'00'ff'00);
	program.SetRegister(Regs::s0, 4);
	program.AddInstruction(Create_sll(Regs::t1, Regs::t0, Regs::s0));
	program.ExpectRegisterValue(Regs::t1, 0xf0'0f'f0'00);

	program.SetRegister(Regs::s0, 16);
	program.AddInstruction(Create_sll(Regs::t2, Regs::t0, Regs::s0));
	program.ExpectRegisterValue(Regs::t2, 0xff'00'00'00);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sll");

	Success();
}
static void Test_slt()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 20);
	program.SetRegister(Regs::a0, 21);
	program.AddInstruction(Create_slt(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.SetRegister(Regs::a0, 20);
	program.AddInstruction(Create_slt(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.SetRegister(Regs::a0, 19);
	program.AddInstruction(Create_slt(Regs::t3, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_slt(Regs::t4, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t4, 0);

	program.SetRegister(Regs::t0, -20);
	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_slt(Regs::t5, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.SetRegister(Regs::a0, -20);
	program.AddInstruction(Create_slt(Regs::t6, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.SetRegister(Regs::a0, -21);
	program.AddInstruction(Create_slt(Regs::s1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_slt");

	Success();
}
static void Test_sltu()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 20);
	program.SetRegister(Regs::a0, 21);
	program.AddInstruction(Create_sltu(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.SetRegister(Regs::a0, 20);
	program.AddInstruction(Create_sltu(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.SetRegister(Regs::a0, 19);
	program.AddInstruction(Create_sltu(Regs::t3, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_sltu(Regs::t4, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t4, 1);

	program.SetRegister(Regs::t0, -20);
	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_sltu(Regs::t5, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.SetRegister(Regs::a0, -20);
	program.AddInstruction(Create_sltu(Regs::t6, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.SetRegister(Regs::a0, -21);
	program.AddInstruction(Create_sltu(Regs::s1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sltu");

	Success();
}
static void Test_xor()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x0f'00'ff'f0);
	program.SetRegister(Regs::t1, 0x00'00'07'0f);
	program.AddInstruction(Create_xor(Regs::t2, Regs::t0, Regs::t1));
	program.ExpectRegisterValue(Regs::t2, 0x0f'00'f8'ff);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_xor");

	Success();
}
static void Test_srl()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.SetRegister(Regs::a0, 4);
	program.AddInstruction(Create_srl(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0x0f'0f'f0'0f);

	program.SetRegister(Regs::a0, 12);
	program.AddInstruction(Create_srl(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0x00'0f'0f'f0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_srl");

	Success();
}
static void Test_sra()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.SetRegister(Regs::a0, 4);
	program.AddInstruction(Create_sra(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0xff'0f'f0'0f);

	program.SetRegister(Regs::a0, 12);
	program.AddInstruction(Create_sra(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0xff'ff'0f'f0);

	program.SetRegister(Regs::t0, 0x00'f0'ff'f0);
	program.SetRegister(Regs::a0, 4);
	program.AddInstruction(Create_sra(Regs::t3, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t3, 0x00'0f'0f'ff);

	program.SetRegister(Regs::a0, 12);
	program.AddInstruction(Create_sra(Regs::t4, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t4, 0x00'00'0f'0f);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_sra");

	Success();
}
static void Test_or()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x8f'00'ff'f1);
	program.SetRegister(Regs::a0, 0x00'00'07'00);
	program.AddInstruction(Create_or(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0x8f'00'ff'f1);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_or");

	Success();
}
static void Test_and()
{
	RISCV_Program program;
	program.SetRegister(Regs::t0, 0x0f'00'ff'f1);
	program.SetRegister(Regs::a0, 0x00'00'07'01);
	program.AddInstruction(Create_and(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'07'01);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_and");

	Success();
}
static void Test_lui()
{
	RISCV_Program program;
	program.AddInstruction(Create_lui(Regs::t0, 0x00'00'04'00));
	program.ExpectRegisterValue(Regs::t0, 0x00'00'04'00 << 12);

	program.AddInstruction(Create_lui(Regs::t1, -64));
	program.ExpectRegisterValue(Regs::t1, -64 << 12);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_lui");

	Success();
}
static void Test_beq()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.ExpectRegisterValue(Regs::s4, 0);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_beq");

	Success();
}
static void Test_bne()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.ExpectRegisterValue(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s4, 1);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_bne");

	Success();
}
static void Test_blt()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s4, 0);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_blt");

	Success();
}
static void Test_bge()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.ExpectRegisterValue(Regs::s4, 1);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_bge");

	Success();
}
static void Test_bltu()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.ExpectRegisterValue(Regs::s4, 1);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_bltu");

	Success();
}
static void Test_bgeu()
{
	RISCV_Program program;
	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s4, 0);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_bgeu");

	Success();
}
static void Test_jalr()
{
	RISCV_Program program;
	program.AddInstruction(Create_jalr(Regs::t0, Regs::x0, 8));
	program.ExpectRegisterValue(Regs::t0, 4);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s0, 1);

	program.SetRegister(Regs::a0, -4);
	program.AddInstruction(Create_jalr(Regs::t1, Regs::a0, 28));
	program.ExpectRegisterValue(Regs::t1, 20);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s1, 1);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_jalr");

	Success();
}
static void Test_jal()
{
	RISCV_Program program;
	program.AddInstruction(Create_jal(Regs::t0, 8));
	program.ExpectRegisterValue(Regs::t0, 4);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s0, 1);

	program.AddInstruction(Create_jal(Regs::t1, 8));
	program.ExpectRegisterValue(Regs::t1, 16);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s1, 1);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_jal");

	Success();
}
static void Test_ecall()
{
	RISCV_Program program;
	program.SetRegister(Regs::a1, 10);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s0, 1);

	program.SetRegister(Regs::a0, 9);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s1, 1);

	program.SetRegister(Regs::a0, 11);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s2, 1);

	program.SetRegister(Regs::a0, 10);
	program.SetRegister(Regs::s3, -1);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s3, -1);

	program.SaveAndTest("InstructionTests/test_ecall");

	Success();
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
	RISCV_Program program;
	program.AddInstruction(Create_li(Regs::s0, 0xff'ff'ff'ff));
	program.ExpectRegisterValue(     Regs::s0, 0xff'ff'ff'ff);

	program.AddInstruction(Create_li(Regs::s1, 29'154'821));
	program.ExpectRegisterValue(     Regs::s1, 29'154'821);

	program.AddInstruction(Create_li(Regs::s2, 2'993'781'092));
	program.ExpectRegisterValue(     Regs::s2, 2'993'781'092);

	program.AddInstruction(Create_li(Regs::s3, -12));
	program.ExpectRegisterValue(     Regs::s3, -12);

	program.AddInstruction(Create_li(Regs::s4, -1'125'213'234));
	program.ExpectRegisterValue(     Regs::s4, -1'125'213'234);

	program.AddInstruction(Create_li(Regs::s5, 0xff'00'00'00));
	program.ExpectRegisterValue(     Regs::s5, 0xff'00'00'00);

	program.SetRegister(Regs::s6, 10);
	program.AddInstruction(Create_li(Regs::s6, 0));
	program.ExpectRegisterValue(     Regs::s6, 0);

	program.EndProgram();
	program.SaveAndTest("InstructionTests/test_li");

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