#ifndef QEMU_DIFF_ISA_H
#define QEMU_DIFF_ISA_H

#include "generated/autoconf.h"
#include "difftest-def.h"
#include "isa.h"
#include "common.h"
// another common.h
#ifdef CONFIG_ISA64
typedef uint64_t word_t;
#else
typedef uint32_t word_t;
#endif
typedef word_t vaddr_t;
#include "isa-def.h"

union CPU_state qemu_regs;

const char *regs[] = {
        "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

inline void isa_reg_display() {
    // print registers
    // pc
    printf("pc: 0x%lx ", qemu_regs.pc);
    // gpr
    for (int i = 0; i < 32; i++) {
        uint64_t reg = qemu_regs.gpr[i];
        if(reg) printf("%s: 0x%lx ", regs[i], reg);
    }
    // fpr
    for (int i = 0; i < 32; i++) {
        uint64_t reg = qemu_regs.fpr[i];
        if(reg) printf("fpr%d: 0x%lx %lf", i, reg, (double) reg);
    }
    printf("\n");
}

const uint32_t img [] = {
        0x800002b7,  // lui t0,0x80000
        0x0002a023,  // sw  zero,0(t0)
        0x0002a503,  // lw  a0,0(t0)
        0x0000006b,  // nemu_trap
};

#define img_size sizeof(img)

#define instr_number (img_size / 4)

#endif //QEMU_DIFF_ISA_H
