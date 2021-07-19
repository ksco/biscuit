#include <biscuit/assert.hpp>
#include <biscuit/assembler.hpp>

namespace biscuit {
namespace {

enum class AddressingMode : uint32_t {
    // clang-format off
    UnitStride       = 0b00,
    IndexedUnordered = 0b01,
    Strided          = 0b10,
    IndexedOrdered   = 0b11,
    // clang-format on
};

enum class UnitStrideLoadAddressingMode : uint32_t {
    // clang-format off
    Load               = 0b00000,
    MaskLoad           = 0b01011,
    LoadFaultOnlyFirst = 0b10000,
    // clang-format on
};

enum class UnitStrideStoreAddressingMode : uint32_t {
    // clang-format off
    Store     = 0b00000,
    MaskStore = 0b01011,
    // clang-format on
};

enum class WidthEncoding : uint32_t {
    // clang-format off
    E8  = 0b000,
    E16 = 0b101,
    E32 = 0b110,
    E64 = 0b111,
    // clang-format on
};

void EmitVectorLoadImpl(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                        VecMask vm, uint32_t lumop, GPR rs, WidthEncoding width, Vec vd) noexcept {
    BISCUIT_ASSERT(nf <= 8);

    // Fit to encoding space. Allows for being more explicit about the size in calling functions
    // (e.g. using 8 for 8 elements instead of 7).
    if (nf != 0) {
        nf -= 1;
    }

    // clang-format off
    const auto value = (nf << 29) |
                       (static_cast<uint32_t>(mew) << 28) |
                       (static_cast<uint32_t>(mop) << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (lumop << 20) |
                       (rs.Index() << 15) |
                       (static_cast<uint32_t>(width) << 12) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b111);
}

void EmitVectorLoad(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                    VecMask vm, UnitStrideLoadAddressingMode lumop, GPR rs,
                    WidthEncoding width, Vec vd) noexcept {
    EmitVectorLoadImpl(buffer, nf, mew, mop, vm, static_cast<uint32_t>(lumop), rs, width, vd);
}

void EmitVectorLoad(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                    VecMask vm, GPR rs2, GPR rs1, WidthEncoding width, Vec vd) noexcept {
    EmitVectorLoadImpl(buffer, nf, mew, mop, vm, rs2.Index(), rs1, width, vd);
}

void EmitVectorLoad(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                    VecMask vm, Vec vs2, GPR rs1, WidthEncoding width, Vec vd) noexcept {
    EmitVectorLoadImpl(buffer, nf, mew, mop, vm, vs2.Index(), rs1, width, vd);
}

void EmitVectorLoadWholeReg(CodeBuffer& buffer, uint32_t nf, bool mew, GPR rs,
                            WidthEncoding width, Vec vd) noexcept {
    // RISC-V V extension spec (as of 1.0RC) only allows these nf values.
    BISCUIT_ASSERT(nf == 1 || nf == 2 || nf == 4 || nf == 8);

    EmitVectorLoadImpl(buffer, nf, mew, AddressingMode::UnitStride,
                       VecMask::No, 0b01000, rs, width, vd);
}

void EmitVectorStoreImpl(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                         VecMask vm, uint32_t sumop, GPR rs, WidthEncoding width, Vec vd) noexcept {
    BISCUIT_ASSERT(nf <= 8);

    // Fit to encoding space. Allows for being more explicit about the size in calling functions
    // (e.g. using 8 for 8 elements instead of 7).
    if (nf != 0) {
        nf -= 1;
    }

    // clang-format off
    const auto value = (nf << 29) |
                       (static_cast<uint32_t>(mew) << 28) |
                       (static_cast<uint32_t>(mop) << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (sumop << 20) |
                       (rs.Index() << 15) |
                       (static_cast<uint32_t>(width) << 12) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b100111);
}

void EmitVectorStore(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                     VecMask vm, UnitStrideStoreAddressingMode lumop, GPR rs,
                     WidthEncoding width, Vec vs) noexcept {
    EmitVectorStoreImpl(buffer, nf, mew, mop, vm, static_cast<uint32_t>(lumop), rs, width, vs);
}

void EmitVectorStore(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                     VecMask vm, GPR rs2, GPR rs1, WidthEncoding width, Vec vs3) noexcept {
    EmitVectorStoreImpl(buffer, nf, mew, mop, vm, rs2.Index(), rs1, width, vs3);
}

void EmitVectorStore(CodeBuffer& buffer, uint32_t nf, bool mew, AddressingMode mop,
                     VecMask vm, Vec vs2, GPR rs1, WidthEncoding width, Vec vs3) noexcept {
    EmitVectorStoreImpl(buffer, nf, mew, mop, vm, vs2.Index(), rs1, width, vs3);
}

void EmitVectorStoreWholeReg(CodeBuffer& buffer, uint32_t nf, GPR rs, Vec vs) noexcept {
    // RISC-V V extension spec (as of 1.0RC) only allows these nf values.
    BISCUIT_ASSERT(nf == 1 || nf == 2 || nf == 4 || nf == 8);

    EmitVectorStoreImpl(buffer, nf, false, AddressingMode::UnitStride, VecMask::No,
                        0b01000, rs, WidthEncoding::E8, vs);
}

void EmitVectorOPIVIImpl(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, uint32_t imm5, Vec vd) noexcept {
    // clang-format off
    const auto value = (funct6 << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (vs2.Index() << 20) |
                       ((imm5 & 0b11111) << 15) |
                       (0b011U << 12) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b1010111);
}

void EmitVectorOPIVI(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, int32_t simm5, Vec vd) noexcept {
    BISCUIT_ASSERT(simm5 >= -16 && simm5 <= 15);
    EmitVectorOPIVIImpl(buffer, funct6, vm, vs2, static_cast<uint32_t>(simm5), vd);
}

void EmitVectorOPIVUI(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, uint32_t uimm5, Vec vd) noexcept {
    BISCUIT_ASSERT(uimm5 <= 31);
    EmitVectorOPIVIImpl(buffer, funct6, vm, vs2, uimm5, vd);
}

void EmitVectorOPIVV(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, Vec vs1, Vec vd) noexcept {
    // clang-format off
    const auto value = (funct6 << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (vs2.Index() << 20) |
                       (vs1.Index() << 15) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b1010111);
}

void EmitVectorOPIVX(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, GPR rs1, Vec vd) noexcept {
    // clang-format off
    const auto value = (funct6 << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (vs2.Index() << 20) |
                       (rs1.Index() << 15) |
                       (0b100U << 12) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b1010111);
}

void EmitVectorOPMVV(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, Vec vs1, Vec vd) noexcept {
    // clang-format off
    const auto value = (funct6 << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (vs2.Index() << 20) |
                       (vs1.Index() << 15) |
                       (0b010U << 12) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b1010111);
}

void EmitVectorOPMVX(CodeBuffer& buffer, uint32_t funct6, VecMask vm, Vec vs2, GPR rs1, Vec vd) noexcept {
    // clang-format off
    const auto value = (funct6 << 26) |
                       (static_cast<uint32_t>(vm) << 25) |
                       (vs2.Index() << 20) |
                       (rs1.Index() << 15) |
                       (0b110U << 12) |
                       (vd.Index() << 7);
    // clang-format on

    buffer.Emit32(value | 0b1010111);
}
} // Anonymous namespace

// Vector Integer Arithmetic Instructions

void Assembler::VAADD(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b001001, mask, vs2, vs1, vd);
}

