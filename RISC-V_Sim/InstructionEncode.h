#pragma once

#include <cstdint>
#include "Register.h"

struct MultiInstruction
{
	uint32_t instruction1;
	uint32_t instruction2;
};

uint32_t Create_lb(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_lh(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_lw(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_lbu(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_lhu(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_fence();
uint32_t Create_fence_i();
uint32_t Create_addi(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_slli(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_slti(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_sltiu(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_xori(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_srli(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_srai(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_ori(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_andi(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_auipc(Regs rd, uint32_t immediate);
uint32_t Create_sb(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_sh(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_sw(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_add(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_sub(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_sll(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_slt(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_sltu(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_xor(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_srl(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_sra(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_or(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_and(Regs rd, Regs rs1, Regs rs2);
uint32_t Create_lui(Regs rd, uint32_t immediate);
uint32_t Create_beq(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_bne(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_blt(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_bge(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_bltu(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_bgeu(Regs rs1, Regs rs2, uint32_t immediate);
uint32_t Create_jalr(Regs rd, Regs rs1, uint32_t immediate);
uint32_t Create_jal(Regs rd, uint32_t immediate);
uint32_t Create_ecall();
uint32_t Create_ebreak();
uint32_t Create_csrrw();
uint32_t Create_csrrs();
uint32_t Create_csrrc();
uint32_t Create_csrrwi();
uint32_t Create_csrrsi();
uint32_t Create_csrrci();
MultiInstruction Create_li(Regs rd, uint32_t immediate);
