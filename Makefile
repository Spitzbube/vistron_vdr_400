TARGET:=FreeRTOS

TOOLCHAIN_ROOT:=~/opt/xPacks/arm-none-eabi-gcc/xpack-arm-none-eabi-gcc-9.2.1-1.1
TOOLCHAIN_PATH:=$(TOOLCHAIN_ROOT)/bin
TOOLCHAIN_PREFIX:=arm-none-eabi

# Optimization level, can be [0, 1, 2, 3, s].
OPTLVL:=0 #1
DBG:=-g

FREERTOS:=$(CURDIR)/FreeRTOS
STARTUP:=$(CURDIR)/Core/Startup
LINKER_SCRIPT:=$(CURDIR)/STM32F103VETX_FLASH.ld

INCLUDE+=-I$(CURDIR)/.
INCLUDE+=-I$(FREERTOS)/include
INCLUDE+=-I$(FREERTOS)/portable/GCC/ARM_CM3
INCLUDE+=-I$(CURDIR)/Drivers/CMSIS/Device/ST/STM32F1xx/Include
INCLUDE+=-I$(CURDIR)/Drivers/CMSIS/Include
INCLUDE+=-I$(CURDIR)/Core/Inc

BUILD_DIR = $(CURDIR)/build
BIN_DIR = $(CURDIR)/binary

vpath %.c $(FREERTOS) \
          $(FREERTOS)/portable/MemMang \
          $(FREERTOS)/portable/GCC/ARM_CM3 

ASRC=startup_stm32f103vetx.s

#SRC+=stm32f1xx_it.c
SRC+=system_stm32f1xx.c
SRC+=main.c

# FreeRTOS Source Files
SRC+=port.c
SRC+=list.c
SRC+=tasks.c
SRC+=heap_4.c

CDEFS+=-DSTM32F103xE

MCUFLAGS=-mcpu=cortex-m3 -mthumb
COMMONFLAGS=-O$(OPTLVL) $(DBG)
CFLAGS=$(COMMONFLAGS) $(MCUFLAGS) $(INCLUDE) $(CDEFS)

LDFLAGS=$(MCUFLAGS) -u _scanf_float -u _printf_float -fno-exceptions -Wl,--gc-sections,-T$(LINKER_SCRIPT),-Map,$(BIN_DIR)/$(TARGET).map

CC=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-gcc
LD=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-gcc
OBJCOPY=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-objcopy
AS=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-as

OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: %.c
	@echo [CC] $(notdir $<)
	@$(CC) $(CFLAGS) $< -c -o $@

all: $(OBJ)
	@echo [AS] $(ASRC)
	@$(AS) -o $(ASRC:%.s=$(BUILD_DIR)/%.o) $(STARTUP)/$(ASRC)
	@echo [LD] $(TARGET).elf
	@$(CC) -o $(BIN_DIR)/$(TARGET).elf $(LDFLAGS) $(OBJ) $(ASRC:%.s=$(BUILD_DIR)/%.o) $(LDLIBS)
	@echo [HEX] $(TARGET).hex
	@$(OBJCOPY) -O ihex $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex
	@echo [BIN] $(TARGET).bin
	@$(OBJCOPY) -O binary $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin


clean:
	@echo [RM] OBJ
	@rm -f $(OBJ)
	@rm -f $(ASRC:%.s=$(BUILD_DIR)/%.o)
	@echo [RM] BIN
	@rm -f $(BIN_DIR)/$(TARGET).elf
	@rm -f $(BIN_DIR)/$(TARGET).hex
	@rm -f $(BIN_DIR)/$(TARGET).bin