void Assembler::VAADD(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPMVX(m_buffer, 0b001001, mask, vs2, rs1, vd);
}

void Assembler::VAADDU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b001000, mask, vs2, vs1, vd);
}

void Assembler::VAADDU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPMVX(m_buffer, 0b001000, mask, vs2, rs1, vd);
}

void Assembler::VADC(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPIVV(m_buffer, 0b010000, VecMask::Yes, vs2, vs1, vd);
}

void Assembler::VADC(Vec vd, Vec vs2, GPR rs1) noexcept {
    EmitVectorOPIVX(m_buffer, 0b010000, VecMask::Yes, vs2, rs1, vd);
}

void Assembler::VADC(Vec vd, Vec vs2, int32_t simm) noexcept {
    EmitVectorOPIVI(m_buffer, 0b010000, VecMask::Yes, vs2, simm, vd);
}

void Assembler::VADD(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b000000, mask, vs2, vs1, vd);
}

void Assembler::VADD(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000000, mask, vs2, rs1, vd);
}

void Assembler::VADD(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b000000, mask, vs2, simm, vd);
}

void Assembler::VAND(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b001001, mask, vs2, vs1, vd);
}

void Assembler::VAND(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b001001, mask, vs2, rs1, vd);
}

void Assembler::VAND(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b001001, mask, vs2, simm, vd);
}

void Assembler::VASUB(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b001011, mask, vs2, vs1, vd);
}

void Assembler::VASUB(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPMVX(m_buffer, 0b001011, mask, vs2, rs1, vd);
}

void Assembler::VASUBU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b001010, mask, vs2, vs1, vd);
}

void Assembler::VASUBU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPMVX(m_buffer, 0b001010, mask, vs2, rs1, vd);
}

