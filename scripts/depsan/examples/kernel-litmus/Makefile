# Makefile for kernel-litmus examples with depsan
# Include the main depsan Makefile
include ../../Makefile.depsan

# Set CONFIG_DEPSAN and LKMM_OUTDIR
CONFIG_DEPSAN := y
LKMM_OUTDIR := $(CURDIR)/depsan_output

# Define the source files
SRCS := addr.c data.c ctrl.c
OBJS := $(patsubst %.c, %.o, $(SRCS))

# Compiler to use (assuming clang is preferred for sanitizers)
CC ?= clang

# Default target
all: $(OBJS)

%.o: %.c
	@mkdir -p $(LKMM_OUTDIR)
	$(CC) $(CFLAGS_DEPSAN) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(LKMM_OUTDIR)

.PHONY: all clean
