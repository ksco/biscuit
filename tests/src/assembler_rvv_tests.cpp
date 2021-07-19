#include <catch/catch.hpp>

#include <biscuit/assembler.hpp>

using namespace biscuit;

TEST_CASE("VAADD.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAADD(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x26862257);

    as.RewindBuffer();

    as.VAADD(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x24862257);
}

TEST_CASE("VAADD.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAADD(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2685E257);

    as.RewindBuffer();

    as.VAADD(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2485E257);
}

TEST_CASE("VAADDU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAADDU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x22862257);

    as.RewindBuffer();

    as.VAADDU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x20862257);
}

TEST_CASE("VAADDU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAADDU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2285E257);

    as.RewindBuffer();

    as.VAADDU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2085E257);
}

TEST_CASE("VADC.VVM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VADC(v4, v8, v12);
    REQUIRE(value == 0x40860257);
}

TEST_CASE("VADC.VXM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VADC(v4, v8, x11);
    REQUIRE(value == 0x4085C257);
}

TEST_CASE("VADC.VIM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VADC(v4, v8, 15);
    REQUIRE(value == 0x4087B257);

    as.RewindBuffer();

    as.VADC(v4, v8, -16);
    REQUIRE(value == 0x40883257);
}

TEST_CASE("VADD.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VADD(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x02860257);

    as.RewindBuffer();

    as.VADD(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x00860257);
}

TEST_CASE("VADD.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VADD(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x0285C257);

    as.RewindBuffer();

    as.VADD(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x0085C257);
}

TEST_CASE("VADD.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VADD(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x0287B257);

    as.RewindBuffer();

    as.VADD(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x02883257);

    as.RewindBuffer();

    as.VADD(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x0087B257);

    as.RewindBuffer();

    as.VADD(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x00883257);
}

TEST_CASE("VAND.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAND(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x26860257);

    as.RewindBuffer();

    as.VAND(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x24860257);
}

TEST_CASE("VAND.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAND(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2685C257);

    as.RewindBuffer();

    as.VAND(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2485C257);
}

TEST_CASE("VAND.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VAND(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x2687B257);

    as.RewindBuffer();

    as.VAND(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x26883257);

    as.RewindBuffer();

    as.VAND(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x2487B257);

    as.RewindBuffer();

    as.VAND(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x24883257);
}

TEST_CASE("VASUB.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VASUB(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x2E862257);

    as.RewindBuffer();

    as.VASUB(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x2C862257);
}

TEST_CASE("VASUB.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VASUB(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2E85E257);

    as.RewindBuffer();

    as.VASUB(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2C85E257);
}

TEST_CASE("VASUBU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VASUBU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x2A862257);

    as.RewindBuffer();

    as.VASUBU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x28862257);
}

TEST_CASE("VASUBU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VASUBU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2A85E257);

    as.RewindBuffer();

    as.VASUBU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2885E257);
}

TEST_CASE("VCOMPRESS.VM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VCOMPRESS(v4, v8, v12);
    REQUIRE(value == 0x5E862257);
}

TEST_CASE("VDIV.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VDIV(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x86862257);

    as.RewindBuffer();

    as.VDIV(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x84862257);
}

TEST_CASE("VDIV.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VDIV(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8685E257);

    as.RewindBuffer();

    as.VDIV(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8485E257);
}

TEST_CASE("VDIVU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VDIVU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x82862257);

    as.RewindBuffer();

    as.VDIVU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x80862257);
}

TEST_CASE("VDIVU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VDIVU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8285E257);

    as.RewindBuffer();

    as.VDIVU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8085E257);
}

TEST_CASE("VMACC.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMACC(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xB6862257);

    as.RewindBuffer();

    as.VMACC(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xB4862257);
}

TEST_CASE("VMACC.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMACC(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xB685E257);

    as.RewindBuffer();

    as.VMACC(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xB485E257);
}

TEST_CASE("VMADC.VV(M)", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMADC(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x46860257);

    as.RewindBuffer();

    as.VMADC(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x44860257);
}

TEST_CASE("VMADC.VX(M)", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMADC(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x4685C257);

    as.RewindBuffer();

    as.VMADC(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x4485C257);
}

TEST_CASE("VMADC.VI(M)", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMADC(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x4687B257);

    as.RewindBuffer();

    as.VMADC(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x46883257);

    as.RewindBuffer();

    as.VMADC(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x4487B257);

    as.RewindBuffer();

    as.VMADC(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x44883257);
}

TEST_CASE("VMADD.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMADD(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xA6862257);

    as.RewindBuffer();

    as.VMADD(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xA4862257);
}

TEST_CASE("VMADD.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMADD(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xA685E257);

    as.RewindBuffer();

    as.VMADD(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xA485E257);
}

TEST_CASE("VMAND.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMAND(v4, v8, v12);
    REQUIRE(value == 0x66862257);
}

TEST_CASE("VMANDNOT.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMANDNOT(v4, v8, v12);
    REQUIRE(value == 0x62862257);
}

TEST_CASE("VMNAND.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMNAND(v4, v8, v12);
    REQUIRE(value == 0x76862257);
}

TEST_CASE("VMNOR.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMNOR(v4, v8, v12);
    REQUIRE(value == 0x7A862257);
}

TEST_CASE("VMOR.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMOR(v4, v8, v12);
    REQUIRE(value == 0x6A862257);
}

TEST_CASE("VMORNOT.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMORNOT(v4, v8, v12);
    REQUIRE(value == 0x72862257);
}

TEST_CASE("VMXNOR.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMXNOR(v4, v8, v12);
    REQUIRE(value == 0x7E862257);
}

TEST_CASE("VMXOR.MM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMXOR(v4, v8, v12);
    REQUIRE(value == 0x6E862257);
}