void Assembler::VCOMPRESS(Vec vd, Vec vs2, Vec vs1) noexcept {
    // Note: Destination register may not overlap any of the source registers,
    //       as per the RVV spec (as of 1.0RC; see section 16.5)
    EmitVectorOPMVV(m_buffer, 0b010111, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMADC(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b010001, mask, vs2, vs1, vd);
}

void Assembler::VMADC(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b010001, mask, vs2, rs1, vd);
}

void Assembler::VMADC(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b010001, mask, vs2, simm, vd);
}

void Assembler::VMAND(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011001, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMANDNOT(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011000, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMNAND(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011101, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMNOR(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011110, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMOR(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011010, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMORNOT(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011100, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMXNOR(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011111, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMXOR(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPMVV(m_buffer, 0b011011, VecMask::No, vs2, vs1, vd);
}

void Assembler::VMAX(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b000111, mask, vs2, vs1, vd);
}

void Assembler::VMAX(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000111, mask, vs2, rs1, vd);
}

void Assembler::VMAXU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b000110, mask, vs2, vs1, vd);
}

void Assembler::VMAXU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000110, mask, vs2, rs1, vd);
}

void Assembler::VMERGE(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPIVV(m_buffer, 0b010111, VecMask::Yes, vs2, vs1, vd);
}

void Assembler::VMERGE(Vec vd, Vec vs2, GPR rs1) noexcept {
    EmitVectorOPIVX(m_buffer, 0b010111, VecMask::Yes, vs2, rs1, vd);
}

void Assembler::VMERGE(Vec vd, Vec vs2, int32_t simm) noexcept {
    EmitVectorOPIVI(m_buffer, 0b010111, VecMask::Yes, vs2, simm, vd);
}

void Assembler::VMIN(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b000101, mask, vs2, vs1, vd);
}

void Assembler::VMIN(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000101, mask, vs2, rs1, vd);
}

void Assembler::VMINU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b000100, mask, vs2, vs1, vd);
}

void Assembler::VMINU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000100, mask, vs2, rs1, vd);
}

void Assembler::VMSBC(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b010011, mask, vs2, vs1, vd);
}

void Assembler::VMSBC(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b010011, mask, vs2, rs1, vd);
}

void Assembler::VMSEQ(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b011000, mask, vs2, vs1, vd);
}

void Assembler::VMSEQ(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011000, mask, vs2, rs1, vd);
}

void Assembler::VMSEQ(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b011000, mask, vs2, simm, vd);
}

void Assembler::VMSGT(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011111, mask, vs2, rs1, vd);
}

void Assembler::VMSGT(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b011111, mask, vs2, simm, vd);
}

void Assembler::VMSGTU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011110, mask, vs2, rs1, vd);
}

void Assembler::VMSGTU(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b011110, mask, vs2, simm, vd);
}

void Assembler::VMSLE(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b011101, mask, vs2, vs1, vd);
}

void Assembler::VMSLE(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011101, mask, vs2, rs1, vd);
}

void Assembler::VMSLE(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b011101, mask, vs2, simm, vd);
}

void Assembler::VMSLEU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b011100, mask, vs2, vs1, vd);
}

void Assembler::VMSLEU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011100, mask, vs2, rs1, vd);
}

void Assembler::VMSLEU(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b011100, mask, vs2, simm, vd);
}

void Assembler::VMSLT(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b011011, mask, vs2, vs1, vd);
}

void Assembler::VMSLT(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011011, mask, vs2, rs1, vd);
}

void Assembler::VMSLTU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b011010, mask, vs2, vs1, vd);
}

void Assembler::VMSLTU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011010, mask, vs2, rs1, vd);
}

void Assembler::VMSNE(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b011001, mask, vs2, vs1, vd);
}

void Assembler::VMSNE(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b011001, mask, vs2, rs1, vd);
}

void Assembler::VMSNE(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b011001, mask, vs2, simm, vd);
}

void Assembler::VMV(Vec vd, Vec vs1) noexcept {
    EmitVectorOPIVV(m_buffer, 0b010111, VecMask::No, v0, vs1, vd);
}

void Assembler::VMV(Vec vd, GPR rs1) noexcept {
    EmitVectorOPIVX(m_buffer, 0b010111, VecMask::No, v0, rs1, vd);
}

void Assembler::VMV(Vec vd, int32_t simm) noexcept {
    EmitVectorOPIVI(m_buffer, 0b010111, VecMask::No, v0, simm, vd);
}

void Assembler::VMV1R(Vec vd, Vec vs) noexcept {
    EmitVectorOPIVI(m_buffer, 0b100111, VecMask::No, vs, 0b00000, vd);
}

