#ifndef QEMU_DIFF_ISA_H
#define QEMU_DIFF_ISA_H

#include "generated/autoconf.h"
#include "difftest-def.h"
#include "isa.h"
#include "common.h"

// another common.h
#if defined(CONFIG_ISA64) && CONFIG_ISA64 == 1
typedef uint64_t word_t;
#elif defined(CONFIG_ISA32) && CONFIG_ISA32 == 1
typedef uint32_t word_t;
#else
#error "No ISA defined"
#endif

typedef word_t vaddr_t;
#include "isa-def.h"

// macro.h
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)

// another isa.h
typedef concat(__GUEST_ISA__, _CPU_state) CPU_state;

CPU_state qemu_regs;

const char *regs[] = {
        "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

static void isa_reg_display() {
    // print registers
    // pc
    printf("pc: 0x%lx ", qemu_regs.pc);
    // gpr
    for (int i = 0; i < sizeof(qemu_regs.gpr)/ sizeof(*qemu_regs.gpr); i++) {
        #if defined(CONFIG_ISA64) && CONFIG_ISA64 == 1
        uint64_t reg = qemu_regs.gpr[i]._64;
        if(reg) printf("%s: 0x%lx ", regs[i], reg);
        #elif defined(CONFIG_ISA32) && CONFIG_ISA32 == 1
        uint32_t reg = qemu_regs.gpr[i]._32;
        if(reg) printf("%s: 0x%x ", regs[i], reg);
        #else
        #error "No ISA defined"
        #endif
    }
    printf("\n");
}

const uint32_t img [] = {
        // taken from https://riscvasm.lucasteske.dev/
        0x3e800093, // addi x1 , x0,   1000  /* x1  = 1000 0x3E8 */
        0x7d008113, // addi x2 , x1,   2000  /* x2  = 3000 0xBB8 */
        0xc1810193, // addi x3 , x2,  -1000  /* x3  = 2000 0x7D0 */
        0x83018213, // addi x4 , x3,  -2000  /* x4  = 0    0x000 */
        0x3e820293, // addi x5 , x4,   1000  /* x5  = 1000 0x3E8 */
};

#define img_size sizeof(img)

#define instr_number (img_size / 4)

#endif //QEMU_DIFF_ISA_H