TEST_CASE("VMAX.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMAX(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x1E860257);

    as.RewindBuffer();

    as.VMAX(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x1C860257);
}

TEST_CASE("VMAX.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMAX(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x1E85C257);

    as.RewindBuffer();

    as.VMAX(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x1C85C257);
}

TEST_CASE("VMAXU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMAXU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x1A860257);

    as.RewindBuffer();

    as.VMAXU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x18860257);
}

TEST_CASE("VMAXU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMAXU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x1A85C257);

    as.RewindBuffer();

    as.VMAXU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x1885C257);
}

TEST_CASE("VMERGE.VVM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMERGE(v4, v8, v12);
    REQUIRE(value == 0x5C860257);
}

TEST_CASE("VMERGE.VXM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMERGE(v4, v8, x11);
    REQUIRE(value == 0x5C85C257);
}

TEST_CASE("VMERGE.VIM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMERGE(v4, v8, 15);
    REQUIRE(value == 0x5C87B257);

    as.RewindBuffer();

    as.VMERGE(v4, v8, -16);
    REQUIRE(value == 0x5C883257);
}

TEST_CASE("VMIN.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMIN(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x16860257);

    as.RewindBuffer();

    as.VMIN(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x14860257);
}

TEST_CASE("VMIN.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMIN(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x1685C257);

    as.RewindBuffer();

    as.VMIN(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x1485C257);
}

TEST_CASE("VMINU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMINU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x12860257);

    as.RewindBuffer();

    as.VMINU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x10860257);
}

TEST_CASE("VMINU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMINU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x1285C257);

    as.RewindBuffer();

    as.VMINU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x1085C257);
}

TEST_CASE("VMSBC.VV(M)", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSBC(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x4E860257);

    as.RewindBuffer();

    as.VMSBC(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x4C860257);
}

TEST_CASE("VMSBC.VX(M)", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSBC(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x4E85C257);

    as.RewindBuffer();

    as.VMSBC(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x4C85C257);
}

TEST_CASE("VMSEQ.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSEQ(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x62860257);

    as.RewindBuffer();

    as.VMSEQ(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x60860257);
}

TEST_CASE("VMSEQ.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSEQ(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x6285C257);

    as.RewindBuffer();

    as.VMSEQ(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x6085C257);
}

TEST_CASE("VMSEQ.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSEQ(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x6287B257);

    as.RewindBuffer();

    as.VMSEQ(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x62883257);

    as.RewindBuffer();

    as.VMSEQ(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x6087B257);

    as.RewindBuffer();

    as.VMSEQ(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x60883257);
}

TEST_CASE("VMSGT.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSGT(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x7E85C257);

    as.RewindBuffer();

    as.VMSGT(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x7C85C257);
}

TEST_CASE("VMSGT.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSGT(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x7E87B257);

    as.RewindBuffer();

    as.VMSGT(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x7E883257);

    as.RewindBuffer();

    as.VMSGT(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x7C87B257);

    as.RewindBuffer();

    as.VMSGT(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x7C883257);
}

TEST_CASE("VMSGTU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSGTU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x7A85C257);

    as.RewindBuffer();

    as.VMSGTU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x7885C257);
}

TEST_CASE("VMSGTU.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSGTU(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x7A87B257);

    as.RewindBuffer();

    as.VMSGTU(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x7A883257);

    as.RewindBuffer();

    as.VMSGTU(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x7887B257);

    as.RewindBuffer();

    as.VMSGTU(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x78883257);
}

TEST_CASE("VMSLE.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLE(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x76860257);

    as.RewindBuffer();

    as.VMSLE(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x74860257);
}

TEST_CASE("VMSLE.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLE(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x7685C257);

    as.RewindBuffer();

    as.VMSLE(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x7485C257);
}

TEST_CASE("VMSLE.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLE(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x7687B257);

    as.RewindBuffer();

    as.VMSLE(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x76883257);

    as.RewindBuffer();

    as.VMSLE(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x7487B257);

    as.RewindBuffer();

    as.VMSLE(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x74883257);
}

TEST_CASE("VMSLEU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLEU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x72860257);

    as.RewindBuffer();

    as.VMSLEU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x70860257);
}

TEST_CASE("VMSLEU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLEU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x7285C257);

    as.RewindBuffer();

    as.VMSLEU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x7085C257);
}

TEST_CASE("VMSLEU.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLEU(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x7287B257);

    as.RewindBuffer();

    as.VMSLEU(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x72883257);

    as.RewindBuffer();

    as.VMSLEU(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x7087B257);

    as.RewindBuffer();

    as.VMSLEU(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x70883257);
}

TEST_CASE("VMSLT.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLT(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x6E860257);

    as.RewindBuffer();

    as.VMSLT(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x6C860257);
}

TEST_CASE("VMSLT.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLT(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x6E85C257);

    as.RewindBuffer();

    as.VMSLT(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x6C85C257);
}

TEST_CASE("VMSLTU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLTU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x6A860257);

    as.RewindBuffer();

    as.VMSLTU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x68860257);
}

TEST_CASE("VMSLTU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSLTU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x6A85C257);

    as.RewindBuffer();

    as.VMSLTU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x6885C257);
}

TEST_CASE("VMSNE.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSNE(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x66860257);

    as.RewindBuffer();

    as.VMSNE(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x64860257);
}

TEST_CASE("VMSNE.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSNE(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x6685C257);

    as.RewindBuffer();

    as.VMSNE(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x6485C257);
}

TEST_CASE("VMSNE.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMSNE(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x6687B257);

    as.RewindBuffer();

    as.VMSNE(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x66883257);

    as.RewindBuffer();

    as.VMSNE(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x6487B257);

    as.RewindBuffer();

    as.VMSNE(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x64883257);
}