void Assembler::VMV2R(Vec vd, Vec vs) noexcept {
    // Registers must be aligned to the register group size, per the
    // RVV spec (as of 1.0RC)
    BISCUIT_ASSERT(vd.Index() % 2 == 0);
    BISCUIT_ASSERT(vs.Index() % 2 == 0);

    EmitVectorOPIVI(m_buffer, 0b100111, VecMask::No, vs, 0b00001, vd);
}

void Assembler::VMV4R(Vec vd, Vec vs) noexcept {
    // Registers must be aligned to the register group size, per the
    // RVV spec (as of 1.0RC)
    BISCUIT_ASSERT(vd.Index() % 4 == 0);
    BISCUIT_ASSERT(vs.Index() % 4 == 0);

    EmitVectorOPIVI(m_buffer, 0b100111, VecMask::No, vs, 0b00011, vd);
}

void Assembler::VMV8R(Vec vd, Vec vs) noexcept {
    // Registers must be aligned to the register group size, per the
    // RVV spec (as of 1.0RC)
    BISCUIT_ASSERT(vd.Index() % 8 == 0);
    BISCUIT_ASSERT(vs.Index() % 8 == 0);

    EmitVectorOPIVI(m_buffer, 0b100111, VecMask::No, vs, 0b00111, vd);
}

void Assembler::VNCLIP(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101111, mask, vs2, vs1, vd);
}

void Assembler::VNCLIP(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101111, mask, vs2, rs1, vd);
}

void Assembler::VNCLIP(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101111, mask, vs2, uimm, vd);
}

void Assembler::VNCLIPU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101110, mask, vs2, vs1, vd);
}

void Assembler::VNCLIPU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101110, mask, vs2, rs1, vd);
}

void Assembler::VNCLIPU(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101110, mask, vs2, uimm, vd);
}

void Assembler::VNSRA(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101101, mask, vs2, vs1, vd);
}

void Assembler::VNSRA(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101101, mask, vs2, rs1, vd);
}

void Assembler::VNSRA(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101101, mask, vs2, uimm, vd);
}

void Assembler::VNSRL(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101100, mask, vs2, vs1, vd);
}

void Assembler::VNSRL(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101100, mask, vs2, rs1, vd);
}

void Assembler::VNSRL(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101100, mask, vs2, uimm, vd);
}

void Assembler::VOR(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b001010, mask, vs2, vs1, vd);
}

void Assembler::VOR(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b001010, mask, vs2, rs1, vd);
}

void Assembler::VOR(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b001010, mask, vs2, simm, vd);
}

void Assembler::VREDAND(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000001, mask, vs2, vs1, vd);
}

void Assembler::VREDMAX(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000111, mask, vs2, vs1, vd);
}

void Assembler::VREDMAXU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000110, mask, vs2, vs1, vd);
}

void Assembler::VREDMIN(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000101, mask, vs2, vs1, vd);
}

void Assembler::VREDMINU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000100, mask, vs2, vs1, vd);
}

void Assembler::VREDOR(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000010, mask, vs2, vs1, vd);
}

void Assembler::VREDSUM(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000000, mask, vs2, vs1, vd);
}

void Assembler::VREDXOR(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPMVV(m_buffer, 0b000011, mask, vs2, vs1, vd);
}

void Assembler::VRGATHER(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b001100, mask, vs2, vs1, vd);
}

void Assembler::VRGATHER(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b001100, mask, vs2, rs1, vd);
}

void Assembler::VRGATHER(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b001100, mask, vs2, static_cast<int32_t>(uimm), vd);
}

void Assembler::VRGATHEREI16(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b001110, mask, vs2, vs1, vd);
}

void Assembler::VRSUB(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000011, mask, vs2, rs1, vd);
}

void Assembler::VRSUB(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b000011, mask, vs2, simm, vd);
}

void Assembler::VSADD(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b100001, mask, vs2, vs1, vd);
}

void Assembler::VSADD(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b100001, mask, vs2, rs1, vd);
}

void Assembler::VSADD(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b100001, mask, vs2, simm, vd);
}

void Assembler::VSADDU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b100000, mask, vs2, vs1, vd);
}

void Assembler::VSADDU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b100000, mask, vs2, rs1, vd);
}

void Assembler::VSADDU(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b100000, mask, vs2, simm, vd);
}

void Assembler::VSBC(Vec vd, Vec vs2, Vec vs1) noexcept {
    EmitVectorOPIVV(m_buffer, 0b010010, VecMask::Yes, vs2, vs1, vd);
}

