#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"

#define RESET_VECTOR (CONFIG_MBASE + CONFIG_PC_RESET_OFFSET)

void difftest_init(int port);
void difftest_regcpy(void *dut, bool direction);
void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction);
void difftest_exec(uint64_t n);

int main(int argc, char *argv[]) {
    int port = 8888;
    // exit if the number of arguments is not 2
    if (argc == 2) {
        // get port number from command line
        port = atoi(argv[1]);
    } else if (argc >= 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }
    // initialize difftest
    difftest_init(port);
    difftest_memcpy(RESET_VECTOR, (void *) img, img_size, DIFFTEST_TO_REF);

    // run the program
    difftest_regcpy(&qemu_regs, DIFFTEST_TO_DUT);
    qemu_regs.pc = RESET_VECTOR;
    difftest_regcpy(&qemu_regs, DIFFTEST_TO_REF);
    difftest_regcpy(&qemu_regs, DIFFTEST_TO_DUT);
    int c = instr_number;
    while (c--) {
        difftest_exec(1);
        difftest_regcpy(&qemu_regs, DIFFTEST_TO_DUT);
        do_isa_reg_display();
    }

    return 0;
}