TEST_CASE("VMUL.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMUL(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x96862257);

    as.RewindBuffer();

    as.VMUL(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x94862257);
}

TEST_CASE("VMUL.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMUL(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x9685E257);

    as.RewindBuffer();

    as.VMUL(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x9485E257);
}

TEST_CASE("VMULH.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMULH(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x9E862257);

    as.RewindBuffer();

    as.VMULH(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x9C862257);
}

TEST_CASE("VMULH.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMULH(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x9E85E257);

    as.RewindBuffer();

    as.VMULH(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x9C85E257);
}

TEST_CASE("VMULHSU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMULHSU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x9A862257);

    as.RewindBuffer();

    as.VMULHSU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x98862257);
}

TEST_CASE("VMULHSU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMULHSU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x9A85E257);

    as.RewindBuffer();

    as.VMULHSU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x9885E257);
}

TEST_CASE("VMULHU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMULHU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x92862257);

    as.RewindBuffer();

    as.VMULHU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x90862257);
}

TEST_CASE("VMULHU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMULHU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x9285E257);

    as.RewindBuffer();

    as.VMULHU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x9085E257);
}

TEST_CASE("VMV.V.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV(v8, v12);
    REQUIRE(value == 0x5E060457);
}

TEST_CASE("VMV.V.X", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV(v8, x11);
    REQUIRE(value == 0x5E05C457);
}

TEST_CASE("VMV.V.I", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV(v8, 15);
    REQUIRE(value == 0x5E07B457);

    as.RewindBuffer();

    as.VMV(v8, -16);
    REQUIRE(value == 0x5E083457);
}

TEST_CASE("VMV1R.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV1R(v1, v2);
    REQUIRE(value == 0x9E2030D7);
}

TEST_CASE("VMV2R.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV2R(v2, v4);
    REQUIRE(value == 0x9E40B157);
}

TEST_CASE("VMV4R.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV4R(v4, v8);
    REQUIRE(value == 0x9E81B257);
}

TEST_CASE("VMV8R.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VMV8R(v0, v8);
    REQUIRE(value == 0x9E83B057);
}

TEST_CASE("VNCLIP.WV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNCLIP(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xBE860257);

    as.RewindBuffer();

    as.VNCLIP(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xBC860257);
}

TEST_CASE("VNCLIP.WX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNCLIP(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xBE85C257);

    as.RewindBuffer();

    as.VNCLIP(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xBC85C257);
}

TEST_CASE("VNCLIP.WI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNCLIP(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xBE80B257);

    as.RewindBuffer();

    as.VNCLIP(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xBE8FB257);

    as.RewindBuffer();

    as.VNCLIP(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xBC80B257);

    as.RewindBuffer();

    as.VNCLIP(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xBC8FB257);
}

TEST_CASE("VNCLIPU.WV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNCLIPU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xBA860257);

    as.RewindBuffer();

    as.VNCLIPU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xB8860257);
}

TEST_CASE("VNCLIPU.WX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNCLIPU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xBA85C257);

    as.RewindBuffer();

    as.VNCLIPU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xB885C257);
}

TEST_CASE("VNCLIPU.WI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNCLIPU(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xBA80B257);

    as.RewindBuffer();

    as.VNCLIPU(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xBA8FB257);

    as.RewindBuffer();

    as.VNCLIPU(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xB880B257);

    as.RewindBuffer();

    as.VNCLIPU(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xB88FB257);
}

TEST_CASE("VNMSAC.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNMSAC(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xBE862257);

    as.RewindBuffer();

    as.VNMSAC(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xBC862257);
}

TEST_CASE("VNMSAC.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNMSAC(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xBE85E257);

    as.RewindBuffer();

    as.VNMSAC(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xBC85E257);
}

TEST_CASE("VNMSUB.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNMSUB(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xAE862257);

    as.RewindBuffer();

    as.VNMSUB(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xAC862257);
}

TEST_CASE("VNMSUB.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNMSUB(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xAE85E257);

    as.RewindBuffer();

    as.VNMSUB(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xAC85E257);
}

TEST_CASE("VNSRA.WV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNSRA(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xB6860257);

    as.RewindBuffer();

    as.VNSRA(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xB4860257);
}

TEST_CASE("VNSRA.WX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNSRA(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xB685C257);

    as.RewindBuffer();

    as.VNSRA(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xB485C257);
}

TEST_CASE("VNSRA.WI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNSRA(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xB680B257);

    as.RewindBuffer();

    as.VNSRA(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xB68FB257);

    as.RewindBuffer();

    as.VNSRA(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xB480B257);

    as.RewindBuffer();

    as.VNSRA(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xB48FB257);
}

TEST_CASE("VNSRL.WV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNSRL(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xB2860257);

    as.RewindBuffer();

    as.VNSRL(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xB0860257);
}

TEST_CASE("VNSRL.WX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNSRL(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xB285C257);

    as.RewindBuffer();

    as.VNSRL(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xB085C257);
}

TEST_CASE("VNSRL.WI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VNSRL(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xB280B257);

    as.RewindBuffer();

    as.VNSRL(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xB28FB257);

    as.RewindBuffer();

    as.VNSRL(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xB080B257);

    as.RewindBuffer();

    as.VNSRL(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xB08FB257);
}

TEST_CASE("VOR.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VOR(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x2A860257);

    as.RewindBuffer();

    as.VOR(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x28860257);
}

TEST_CASE("VOR.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VOR(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2A85C257);

    as.RewindBuffer();

    as.VOR(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2885C257);
}

TEST_CASE("VOR.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VOR(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x2A87B257);

    as.RewindBuffer();

    as.VOR(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x2A883257);

    as.RewindBuffer();

    as.VOR(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x2887B257);

    as.RewindBuffer();

    as.VOR(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x28883257);
}