void Assembler::VSBC(Vec vd, Vec vs2, GPR rs1) noexcept {
    EmitVectorOPIVX(m_buffer, 0b010010, VecMask::Yes, vs2, rs1, vd);
}

void Assembler::VSLIDE1DOWN(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPMVX(m_buffer, 0b001111, mask, vs2, rs1, vd);
}

void Assembler::VSLIDEDOWN(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b001111, mask, vs2, rs1, vd);
}

void Assembler::VSLIDEDOWN(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b001111, mask, vs2, uimm, vd);
}

void Assembler::VSLIDE1UP(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPMVX(m_buffer, 0b001110, mask, vs2, rs1, vd);
}

void Assembler::VSLIDEUP(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b001110, mask, vs2, rs1, vd);
}

void Assembler::VSLIDEUP(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b001110, mask, vs2, uimm, vd);
}

void Assembler::VSLL(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b100101, mask, vs2, vs1, vd);
}

void Assembler::VSLL(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b100101, mask, vs2, rs1, vd);
}

void Assembler::VSLL(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b100101, mask, vs2, uimm, vd);
}

void Assembler::VSMUL(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b100111, mask, vs2, vs1, vd);
}

void Assembler::VSMUL(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b100111, mask, vs2, rs1, vd);
}

void Assembler::VSRA(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101001, mask, vs2, vs1, vd);
}

void Assembler::VSRA(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101001, mask, vs2, rs1, vd);
}

void Assembler::VSRA(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101001, mask, vs2, uimm, vd);
}

void Assembler::VSRL(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101000, mask, vs2, vs1, vd);
}

void Assembler::VSRL(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101000, mask, vs2, rs1, vd);
}

void Assembler::VSRL(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101000, mask, vs2, uimm, vd);
}

void Assembler::VSSRA(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101011, mask, vs2, vs1, vd);
}

void Assembler::VSSRA(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101011, mask, vs2, rs1, vd);
}

void Assembler::VSSRA(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101011, mask, vs2, uimm, vd);
}

void Assembler::VSSRL(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b101010, mask, vs2, vs1, vd);
}

void Assembler::VSSRL(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b101010, mask, vs2, rs1, vd);
}

void Assembler::VSSRL(Vec vd, Vec vs2, uint32_t uimm, VecMask mask) noexcept {
    EmitVectorOPIVUI(m_buffer, 0b101010, mask, vs2, uimm, vd);
}

void Assembler::VSSUB(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b100011, mask, vs2, vs1, vd);
}

void Assembler::VSSUB(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b100011, mask, vs2, rs1, vd);
}

void Assembler::VSSUBU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b100010, mask, vs2, vs1, vd);
}

void Assembler::VSSUBU(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b100010, mask, vs2, rs1, vd);
}

void Assembler::VSUB(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b000010, mask, vs2, vs1, vd);
}

void Assembler::VSUB(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b000010, mask, vs2, rs1, vd);
}

void Assembler::VWREDSUM(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b110001, mask, vs2, vs1, vd);
}

void Assembler::VWREDSUMU(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b110000, mask, vs2, vs1, vd);
}

void Assembler::VXOR(Vec vd, Vec vs2, Vec vs1, VecMask mask) noexcept {
    EmitVectorOPIVV(m_buffer, 0b001011, mask, vs2, vs1, vd);
}

void Assembler::VXOR(Vec vd, Vec vs2, GPR rs1, VecMask mask) noexcept {
    EmitVectorOPIVX(m_buffer, 0b001011, mask, vs2, rs1, vd);
}

void Assembler::VXOR(Vec vd, Vec vs2, int32_t simm, VecMask mask) noexcept {
    EmitVectorOPIVI(m_buffer, 0b001011, mask, vs2, simm, vd);
}

// Vector Load/Store Instructions

void Assembler::VLE8(Vec vd, GPR rs, VecMask mask) noexcept {
    VLSEGE8(1, vd, rs, mask);
}

void Assembler::VLE16(Vec vd, GPR rs, VecMask mask) noexcept {
    VLSEGE16(1, vd, rs, mask);
}

void Assembler::VLE32(Vec vd, GPR rs, VecMask mask) noexcept {
    VLSEGE32(1, vd, rs, mask);
}

void Assembler::VLE64(Vec vd, GPR rs, VecMask mask) noexcept {
    VLSEGE64(1, vd, rs, mask);
}

void Assembler::VLM(Vec vd, GPR rs) noexcept {
    EmitVectorLoad(m_buffer, 0b000, false, AddressingMode::UnitStride, VecMask::No,
                   UnitStrideLoadAddressingMode::MaskLoad, rs, WidthEncoding::E8, vd);
}

