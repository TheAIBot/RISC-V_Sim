#include "InstructionEncode.h"
#include <cstdint>
#include <stdexcept>
#include "Instruction.h"
#include "InstructionFormat.h"
#include "InstructionType.h"
#include "InstructionDecode.h"
#include "ImmediateFormat.h"


static uint32_t EncodeRType(const InstructionType type, const Regs rd, const Regs rs1, const Regs rs2)
{
	RType rType;
	rType.opcode.FromInt(InstructionTypeGetOpCode(type));
	rType.rd    .FromInt(static_cast<uint32_t>(rd));
	rType.funct3.FromInt(InstructionTypeFunct3(type));
	rType.rs1   .FromInt(static_cast<uint32_t>(rs1));
	rType.rs2   .FromInt(static_cast<uint32_t>(rs2));
	rType.funct7.FromInt(InstructionTypeFunct7(type));

	return rType.ToRawInstruction();
}

static uint32_t EncodeIType(const InstructionType type, const Regs rd, const Regs rs1, const uint32_t immediate)
{
	IType iType;
	iType.opcode.FromInt(InstructionTypeGetOpCode(type));
	iType.rd    .FromInt(static_cast<uint32_t>(rd));
	iType.funct3.FromInt(InstructionTypeFunct3(type));
	iType.rs1   .FromInt(static_cast<uint32_t>(rs1));
	//if there is something in the funct7 then it has to be added to the
	//instruction as it's needed to identify the instruction.
	//Otherwise use the immediate value given.
	iType.immediate.FromInt((InstructionTypeFunct7(type) << 5) | immediate);

	return iType.ToRawInstruction();
}

static uint32_t EncodeSType(const InstructionType type, const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	SType sType = { 0 };
	const SImmediate sImmediate(immediate);
	sType.opcode    .FromInt(InstructionTypeGetOpCode(type));
	sType.immediate1.FromInt(sImmediate.immediate1.GetAsInt());
	sType.funct3    .FromInt(InstructionTypeFunct3(type));
	sType.rs1       .FromInt(static_cast<uint32_t>(rs1));
	sType.rs2       .FromInt(static_cast<uint32_t>(rs2));
	sType.immediate2.FromInt(sImmediate.immediate2.GetAsInt());

	return sType.ToRawInstruction();
}

static uint32_t EncodeSBType(const InstructionType type, const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	SBType sbType = { 0 };
	const SBImmediate sbImmediate(immediate);
	sbType.opcode.FromInt(InstructionTypeGetOpCode(type));
	sbType.immediate1.FromInt(sbImmediate.immediate3.GetAsInt());
	sbType.immediate2.FromInt(sbImmediate.immediate1.GetAsInt());
	sbType.funct3    .FromInt(InstructionTypeFunct3(type));
	sbType.rs1       .FromInt(static_cast<uint32_t>(rs1));
	sbType.rs2       .FromInt(static_cast<uint32_t>(rs2));
	sbType.immediate3.FromInt(sbImmediate.immediate2.GetAsInt());
	sbType.immediate4.FromInt(sbImmediate.immediate4.GetAsInt());

	return sbType.ToRawInstruction();
}

static uint32_t EncodeUJType(const InstructionType type, const Regs rd, const uint32_t immediate)
{
	UJType ujType = { 0 };
	const UJImmediate ujImmediate(immediate);
	ujType.opcode    .FromInt(InstructionTypeGetOpCode(type));
	ujType.rd        .FromInt(static_cast<uint32_t>(rd));
	ujType.immediate1.FromInt(ujImmediate.immediate3.GetAsInt());
	ujType.immediate2.FromInt(ujImmediate.immediate2.GetAsInt());
	ujType.immediate3.FromInt(ujImmediate.immediate1.GetAsInt());
	ujType.immediate4.FromInt(ujImmediate.immediate4.GetAsInt());

	return ujType.ToRawInstruction();
}

static uint32_t EncodeUType(const InstructionType type, const Regs rd, const uint32_t immediate)
{
	UType uType = { 0 };
	const UImmediate uImmediate = { immediate };
	uType.opcode   .FromInt(InstructionTypeGetOpCode(type));
	uType.rd       .FromInt(static_cast<uint32_t>(rd));
	uType.immediate.FromInt(uImmediate.immediate1.GetAsInt());

	return uType.ToRawInstruction();
}

static void VerifyRange(const int32_t min, const int32_t max, const int32_t x)
{
	if (x > max || x < min)
	{
		throw std::runtime_error("\nNumber is not within range.\nMin: " + std::to_string(min) + 
			"\nMax: " + std::to_string(max) + 
			"\nActual: " + std::to_string(x) + "\n");
	}
}

