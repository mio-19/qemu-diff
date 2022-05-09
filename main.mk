CFLAGS += -D__GUEST_ISA__=$(GUEST_ISA)

INC_PATH += src/isa/$(GUEST_ISA)

build/diffTest: $(SRCS) main.c
	$(CC) $(CFLAGS) -o $@ $^