TEST_CASE("VREDAND.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDAND(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x06862257);

    as.RewindBuffer();

    as.VREDAND(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x04862257);
}

TEST_CASE("VREDMAX.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDMAX(v4, v8, v8, VecMask::No);
    REQUIRE(value == 0x1E842257);

    as.RewindBuffer();

    as.VREDMAX(v4, v8, v8, VecMask::Yes);
    REQUIRE(value == 0x1C842257);
}

TEST_CASE("VREDMAXU.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDMAXU(v4, v8, v8, VecMask::No);
    REQUIRE(value == 0x1A842257);

    as.RewindBuffer();

    as.VREDMAXU(v4, v8, v8, VecMask::Yes);
    REQUIRE(value == 0x18842257);
}

TEST_CASE("VREDMIN.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDMIN(v4, v8, v8, VecMask::No);
    REQUIRE(value == 0x16842257);

    as.RewindBuffer();

    as.VREDMIN(v4, v8, v8, VecMask::Yes);
    REQUIRE(value == 0x14842257);
}

TEST_CASE("VREDMINU.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDMINU(v4, v8, v8, VecMask::No);
    REQUIRE(value == 0x12842257);

    as.RewindBuffer();

    as.VREDMINU(v4, v8, v8, VecMask::Yes);
    REQUIRE(value == 0x10842257);
}

TEST_CASE("VREDOR.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDOR(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x0A862257);

    as.RewindBuffer();

    as.VREDOR(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x08862257);
}

TEST_CASE("VREDSUM.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDSUM(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x02862257);

    as.RewindBuffer();

    as.VREDSUM(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x00862257);
}

TEST_CASE("VREDXOR.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREDXOR(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x0E862257);

    as.RewindBuffer();

    as.VREDXOR(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x0C862257);
}

TEST_CASE("VREM.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREM(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x8E862257);

    as.RewindBuffer();

    as.VREM(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x8C862257);
}

TEST_CASE("VREM.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREM(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8E85E257);

    as.RewindBuffer();

    as.VREM(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8C85E257);
}

TEST_CASE("VREMU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREMU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x8A862257);

    as.RewindBuffer();

    as.VREMU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x88862257);
}

TEST_CASE("VREMU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VREMU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8A85E257);

    as.RewindBuffer();

    as.VREMU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8885E257);
}

TEST_CASE("VRGATHER.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VRGATHER(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x32860257);

    as.RewindBuffer();

    as.VRGATHER(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x30860257);
}

TEST_CASE("VRGATHER.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VRGATHER(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x3285C257);

    as.RewindBuffer();

    as.VRGATHER(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x3085C257);
}

TEST_CASE("VRGATHER.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VRGATHER(v4, v8, 0, VecMask::No);
    REQUIRE(value == 0x32803257);

    as.RewindBuffer();

    as.VRGATHER(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0x328FB257);

    as.RewindBuffer();

    as.VRGATHER(v4, v8, 0, VecMask::Yes);
    REQUIRE(value == 0x30803257);

    as.RewindBuffer();

    as.VRGATHER(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0x308FB257);
}

TEST_CASE("VRGATHEREI16.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VRGATHEREI16(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x3A860257);

    as.RewindBuffer();

    as.VRGATHEREI16(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x38860257);
}

TEST_CASE("VRSUB.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VRSUB(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x0E85C257);

    as.RewindBuffer();

    as.VRSUB(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x0C85C257);
}

TEST_CASE("VRSUB.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VRSUB(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x0E87B257);

    as.RewindBuffer();

    as.VRSUB(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x0E883257);

    as.RewindBuffer();

    as.VRSUB(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x0C87B257);

    as.RewindBuffer();

    as.VRSUB(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x0C883257);
}

TEST_CASE("VSADD.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSADD(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x86860257);

    as.RewindBuffer();

    as.VSADD(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x84860257);
}

TEST_CASE("VSADD.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSADD(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8685C257);

    as.RewindBuffer();

    as.VSADD(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8485C257);
}

TEST_CASE("VSADD.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSADD(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x8687B257);

    as.RewindBuffer();

    as.VSADD(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x86883257);

    as.RewindBuffer();

    as.VSADD(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x8487B257);

    as.RewindBuffer();

    as.VSADD(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x84883257);
}

TEST_CASE("VSADDU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSADDU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x82860257);

    as.RewindBuffer();

    as.VSADDU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x80860257);
}

TEST_CASE("VSADDU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSADDU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8285C257);

    as.RewindBuffer();

    as.VSADDU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8085C257);
}

TEST_CASE("VSADDU.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSADDU(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x8287B257);

    as.RewindBuffer();

    as.VSADDU(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x82883257);

    as.RewindBuffer();

    as.VSADDU(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x8087B257);

    as.RewindBuffer();

    as.VSADDU(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x80883257);
}

TEST_CASE("VSBC.VVM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSBC(v4, v8, v12);
    REQUIRE(value == 0x48860257);
}

TEST_CASE("VSBC.VXM", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSBC(v4, v8, x11);
    REQUIRE(value == 0x4885C257);
}

TEST_CASE("VSLIDE1DOWN.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLIDE1DOWN(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x3E85E257);

    as.RewindBuffer();

    as.VSLIDE1DOWN(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x3C85E257);
}

TEST_CASE("VSLIDEDOWN.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLIDEDOWN(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x3E85C257);

    as.RewindBuffer();

    as.VSLIDEDOWN(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x3C85C257);
}

