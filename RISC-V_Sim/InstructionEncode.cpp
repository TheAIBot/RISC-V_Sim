#include "InstructionEncode.h"
#include <cstdint>
#include <stdexcept>
#include "Instruction.h"
#include "InstructionFormat.h"
#include "InstructionType.h"

struct SImmediate
{
	uint32_t immediate1 : 5;
	uint32_t immediate2 : 7;
};
union USImmediate
{
	uint32_t immediate;
	SImmediate splitted;
};

struct SBImmediate
{
	uint32_t : 1;
	uint32_t immediate1 : 4;
	uint32_t immediate2 : 6;
	uint32_t immediate3 : 1;
	uint32_t immediate4 : 1;
};
union USBImmediate
{
	uint32_t immediate;
	SBImmediate splitted;
};

struct UImmediate
{
	uint32_t : 12;
	uint32_t immediate1 : 20;
};
union UUImmediate
{
	uint32_t immediate;
	UImmediate splitted;
};

struct UJImmediate
{
	uint32_t : 1;
	uint32_t immediate1 : 10;
	uint32_t immediate2 :  1;
	uint32_t immediate3 :  8;
	uint32_t immediate4 :  1;
};
union UUJImmediate
{
	uint32_t immediate;
	UJImmediate splitted;
};

static uint32_t EncodeRType(InstructionType type, Regs rd, Regs rs1, Regs rs2)
{
	URType rType = { 0 };
	rType.type.opcode = InstructionTypeGetOpCode(type);
	rType.type.rd = static_cast<uint32_t>(rd);
	rType.type.funct3 = InstructionTypeFunct3(type);
	rType.type.rs1 = static_cast<uint32_t>(rs1);
	rType.type.rs2 = static_cast<uint32_t>(rs2);
	rType.type.funct7 = InstructionTypeFunct7(type);

	return rType.rawInstruction;
}

static uint32_t EncodeIType(InstructionType type, Regs rd, Regs rs1, uint32_t immediate)
{
	UIType iType = { 0 };
	iType.type.opcode = InstructionTypeGetOpCode(type);
	iType.type.rd = static_cast<uint32_t>(rd);
	iType.type.funct3 = InstructionTypeFunct3(type);
	iType.type.rs1 = static_cast<uint32_t>(rs1);
	//if there is something in the funct7 then it has to be added to the
	//instruction as it's needed to identify the instruction.
	//Otherwise use the immediate value given.
	iType.type.immediate = (InstructionTypeFunct7(type) << 5) | immediate;

	return iType.rawInstruction;
}

static uint32_t EncodeSType(InstructionType type, Regs rs1, Regs rs2, uint32_t immediate)
{
	USType sType = { 0 };
	const USImmediate sImmediate = { immediate };
	sType.type.opcode = InstructionTypeGetOpCode(type);
	sType.type.immediate1 = sImmediate.splitted.immediate1;
	sType.type.funct3 = InstructionTypeFunct3(type);
	sType.type.rs1 = static_cast<uint32_t>(rs1);
	sType.type.rs2 = static_cast<uint32_t>(rs2);
	sType.type.immediate2 = sImmediate.splitted.immediate2;

	return sType.rawInstruction;
}

static uint32_t EncodeSBType(InstructionType type, Regs rs1, Regs rs2, uint32_t immediate)
{
	USBType sbType = { 0 };
	const USBImmediate sbImmediate = { immediate };
	sbType.type.opcode = InstructionTypeGetOpCode(type);
	sbType.type.immediate1 = sbImmediate.splitted.immediate3;
	sbType.type.immediate2 = sbImmediate.splitted.immediate1;
	sbType.type.funct3 = InstructionTypeFunct3(type);
	sbType.type.rs1 = static_cast<uint32_t>(rs1);
	sbType.type.rs2 = static_cast<uint32_t>(rs2);
	sbType.type.immediate3 = sbImmediate.splitted.immediate2;
	sbType.type.immediate4 = sbImmediate.splitted.immediate4;

	return sbType.rawInstruction;
}

static uint32_t EncodeUType(InstructionType type, Regs rd, uint32_t immediate)
{
	UUType uType = { 0 };
	UUImmediate uImmediate = { immediate };
	uType.type.opcode = InstructionTypeGetOpCode(type);
	uType.type.rd = static_cast<uint32_t>(rd);
	uType.type.immediate = uImmediate.splitted.immediate1;

	return uType.rawInstruction;
}

static uint32_t EncodeUJType(InstructionType type, Regs rd, uint32_t immediate)
{
	UUJType ujType = { 0 };
	const UUJImmediate ujImmediate = { immediate };
	ujType.type.opcode = InstructionTypeGetOpCode(type);
	ujType.type.rd = static_cast<uint32_t>(rd);
	ujType.type.immediate1 = ujImmediate.splitted.immediate3;
	ujType.type.immediate2 = ujImmediate.splitted.immediate2;
	ujType.type.immediate3 = ujImmediate.splitted.immediate1;
	ujType.type.immediate4 = ujImmediate.splitted.immediate4;

	return ujType.rawInstruction;
}

