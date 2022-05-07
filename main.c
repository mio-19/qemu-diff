#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"

#define RESET_VECTOR (CONFIG_MBASE + CONFIG_PC_RESET_OFFSET)

void difftest_init(int port);
void difftest_regcpy(void *dut, bool direction);
void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction);

int main(int argc, char *argv[]) {
    // exit if the number of arguments is not 2
    if (argc != 2) {
        printf("Usage: ./main <port>\n");
        return 1;
    }
    // get port number from command line
    int port = atoi(argv[1]);
    // initialize difftest
    difftest_init(port);
    difftest_memcpy(RESET_VECTOR, (void*) img, img_size, DIFFTEST_TO_REF);

    // run the program
    int c = instr_number;
    while (c--) {
        ref_difftest_exec(1);
        difftest_regcpy(&qemu_r, DIFFTEST_TO_DUT);
        isa_reg_display();
    }

    return 0;
}