TEST_CASE("VSLIDEDOWN.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLIDEDOWN(v4, v8, 0, VecMask::No);
    REQUIRE(value == 0x3E803257);

    as.RewindBuffer();

    as.VSLIDEDOWN(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0x3E8FB257);

    as.RewindBuffer();

    as.VSLIDEDOWN(v4, v8, 0, VecMask::Yes);
    REQUIRE(value == 0x3C803257);

    as.RewindBuffer();

    as.VSLIDEDOWN(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0x3C8FB257);
}

TEST_CASE("VSLIDE1UP.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLIDE1UP(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x3A85E257);

    as.RewindBuffer();

    as.VSLIDE1UP(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x3885E257);
}

TEST_CASE("VSLIDEUP.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLIDEUP(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x3A85C257);

    as.RewindBuffer();

    as.VSLIDEUP(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x3885C257);
}

TEST_CASE("VSLIDEUP.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLIDEUP(v4, v8, 0, VecMask::No);
    REQUIRE(value == 0x3A803257);

    as.RewindBuffer();

    as.VSLIDEUP(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0x3A8FB257);

    as.RewindBuffer();

    as.VSLIDEUP(v4, v8, 0, VecMask::Yes);
    REQUIRE(value == 0x38803257);

    as.RewindBuffer();

    as.VSLIDEUP(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0x388FB257);
}

TEST_CASE("VSLL.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLL(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x96860257);

    as.RewindBuffer();

    as.VSLL(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x94860257);
}

TEST_CASE("VSLL.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLL(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x9685C257);

    as.RewindBuffer();

    as.VSLL(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x9485C257);
}

TEST_CASE("VSLL.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSLL(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0x9680B257);

    as.RewindBuffer();

    as.VSLL(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0x968FB257);

    as.RewindBuffer();

    as.VSLL(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0x9480B257);

    as.RewindBuffer();

    as.VSLL(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0x948FB257);
}

TEST_CASE("VSMUL.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSMUL(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x9E860257);

    as.RewindBuffer();

    as.VSMUL(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x9C860257);
}

TEST_CASE("VSMUL.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSMUL(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x9E85C257);

    as.RewindBuffer();

    as.VSMUL(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x9C85C257);
}

TEST_CASE("VSRA.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSRA(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xA6860257);

    as.RewindBuffer();

    as.VSRA(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xA4860257);
}

TEST_CASE("VSRA.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSRA(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xA685C257);

    as.RewindBuffer();

    as.VSRA(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xA485C257);
}

TEST_CASE("VSRA.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSRA(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xA680B257);

    as.RewindBuffer();

    as.VSRA(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xA68FB257);

    as.RewindBuffer();

    as.VSRA(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xA480B257);

    as.RewindBuffer();

    as.VSRA(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xA48FB257);
}

TEST_CASE("VSRL.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSRL(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xA2860257);

    as.RewindBuffer();

    as.VSRL(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xA0860257);
}

TEST_CASE("VSRL.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSRL(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xA285C257);

    as.RewindBuffer();

    as.VSRL(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xA085C257);
}

TEST_CASE("VSRL.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSRL(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xA280B257);

    as.RewindBuffer();

    as.VSRL(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xA28FB257);

    as.RewindBuffer();

    as.VSRL(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xA080B257);

    as.RewindBuffer();

    as.VSRL(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xA08FB257);
}

TEST_CASE("VSSRA.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSRA(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xAE860257);

    as.RewindBuffer();

    as.VSSRA(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xAC860257);
}

TEST_CASE("VSSRA.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSRA(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xAE85C257);

    as.RewindBuffer();

    as.VSSRA(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xAC85C257);
}

TEST_CASE("VSSRA.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSRA(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xAE80B257);

    as.RewindBuffer();

    as.VSSRA(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xAE8FB257);

    as.RewindBuffer();

    as.VSSRA(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xAC80B257);

    as.RewindBuffer();

    as.VSSRA(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xAC8FB257);
}

TEST_CASE("VSSRL.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSRL(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xAA860257);

    as.RewindBuffer();

    as.VSSRL(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xA8860257);
}

TEST_CASE("VSSRL.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSRL(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xAA85C257);

    as.RewindBuffer();

    as.VSSRL(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xA885C257);
}

TEST_CASE("VSSRL.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSRL(v4, v8, 1, VecMask::No);
    REQUIRE(value == 0xAA80B257);

    as.RewindBuffer();

    as.VSSRL(v4, v8, 31, VecMask::No);
    REQUIRE(value == 0xAA8FB257);

    as.RewindBuffer();

    as.VSSRL(v4, v8, 1, VecMask::Yes);
    REQUIRE(value == 0xA880B257);

    as.RewindBuffer();

    as.VSSRL(v4, v8, 31, VecMask::Yes);
    REQUIRE(value == 0xA88FB257);
}

TEST_CASE("VSSUB.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSUB(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x8E860257);

    as.RewindBuffer();

    as.VSSUB(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x8C860257);
}

TEST_CASE("VSSUB.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSUB(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8E85C257);

    as.RewindBuffer();

    as.VSSUB(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8C85C257);
}

TEST_CASE("VSSUBU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSUBU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x8A860257);

    as.RewindBuffer();

    as.VSSUBU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x88860257);
}

TEST_CASE("VSSUBU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSUBU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x8A85C257);

    as.RewindBuffer();

    as.VSSUBU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x8885C257);
}

TEST_CASE("VSUB.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSUB(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x0A860257);

    as.RewindBuffer();

    as.VSUB(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x08860257);
}

TEST_CASE("VSUB.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSUB(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x0A85C257);

    as.RewindBuffer();

    as.VSUB(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x0885C257);
}

TEST_CASE("VWADD.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VWADD(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xC6862257);

    as.RewindBuffer();

    as.VWADD(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xC4862257);
}