void Assembler::VLSE8(Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VLSSEGE8(1, vd, rs1, rs2, mask);
}

void Assembler::VLSE16(Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VLSSEGE16(1, vd, rs1, rs2, mask);
}

void Assembler::VLSE32(Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VLSSEGE32(1, vd, rs1, rs2, mask);
}

void Assembler::VLSE64(Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VLSSEGE64(1, vd, rs1, rs2, mask);
}

void Assembler::VLOXEI8(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLOXSEGEI8(1, vd, rs, vs, mask);
}

void Assembler::VLOXEI16(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLOXSEGEI16(1, vd, rs, vs, mask);
}

void Assembler::VLOXEI32(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLOXSEGEI32(1, vd, rs, vs, mask);
}

void Assembler::VLOXEI64(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLOXSEGEI64(1, vd, rs, vs, mask);
}

void Assembler::VLUXEI8(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLUXSEGEI8(1, vd, rs, vs, mask);
}

void Assembler::VLUXEI16(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLUXSEGEI16(1, vd, rs, vs, mask);
}

void Assembler::VLUXEI32(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLUXSEGEI32(1, vd, rs, vs, mask);
}

void Assembler::VLUXEI64(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VLUXSEGEI64(1, vd, rs, vs, mask);
}

void Assembler::VLE8FF(Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, 0b000, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::LoadFaultOnlyFirst, rs, WidthEncoding::E8, vd);
}

void Assembler::VLE16FF(Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, 0b000, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::LoadFaultOnlyFirst, rs, WidthEncoding::E16, vd);
}

void Assembler::VLE32FF(Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, 0b000, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::LoadFaultOnlyFirst, rs, WidthEncoding::E32, vd);
}

void Assembler::VLE64FF(Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, 0b000, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::LoadFaultOnlyFirst, rs, WidthEncoding::E64, vd);
}

void Assembler::VLSEGE8(uint32_t num_segments, Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::Load, rs, WidthEncoding::E8, vd);
}

void Assembler::VLSEGE16(uint32_t num_segments, Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::Load, rs, WidthEncoding::E16, vd);
}

void Assembler::VLSEGE32(uint32_t num_segments, Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::Load, rs, WidthEncoding::E32, vd);
}

void Assembler::VLSEGE64(uint32_t num_segments, Vec vd, GPR rs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                   UnitStrideLoadAddressingMode::Load, rs, WidthEncoding::E64, vd);
}

void Assembler::VLSSEGE8(uint32_t num_segments, Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                   rs2, rs1, WidthEncoding::E8, vd);
}

void Assembler::VLSSEGE16(uint32_t num_segments, Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                   rs2, rs1, WidthEncoding::E16, vd);
}

void Assembler::VLSSEGE32(uint32_t num_segments, Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                   rs2, rs1, WidthEncoding::E32, vd);
}

void Assembler::VLSSEGE64(uint32_t num_segments, Vec vd, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                   rs2, rs1, WidthEncoding::E64, vd);
}

void Assembler::VLOXSEGEI8(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
                   vs, rs, WidthEncoding::E8, vd);
}

void Assembler::VLOXSEGEI16(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
                   vs, rs, WidthEncoding::E16, vd);
}

void Assembler::VLOXSEGEI32(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
                   vs, rs, WidthEncoding::E32, vd);
}

void Assembler::VLOXSEGEI64(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
                   vs, rs, WidthEncoding::E64, vd);
}

void Assembler::VLUXSEGEI8(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                   vs, rs, WidthEncoding::E8, vd);
}

void Assembler::VLUXSEGEI16(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                   vs, rs, WidthEncoding::E16, vd);
}

void Assembler::VLUXSEGEI32(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                   vs, rs, WidthEncoding::E32, vd);
}

void Assembler::VLUXSEGEI64(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorLoad(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                   vs, rs, WidthEncoding::E64, vd);
}

void Assembler::VLRE8(uint32_t num_registers, Vec vd, GPR rs) noexcept {
    BISCUIT_ASSERT(vd.Index() % num_registers == 0);
    EmitVectorLoadWholeReg(m_buffer, num_registers, false, rs, WidthEncoding::E8, vd);
}

void Assembler::VL1RE8(Vec vd, GPR rs) noexcept {
    VLRE8(1, vd, rs);
}

void Assembler::VL2RE8(Vec vd, GPR rs) noexcept {
    VLRE8(2, vd, rs);
}

void Assembler::VL4RE8(Vec vd, GPR rs) noexcept {
    VLRE8(4, vd, rs);
}

void Assembler::VL8RE8(Vec vd, GPR rs) noexcept {
    VLRE8(8, vd, rs);
}