uint32_t Create_lb(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::lb, rd, rs1, immediate);
}
uint32_t Create_lh(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::lh, rd, rs1, immediate);
}
uint32_t Create_lw(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::lw, rd, rs1, immediate);
}
uint32_t Create_lbu(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::lbu, rd, rs1, immediate);
}
uint32_t Create_lhu(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::lhu, rd, rs1, immediate);
}
uint32_t Create_fence()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_fence_i()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_addi(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::addi, rd, rs1, immediate);
}
uint32_t Create_slli(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::slli, rd, rs1, immediate);
}
uint32_t Create_slti(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::slti, rd, rs1, immediate);
}
uint32_t Create_sltiu(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::sltiu, rd, rs1, immediate);
}
uint32_t Create_xori(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::xori, rd, rs1, immediate);
}
uint32_t Create_srli(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::srli, rd, rs1, immediate);
}
uint32_t Create_srai(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::srai, rd, rs1, immediate);
}
uint32_t Create_ori(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::ori, rd, rs1, immediate);
}
uint32_t Create_andi(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::andi, rd, rs1, immediate);
}
uint32_t Create_auipc(const Regs rd, const uint32_t immediate)
{
	VerifyRange(0, 1048575, immediate);
	return EncodeUType(InstructionType::auipc, rd, immediate << 12);
}
uint32_t Create_sb(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeSType(InstructionType::sb, rs1, rs2, immediate);
}
uint32_t Create_sh(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeSType(InstructionType::sh, rs1, rs2, immediate);
}
uint32_t Create_sw(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeSType(InstructionType::sw, rs1, rs2, immediate);
}
uint32_t Create_add(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::add, rd, rs1, rs2);
}
uint32_t Create_sub(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::sub, rd, rs1, rs2);
}
uint32_t Create_sll(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::sll, rd, rs1, rs2);
}
uint32_t Create_slt(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::slt, rd, rs1, rs2);
}
uint32_t Create_sltu(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::sltu, rd, rs1, rs2);
}
uint32_t Create_xor(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::xor_, rd, rs1, rs2);
}
uint32_t Create_srl(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::srl, rd, rs1, rs2);
}
uint32_t Create_sra(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::sra, rd, rs1, rs2);
}
uint32_t Create_or(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::or_, rd, rs1, rs2);
}
uint32_t Create_and(const Regs rd, const Regs rs1, const Regs rs2)
{
	return EncodeRType(InstructionType::and_, rd, rs1, rs2);
}
uint32_t Create_lui(const Regs rd, const uint32_t immediate)
{
	return EncodeUType(InstructionType::lui, rd, immediate << 12);
}
uint32_t Create_beq(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2047, 4095, immediate);
	return EncodeSBType(InstructionType::beq, rs1, rs2, immediate);
}
uint32_t Create_bne(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2047, 4095, immediate);
	return EncodeSBType(InstructionType::bne, rs1, rs2, immediate);
}
uint32_t Create_blt(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2047, 4095, immediate);
	return EncodeSBType(InstructionType::blt, rs1, rs2, immediate);
}
uint32_t Create_bge(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2047, 4095, immediate);
	return EncodeSBType(InstructionType::bge, rs1, rs2, immediate);
}
uint32_t Create_bltu(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2047, 4095, immediate);
	return EncodeSBType(InstructionType::bltu, rs1, rs2, immediate);
}
uint32_t Create_bgeu(const Regs rs1, const Regs rs2, const uint32_t immediate)
{
	VerifyRange(-2047, 4095, immediate);
	return EncodeSBType(InstructionType::bgeu, rs1, rs2, immediate);
}
uint32_t Create_jalr(const Regs rd, const Regs rs1, const uint32_t immediate)
{
	VerifyRange(-2048, 4095, immediate);
	return EncodeIType(InstructionType::jalr, rd, rs1, immediate);
}
uint32_t Create_jal(const Regs rd, const uint32_t immediate)
{
	VerifyRange(-524288, 1048575, immediate);
	return EncodeUJType(InstructionType::jal, rd, immediate);
}
uint32_t Create_ecall()
{
	return EncodeIType(InstructionType::ecall, Regs::x0, Regs::x0, 0);
}
uint32_t Create_ebreak()
{
	return EncodeIType(InstructionType::ebreak, Regs::x0, Regs::x0, 0);
}
uint32_t Create_csrrw()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_csrrs()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_csrrc()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_csrrwi()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_csrrsi()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_csrrci()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
MultiInstruction Create_li(const Regs rd, const uint32_t immediate)
{
	const uint32_t addiImmediate = SignExtend<12>(immediate & 0x0f'ff);
	const uint32_t leftover = immediate - addiImmediate;

	MultiInstruction mInstruction;
	if (addiImmediate != 0 &&
		leftover != 0)
	{
		mInstruction.instruction1 = Create_lui(rd, leftover >> 12);
		mInstruction.instruction2 = Create_addi(rd, rd, addiImmediate & 0x0f'ff);
	}
	else if (addiImmediate != 0 &&
			 leftover == 0)
	{
		mInstruction.instruction1 = 0;
		//Here add with x0 to make sure to override the whole register
		mInstruction.instruction2 = Create_addi(rd, Regs::x0, addiImmediate & 0x0f'ff);
	}
	else if (addiImmediate == 0 &&
			 leftover != 0)
	{
		mInstruction.instruction1 = Create_lui(rd, leftover >> 12);
		mInstruction.instruction2 = 0;
	}
	else
	{
		mInstruction.instruction1 = 0;
		//load zero for some reason, so just set register to zero
		mInstruction.instruction2 = Create_addi(rd, Regs::x0, 0);
	}

	return mInstruction;
}