void VerifyRange(int32_t min, int32_t max, int32_t x)
{
	if (x > max || x < min)
	{
		throw std::runtime_error("\nNumber is not within range.\nMin: " + std::to_string(min) + 
			"\nMax: " + std::to_string(max) + 
			"\nActual: " + std::to_string(x) + "\n");
	}
}

uint32_t Create_lb(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::lb, rd, rs1, immediate);
}
uint32_t Create_lh(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::lh, rd, rs1, immediate);
}
uint32_t Create_lw(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::lw, rd, rs1, immediate);
}
uint32_t Create_ld(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::ld, rd, rs1, immediate);
}
uint32_t Create_lbu(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::lbu, rd, rs1, immediate);
}
uint32_t Create_lhu(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::lhu, rd, rs1, immediate);
}
uint32_t Create_lwu(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::lwu, rd, rs1, immediate);
}
uint32_t Create_fence()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_fence_i()
{
	throw std::runtime_error("Instruction encoding not implemented for this instruction.");
}
uint32_t Create_addi(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::addi, rd, rs1, immediate);
}
uint32_t Create_slli(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::slli, rd, rs1, immediate);
}
uint32_t Create_slti(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::slti, rd, rs1, immediate);
}
uint32_t Create_sltiu(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::sltiu, rd, rs1, immediate);
}
uint32_t Create_xori(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::xori, rd, rs1, immediate);
}
uint32_t Create_srli(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::srli, rd, rs1, immediate);
}
uint32_t Create_srai(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::srai, rd, rs1, immediate);
}
uint32_t Create_ori(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::ori, rd, rs1, immediate);
}
uint32_t Create_andi(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::andi, rd, rs1, immediate);
}
uint32_t Create_auipc(Regs rd, uint32_t immediate)
{
	VerifyRange(-524288, 524287, immediate);
	return EncodeUType(InstructionType::auipc, rd, immediate << 12);
}
uint32_t Create_addiw(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::addiw, rd, rs1, immediate);
}
uint32_t Create_slliw(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::slliw, rd, rs1, immediate);
}
uint32_t Create_srliw(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::srliw, rd, rs1, immediate);
}
uint32_t Create_sraiw(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(0, 32, immediate);
	return EncodeIType(InstructionType::sraiw, rd, rs1, immediate);
}
uint32_t Create_sb(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeSType(InstructionType::sb, rs1, rs2, immediate);
}
uint32_t Create_sh(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeSType(InstructionType::sh, rs1, rs2, immediate);
}
uint32_t Create_sw(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeSType(InstructionType::sw, rs1, rs2, immediate);
}
uint32_t Create_sd(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeSType(InstructionType::sd, rs1, rs2, immediate);
}
uint32_t Create_add(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::add, rd, rs1, rs2);
}
uint32_t Create_sub(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::sub, rd, rs1, rs2);
}
uint32_t Create_sll(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::sll, rd, rs1, rs2);
}
uint32_t Create_slt(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::slt, rd, rs1, rs2);
}
uint32_t Create_sltu(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::sltu, rd, rs1, rs2);
}
uint32_t Create_xor(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::xor_, rd, rs1, rs2);
}
uint32_t Create_srl(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::srl, rd, rs1, rs2);
}
uint32_t Create_sra(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::sra, rd, rs1, rs2);
}
uint32_t Create_or(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::or_, rd, rs1, rs2);
}
uint32_t Create_and(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::and_, rd, rs1, rs2);
}
uint32_t Create_lui(Regs rd, uint32_t immediate)
{
	return EncodeUType(InstructionType::lui, rd, immediate << 12);
}
uint32_t Create_addw(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::addw, rd, rs1, rs2);
}
uint32_t Create_subw(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::subw, rd, rs1, rs2);
}
uint32_t Create_sllw(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::sllw, rd, rs1, rs2);
}
uint32_t Create_srlw(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::srlw, rd, rs1, rs2);
}
uint32_t Create_sraw(Regs rd, Regs rs1, Regs rs2)
{
	return EncodeRType(InstructionType::sraw, rd, rs1, rs2);
}
uint32_t Create_beq(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2047, 2046, immediate);
	return EncodeSBType(InstructionType::beq, rs1, rs2, immediate);
}
uint32_t Create_bne(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2047, 2046, immediate);
	return EncodeSBType(InstructionType::bne, rs1, rs2, immediate);
}
uint32_t Create_blt(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2047, 2046, immediate);
	return EncodeSBType(InstructionType::blt, rs1, rs2, immediate);
}
uint32_t Create_bge(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2047, 2046, immediate);
	return EncodeSBType(InstructionType::bge, rs1, rs2, immediate);
}
uint32_t Create_bltu(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2047, 2046, immediate);
	return EncodeSBType(InstructionType::bltu, rs1, rs2, immediate);
}
uint32_t Create_bgeu(Regs rs1, Regs rs2, uint32_t immediate)
{
	VerifyRange(-2047, 2046, immediate);
	return EncodeSBType(InstructionType::bgeu, rs1, rs2, immediate);
}
uint32_t Create_jalr(Regs rd, Regs rs1, uint32_t immediate)
{
	VerifyRange(-2048, 2047, immediate);
	return EncodeIType(InstructionType::jalr, rd, rs1, immediate);
}
uint32_t Create_jal(Regs rd, uint32_t immediate)
{
	VerifyRange(-524288, 524287, immediate);
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