TEST_CASE("VWADD.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VWADD(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xC685E257);

    as.RewindBuffer();

    as.VWADD(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xC485E257);
}

TEST_CASE("VWADDU.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VWADDU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xC2862257);

    as.RewindBuffer();

    as.VWADDU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xC0862257);
}

TEST_CASE("VWADDU.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VWADDU(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0xC285E257);

    as.RewindBuffer();

    as.VWADDU(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0xC085E257);
}

TEST_CASE("VWREDSUM.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VWREDSUM(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xC6860257);

    as.RewindBuffer();

    as.VWREDSUM(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xC4860257);
}

TEST_CASE("VWREDSUMU.VS", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VWREDSUMU(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0xC2860257);

    as.RewindBuffer();

    as.VWREDSUMU(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0xC0860257);
}

TEST_CASE("VXOR.VV", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VXOR(v4, v8, v12, VecMask::No);
    REQUIRE(value == 0x2E860257);

    as.RewindBuffer();

    as.VXOR(v4, v8, v12, VecMask::Yes);
    REQUIRE(value == 0x2C860257);
}

TEST_CASE("VXOR.VX", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VXOR(v4, v8, x11, VecMask::No);
    REQUIRE(value == 0x2E85C257);

    as.RewindBuffer();

    as.VXOR(v4, v8, x11, VecMask::Yes);
    REQUIRE(value == 0x2C85C257);
}

TEST_CASE("VXOR.VI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VXOR(v4, v8, 15, VecMask::No);
    REQUIRE(value == 0x2E87B257);

    as.RewindBuffer();

    as.VXOR(v4, v8, -16, VecMask::No);
    REQUIRE(value == 0x2E883257);

    as.RewindBuffer();

    as.VXOR(v4, v8, 15, VecMask::Yes);
    REQUIRE(value == 0x2C87B257);

    as.RewindBuffer();

    as.VXOR(v4, v8, -16, VecMask::Yes);
    REQUIRE(value == 0x2C883257);
}

TEST_CASE("VLE8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE8(v0, x11, VecMask::No);
    REQUIRE(value == 0x02058007);

    as.RewindBuffer();

    as.VLE8(v0, x11, VecMask::Yes);
    REQUIRE(value == 0x00058007);
}

TEST_CASE("VLE16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE16(v0, x11, VecMask::No);
    REQUIRE(value == 0x0205D007);

    as.RewindBuffer();

    as.VLE16(v0, x11, VecMask::Yes);
    REQUIRE(value == 0x0005D007);
}

TEST_CASE("VLE32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE32(v0, x11, VecMask::No);
    REQUIRE(value == 0x0205E007);

    as.RewindBuffer();

    as.VLE32(v0, x11, VecMask::Yes);
    REQUIRE(value == 0x0005E007);
}

TEST_CASE("VLE64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE64(v0, x11, VecMask::No);
    REQUIRE(value == 0x0205F007);

    as.RewindBuffer();

    as.VLE64(v0, x11, VecMask::Yes);
    REQUIRE(value == 0x0005F007);
}

TEST_CASE("VLM.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLM(v0, x11);
    REQUIRE(value == 0x02B58007);
}

TEST_CASE("VLSE8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLSE8(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB50207);

    as.RewindBuffer();

    as.VLSE8(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B50207);
}

TEST_CASE("VLSE16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLSE16(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB55207);

    as.RewindBuffer();

    as.VLSE16(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B55207);
}

TEST_CASE("VLSE32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLSE32(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB56207);

    as.RewindBuffer();

    as.VLSE32(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B56207);
}

TEST_CASE("VLSE64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLSE64(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB57207);

    as.RewindBuffer();

    as.VLSE64(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B57207);
}

TEST_CASE("VLOXEI8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLOXEI8(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC50207);

    as.RewindBuffer();

    as.VLOXEI8(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC50207);
}

TEST_CASE("VLOXEI16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLOXEI16(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC55207);

    as.RewindBuffer();

    as.VLOXEI16(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC55207);
}

TEST_CASE("VLOXEI32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLOXEI32(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC56207);

    as.RewindBuffer();

    as.VLOXEI32(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC56207);
}

TEST_CASE("VLOXEI64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLOXEI64(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC57207);

    as.RewindBuffer();

    as.VLOXEI64(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC57207);
}

TEST_CASE("VLUXEI8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLUXEI8(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C50207);

    as.RewindBuffer();

    as.VLUXEI8(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C50207);
}

TEST_CASE("VLUXEI16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLUXEI16(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C55207);

    as.RewindBuffer();

    as.VLUXEI16(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C55207);
}

TEST_CASE("VLUXEI32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLUXEI32(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C56207);

    as.RewindBuffer();

    as.VLUXEI32(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C56207);
}

TEST_CASE("VLUXEI64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLUXEI64(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C57207);

    as.RewindBuffer();

    as.VLUXEI64(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C57207);
}

TEST_CASE("VLE8FF.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE8FF(v4, x10, VecMask::No);
    REQUIRE(value == 0x03050207);

    as.RewindBuffer();

    as.VLE8FF(v4, x10, VecMask::Yes);
    REQUIRE(value == 0x01050207);
}

TEST_CASE("VLE16FF.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE16FF(v4, x10, VecMask::No);
    REQUIRE(value == 0x03055207);

    as.RewindBuffer();

    as.VLE16FF(v4, x10, VecMask::Yes);
    REQUIRE(value == 0x01055207);
}

TEST_CASE("VLE32FF.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE32FF(v4, x10, VecMask::No);
    REQUIRE(value == 0x03056207);

    as.RewindBuffer();

    as.VLE32FF(v4, x10, VecMask::Yes);
    REQUIRE(value == 0x01056207);
}

