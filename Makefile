GUEST_ISA = riscv64

NAME  = $(GUEST_ISA)-qemu
SRCS  = $(shell find src/ -name "*.c")

SHARE = 1
CFLAGS += -DNEMU_HOME=\".\" -DCONFIG_ISA_$(GUEST_ISA)
INC_PATH += include src/isa/$(GUEST_ISA)/include

CFLAGS += -D__GUEST_ISA__=$(GUEST_ISA)

include build.mk

include main.mk