void Assembler::VLRE16(uint32_t num_registers, Vec vd, GPR rs) noexcept {
    BISCUIT_ASSERT(vd.Index() % num_registers == 0);
    EmitVectorLoadWholeReg(m_buffer, num_registers, false, rs, WidthEncoding::E16, vd);
}

void Assembler::VL1RE16(Vec vd, GPR rs) noexcept {
    VLRE16(1, vd, rs);
}

void Assembler::VL2RE16(Vec vd, GPR rs) noexcept {
    VLRE16(2, vd, rs);
}

void Assembler::VL4RE16(Vec vd, GPR rs) noexcept {
    VLRE16(4, vd, rs);
}

void Assembler::VL8RE16(Vec vd, GPR rs) noexcept {
    VLRE16(8, vd, rs);
}

void Assembler::VLRE32(uint32_t num_registers, Vec vd, GPR rs) noexcept {
    BISCUIT_ASSERT(vd.Index() % num_registers == 0);
    EmitVectorLoadWholeReg(m_buffer, num_registers, false, rs, WidthEncoding::E32, vd);
}

void Assembler::VL1RE32(Vec vd, GPR rs) noexcept {
    VLRE32(1, vd, rs);
}

void Assembler::VL2RE32(Vec vd, GPR rs) noexcept {
    VLRE32(2, vd, rs);
}

void Assembler::VL4RE32(Vec vd, GPR rs) noexcept {
    VLRE32(4, vd, rs);
}

void Assembler::VL8RE32(Vec vd, GPR rs) noexcept {
    VLRE32(8, vd, rs);
}

void Assembler::VLRE64(uint32_t num_registers, Vec vd, GPR rs) noexcept {
    BISCUIT_ASSERT(vd.Index() % num_registers == 0);
    EmitVectorLoadWholeReg(m_buffer, num_registers, false, rs, WidthEncoding::E64, vd);
}

void Assembler::VL1RE64(Vec vd, GPR rs) noexcept {
    VLRE64(1, vd, rs);
}

void Assembler::VL2RE64(Vec vd, GPR rs) noexcept {
    VLRE64(2, vd, rs);
}

void Assembler::VL4RE64(Vec vd, GPR rs) noexcept {
    VLRE64(4, vd, rs);
}

void Assembler::VL8RE64(Vec vd, GPR rs) noexcept {
    VLRE64(8, vd, rs);
}

void Assembler::VSE8(Vec vs, GPR rs, VecMask mask) noexcept {
    VSSEGE8(1, vs, rs, mask);
}

void Assembler::VSE16(Vec vs, GPR rs, VecMask mask) noexcept {
    VSSEGE16(1, vs, rs, mask);
}

void Assembler::VSE32(Vec vs, GPR rs, VecMask mask) noexcept {
    VSSEGE32(1, vs, rs, mask);
}

void Assembler::VSE64(Vec vs, GPR rs, VecMask mask) noexcept {
    VSSEGE64(1, vs, rs, mask);
}

void Assembler::VSM(Vec vs, GPR rs) noexcept {
    EmitVectorStore(m_buffer, 0b000, false, AddressingMode::UnitStride, VecMask::No,
                    UnitStrideStoreAddressingMode::MaskStore, rs, WidthEncoding::E8, vs);
}

void Assembler::VSSE8(Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VSSSEGE8(1, vs, rs1, rs2, mask);
}

void Assembler::VSSE16(Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VSSSEGE16(1, vs, rs1, rs2, mask);
}

void Assembler::VSSE32(Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VSSSEGE32(1, vs, rs1, rs2, mask);
}

void Assembler::VSSE64(Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    VSSSEGE64(1, vs, rs1, rs2, mask);
}

void Assembler::VSOXEI8(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSOXSEGEI8(1, vd, rs, vs, mask);
}

void Assembler::VSOXEI16(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSOXSEGEI16(1, vd, rs, vs, mask);
}

void Assembler::VSOXEI32(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSOXSEGEI32(1, vd, rs, vs, mask);
}

void Assembler::VSOXEI64(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSOXSEGEI64(1, vd, rs, vs, mask);
}

void Assembler::VSUXEI8(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSUXSEGEI8(1, vd, rs, vs, mask);
}

void Assembler::VSUXEI16(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSUXSEGEI16(1, vd, rs, vs, mask);
}

void Assembler::VSUXEI32(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSUXSEGEI32(1, vd, rs, vs, mask);
}

void Assembler::VSUXEI64(Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    VSUXSEGEI64(1, vd, rs, vs, mask);
}

void Assembler::VSSEGE8(uint32_t num_segments, Vec vs, GPR rs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                    UnitStrideStoreAddressingMode::Store, rs, WidthEncoding::E8, vs);
}

