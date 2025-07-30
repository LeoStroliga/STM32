PROJECT = bootloader
CHIP = stm32f4
OPENCM3_DIR = ../libopencm3

# Output files
BINARY = $(PROJECT).elf
HEX    = $(PROJECT).hex
BIN    = $(PROJECT).bin

# Source folders
SRCDIR = src
INCDIR = inc

# Find all .c source files
SRC = $(wildcard src/**/*.c) $(wildcard src/*.c) startup.c
OBJS = $(SRC:.c=.o)

# Compiler
CC = arm-none-eabi-gcc
CFLAGS = -g -O0 -Wall -Wextra \
         -I$(OPENCM3_DIR)/include -I$(INCDIR) \
         -mcpu=cortex-m4 -mthumb -nostdlib -MD -MP \
         -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F4

# Linker
LDFLAGS = -Tlinker.ld -nostartfiles -Wl,--gc-sections,--exclude-libs=ALL,-Map=$(PROJECT).map \
          -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
          -L$(OPENCM3_DIR)/lib -lopencm3_$(CHIP)

# Targets
all: $(BINARY) $(HEX) $(BIN)

$(BINARY): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.hex: %.elf
	arm-none-eabi-objcopy -O ihex $< $@

%.bin: %.elf
	arm-none-eabi-objcopy -O binary $< $@
	python pad-bootloader.py

clean:
	del /Q /S *.o *.d $(BINARY) $(HEX) $(BIN) 2>nul || exit 0

flash: $(BINARY)
	st-flash write $(BIN) 0x8000000