TEST_CASE("VLE64FF.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLE64FF(v4, x10, VecMask::No);
    REQUIRE(value == 0x03057207);

    as.RewindBuffer();

    as.VLE64FF(v4, x10, VecMask::Yes);
    REQUIRE(value == 0x01057207);
}

TEST_CASE("8-bit segmented unit-stride loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSEGE8(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02050207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSEGE8(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00050207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit segmented unit-stride loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSEGE16(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02055207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSEGE16(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00055207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit segmented unit-stride loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSEGE32(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02056207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSEGE32(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00056207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit segmented unit-stride loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSEGE64(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02057207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSEGE64(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00057207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit segmented strided loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSSEGE8(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB50207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSSEGE8(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B50207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit segmented strided loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSSEGE16(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB55207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSSEGE16(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B55207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit segmented strided loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSSEGE32(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB56207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSSEGE32(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B56207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit segmented strided loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLSSEGE64(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB57207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLSSEGE64(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B57207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit vector indexed-ordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLOXSEGEI8(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC50207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLOXSEGEI8(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC50207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit vector indexed-ordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLOXSEGEI16(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC55207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLOXSEGEI16(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC55207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit vector indexed-ordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLOXSEGEI32(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC56207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLOXSEGEI32(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC56207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit vector indexed-ordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLOXSEGEI64(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC57207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLOXSEGEI64(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC57207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit vector indexed-unordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLUXSEGEI8(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C50207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLUXSEGEI8(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C50207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit vector indexed-unordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLUXSEGEI16(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C55207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLUXSEGEI16(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C55207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit vector indexed-unordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLUXSEGEI32(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C56207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLUXSEGEI32(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C56207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit vector indexed-unordered segment loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VLUXSEGEI64(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C57207 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VLUXSEGEI64(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C57207 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit vector whole register loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLRE8(1, v3, x10);
    REQUIRE(value == 0x02850187);
    as.RewindBuffer();

    as.VLRE8(2, v2, x10);
    REQUIRE(value == 0x22850107);
    as.RewindBuffer();

    as.VLRE8(4, v4, x10);
    REQUIRE(value == 0x62850207);
    as.RewindBuffer();

    as.VLRE8(8, v8, x10);
    REQUIRE(value == 0xE2850407);
}

TEST_CASE("16-bit vector whole register loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLRE16(1, v3, x10);
    REQUIRE(value == 0x02855187);
    as.RewindBuffer();

    as.VLRE16(2, v2, x10);
    REQUIRE(value == 0x22855107);
    as.RewindBuffer();

    as.VLRE16(4, v4, x10);
    REQUIRE(value == 0x62855207);
    as.RewindBuffer();

    as.VLRE16(8, v8, x10);
    REQUIRE(value == 0xE2855407);
}

TEST_CASE("32-bit vector whole register loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLRE32(1, v3, x10);
    REQUIRE(value == 0x02856187);
    as.RewindBuffer();

    as.VLRE32(2, v2, x10);
    REQUIRE(value == 0x22856107);
    as.RewindBuffer();

    as.VLRE32(4, v4, x10);
    REQUIRE(value == 0x62856207);
    as.RewindBuffer();

    as.VLRE32(8, v8, x10);
    REQUIRE(value == 0xE2856407);
}

TEST_CASE("64-bit vector whole register loads", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VLRE64(1, v3, x10);
    REQUIRE(value == 0x02857187);
    as.RewindBuffer();

    as.VLRE64(2, v2, x10);
    REQUIRE(value == 0x22857107);
    as.RewindBuffer();

    as.VLRE64(4, v4, x10);
    REQUIRE(value == 0x62857207);
    as.RewindBuffer();

    as.VLRE64(8, v8, x10);
    REQUIRE(value == 0xE2857407);
}

TEST_CASE("VSE8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSE8(v0, x13, VecMask::No);
    REQUIRE(value == 0x02068027);

    as.RewindBuffer();

    as.VSE8(v0, x13, VecMask::Yes);
    REQUIRE(value == 0x00068027);
}

TEST_CASE("VSE16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSE16(v0, x13, VecMask::No);
    REQUIRE(value == 0x0206D027);

    as.RewindBuffer();

    as.VSE16(v0, x13, VecMask::Yes);
    REQUIRE(value == 0x0006D027);
}

TEST_CASE("VSE32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSE32(v0, x13, VecMask::No);
    REQUIRE(value == 0x0206E027);

    as.RewindBuffer();

    as.VSE32(v0, x13, VecMask::Yes);
    REQUIRE(value == 0x0006E027);
}

TEST_CASE("VSE64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSE64(v0, x13, VecMask::No);
    REQUIRE(value == 0x0206F027);

    as.RewindBuffer();

    as.VSE64(v0, x13, VecMask::Yes);
    REQUIRE(value == 0x0006F027);
}

TEST_CASE("VSM.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSM(v0, x13);
    REQUIRE(value == 0x02B68027);
}

TEST_CASE("VSSE8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSE8(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB50227);

    as.RewindBuffer();

    as.VSSE8(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B50227);
}

TEST_CASE("VSSE16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSE16(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB55227);

    as.RewindBuffer();

    as.VSSE16(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B55227);
}

TEST_CASE("VSSE32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSE32(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB56227);

    as.RewindBuffer();

    as.VSSE32(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B56227);
}

TEST_CASE("VSSE64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSSE64(v4, x10, x11, VecMask::No);
    REQUIRE(value == 0x0AB57227);

    as.RewindBuffer();

    as.VSSE64(v4, x10, x11, VecMask::Yes);
    REQUIRE(value == 0x08B57227);
}

TEST_CASE("VSOXEI8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSOXEI8(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC50227);

    as.RewindBuffer();

    as.VSOXEI8(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC50227);
}