void Assembler::VSSEGE16(uint32_t num_segments, Vec vs, GPR rs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                    UnitStrideStoreAddressingMode::Store, rs, WidthEncoding::E16, vs);
}

void Assembler::VSSEGE32(uint32_t num_segments, Vec vs, GPR rs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                    UnitStrideStoreAddressingMode::Store, rs, WidthEncoding::E32, vs);
}

void Assembler::VSSEGE64(uint32_t num_segments, Vec vs, GPR rs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::UnitStride, mask,
                    UnitStrideStoreAddressingMode::Store, rs, WidthEncoding::E64, vs);
}

void Assembler::VSSSEGE8(uint32_t num_segments, Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                    rs2, rs1, WidthEncoding::E8, vs);
}

void Assembler::VSSSEGE16(uint32_t num_segments, Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                    rs2, rs1, WidthEncoding::E16, vs);
}

void Assembler::VSSSEGE32(uint32_t num_segments, Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                    rs2, rs1, WidthEncoding::E32, vs);
}

void Assembler::VSSSEGE64(uint32_t num_segments, Vec vs, GPR rs1, GPR rs2, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::Strided, mask,
                    rs2, rs1, WidthEncoding::E64, vs);
}

void Assembler::VSOXSEGEI8(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
        vs, rs, WidthEncoding::E8, vd);
}

void Assembler::VSOXSEGEI16(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
        vs, rs, WidthEncoding::E16, vd);
}

void Assembler::VSOXSEGEI32(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
        vs, rs, WidthEncoding::E32, vd);
}

void Assembler::VSOXSEGEI64(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedOrdered, mask,
        vs, rs, WidthEncoding::E64, vd);
}

void Assembler::VSUXSEGEI8(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                    vs, rs, WidthEncoding::E8, vd);
}

void Assembler::VSUXSEGEI16(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                    vs, rs, WidthEncoding::E16, vd);
}

void Assembler::VSUXSEGEI32(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                    vs, rs, WidthEncoding::E32, vd);
}

void Assembler::VSUXSEGEI64(uint32_t num_segments, Vec vd, GPR rs, Vec vs, VecMask mask) noexcept {
    EmitVectorStore(m_buffer, num_segments, false, AddressingMode::IndexedUnordered, mask,
                    vs, rs, WidthEncoding::E64, vd);
}

void Assembler::VSR(uint32_t num_registers, Vec vs, GPR rs) noexcept {
    EmitVectorStoreWholeReg(m_buffer, num_registers, rs, vs);
}

void Assembler::VS1R(Vec vs, GPR rs) noexcept {
    VSR(1, vs, rs);
}

void Assembler::VS2R(Vec vs, GPR rs) noexcept {
    BISCUIT_ASSERT(vs.Index() % 2 == 0);
    VSR(2, vs, rs);
}

void Assembler::VS4R(Vec vs, GPR rs) noexcept {
    BISCUIT_ASSERT(vs.Index() % 4 == 0);
    VSR(4, vs, rs);
}

void Assembler::VS8R(Vec vs, GPR rs) noexcept {
    BISCUIT_ASSERT(vs.Index() % 8 == 0);
    VSR(8, vs, rs);
}

void Assembler::VSETIVLI(GPR rd, uint32_t imm, SEW sew, LMUL lmul, VTA vta, VMA vma) noexcept {
    imm &= 0b11111;

    // clang-format off
    const auto zimm = static_cast<uint32_t>(lmul) |
                      (static_cast<uint32_t>(sew) << 3) |
                      (static_cast<uint32_t>(vta) << 6) |
                      (static_cast<uint32_t>(vma) << 7);
    // clang-format on

    m_buffer.Emit32(0xC0007057U | (zimm << 20) | (imm << 15) | (rd.Index() << 7));
}

void Assembler::VSETVL(GPR rd, GPR rs1, GPR rs2) noexcept {
    m_buffer.Emit32(0x80007057U | (rs2.Index() << 20) | (rs1.Index() << 15) | (rd.Index() << 7));
}

void Assembler::VSETVLI(GPR rd, GPR rs, SEW sew, LMUL lmul, VTA vta, VMA vma) noexcept {
    // clang-format off
    const auto zimm = static_cast<uint32_t>(lmul) |
                      (static_cast<uint32_t>(sew) << 3) |
                      (static_cast<uint32_t>(vta) << 6) |
                      (static_cast<uint32_t>(vma) << 7);
    // clang-format on

    m_buffer.Emit32(0x00007057U | (zimm << 20) | (rs.Index() << 15) | (rd.Index() << 7));
}

} // namespace biscuit
