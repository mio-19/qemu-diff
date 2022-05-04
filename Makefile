NAME  = $(GUEST_ISA)-qemu
SRCS  = $(shell find src/ -name "*.c")

GUEST_ISA = riscv64

SHARE = 1
CFLAGS += -DNEMU_HOME=\"$(shell pwd)\" -DCONFIG_ISA_$(GUEST_ISA)
INC_PATH += include

include build.mk