TEST_CASE("VSOXEI16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSOXEI16(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC55227);

    as.RewindBuffer();

    as.VSOXEI16(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC55227);
}

TEST_CASE("VSOXEI32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSOXEI32(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC56227);

    as.RewindBuffer();

    as.VSOXEI32(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC56227);
}

TEST_CASE("VSOXEI64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSOXEI64(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x0EC57227);

    as.RewindBuffer();

    as.VSOXEI64(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x0CC57227);
}

TEST_CASE("VSUXEI8.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSUXEI8(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C50227);

    as.RewindBuffer();

    as.VSUXEI8(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C50227);
}

TEST_CASE("VSUXEI16.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSUXEI16(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C55227);

    as.RewindBuffer();

    as.VSUXEI16(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C55227);
}

TEST_CASE("VSUXEI32.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSUXEI32(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C56227);

    as.RewindBuffer();

    as.VSUXEI32(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C56227);
}

TEST_CASE("VSUXEI64.V", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSUXEI64(v4, x10, v12, VecMask::No);
    REQUIRE(value == 0x06C57227);

    as.RewindBuffer();

    as.VSUXEI64(v4, x10, v12, VecMask::Yes);
    REQUIRE(value == 0x04C57227);
}

TEST_CASE("8-bit segmented unit-stride stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSEGE8(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02050227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSEGE8(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00050227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit segmented unit-stride stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSEGE16(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02055227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSEGE16(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00055227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit segmented unit-stride stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSEGE32(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02056227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSEGE32(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00056227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit segmented unit-stride stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSEGE64(i, v4, x10, VecMask::No);
        REQUIRE(value == (0x02057227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSEGE64(i, v4, x10, VecMask::Yes);
        REQUIRE(value == (0x00057227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit segmented strided stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSSEGE8(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB50227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSSEGE8(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B50227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit segmented strided stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSSEGE16(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB55227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSSEGE16(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B55227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit segmented strided stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSSEGE32(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB56227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSSEGE32(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B56227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit segmented strided stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSSSEGE64(i, v4, x10, x11, VecMask::No);
        REQUIRE(value == (0x0AB57227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSSSEGE64(i, v4, x10, x11, VecMask::Yes);
        REQUIRE(value == (0x08B57227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit segmented vector indexed-ordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSOXSEGEI8(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC50227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSOXSEGEI8(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC50227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit segmented vector indexed-ordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSOXSEGEI16(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC55227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSOXSEGEI16(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC55227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit segmented vector indexed-ordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSOXSEGEI32(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC56227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSOXSEGEI32(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC56227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit segmented vector indexed-ordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSOXSEGEI64(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x0EC57227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSOXSEGEI64(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x0CC57227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("8-bit segmented vector indexed-unordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSUXSEGEI8(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C50227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSUXSEGEI8(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C50227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("16-bit segmented vector indexed-unordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSUXSEGEI16(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C55227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSUXSEGEI16(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C55227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("32-bit segmented vector indexed-unordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSUXSEGEI32(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C56227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSUXSEGEI32(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C56227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("64-bit segmented vector indexed-unordered stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (uint32_t i = 2; i <= 8; i++) {
        as.VSUXSEGEI64(i, v4, x10, v12, VecMask::No);
        REQUIRE(value == (0x06C57227 | ((i - 1) << 29)));

        as.RewindBuffer();

        as.VSUXSEGEI64(i, v4, x10, v12, VecMask::Yes);
        REQUIRE(value == (0x04C57227 | ((i - 1) << 29)));

        as.RewindBuffer();
    }
}

TEST_CASE("Vector whole register stores", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSR(1, v3, x11);
    REQUIRE(value == 0x028581A7);

    as.RewindBuffer();

    as.VSR(2, v2, x11);
    REQUIRE(value == 0x22858127);

    as.RewindBuffer();

    as.VSR(4, v4, x11);
    REQUIRE(value == 0x62858227);

    as.RewindBuffer();

    as.VSR(8, v8, x11);
    REQUIRE(value == 0xE2858427);
}

TEST_CASE("VSETIVLI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSETIVLI(x10, 11, SEW::E8, LMUL::M1, VTA::No, VMA::No);
    REQUIRE(value == 0xC005F557);

    as.RewindBuffer();

    as.VSETIVLI(x10, 11, SEW::E16, LMUL::M2, VTA::No, VMA::No);
    REQUIRE(value == 0xC095F557);

    as.RewindBuffer();

    as.VSETIVLI(x10, 11, SEW::E256, LMUL::M2, VTA::Yes, VMA::No);
    REQUIRE(value == 0xC695F557);

    as.RewindBuffer();

    as.VSETIVLI(x10, 11, SEW::E256, LMUL::M2, VTA::Yes, VMA::Yes);
    REQUIRE(value == 0xCE95F557);
}

TEST_CASE("VSETVL", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSETVL(x10, x11, x12);
    REQUIRE(value == 0x80C5F557);
}

TEST_CASE("VSETVLI", "[rvv]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    as.VSETVLI(x31, x6, SEW::E64, LMUL::MF2, VTA::Yes, VMA::Yes);
    REQUIRE(value == 0x0DF37FD7);

    as.RewindBuffer();

    as.VSETVLI(x31, x6, SEW::E64, LMUL::MF2, VTA::No, VMA::No);
    REQUIRE(value == 0x01F37FD7);

    as.RewindBuffer();

    as.VSETVLI(x12, x18, SEW::E8, LMUL::M1, VTA::No, VMA::No);
    REQUIRE(value == 0x00097657);

    as.RewindBuffer();

    as.VSETVLI(x15, x12, SEW::E32, LMUL::M4, VTA::No, VMA::No);
    REQUIRE(value == 0x012677D7);
}
