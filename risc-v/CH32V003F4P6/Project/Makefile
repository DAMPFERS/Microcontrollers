# Имя проекта
PROJECT = GPIO_Toggle

# Компилятор
# CC = riscv-none-elf-gcc
# OBJCOPY = riscv-none-elf-objcopy
# SIZE = riscv-none-elf-size
CC = riscv-none-embed-gcc
OBJCOPY = riscv-none-embed-objcopy
SIZE = riscv-none-embed-size

# Опции компилятора
# none-embed
CFLAGS = -march=rv32imac -mabi=ilp32 -mcmodel=medlow -Os -ffunction-sections -fdata-sections -Wall

# CFLAGS = -march=rv32imac_zicsr -mabi=ilp32 -mcmodel=medany -Os -ffunction-sections -fdata-sections -Wall

CFLAGS += -I./SRC/Core -I./SRC/Peripheral/inc -I./GPIO_Toggle/User -I./SRC/Debug -I./SRC/Peripheral/src
CFLAGS += -I"C:\MounRiver\MRS_Community\toolchain\RISC-V Embedded GCC\lib\gcc\riscv-none-embed\8.2.0\include"
CFLAGS += -I"C:\MounRiver\MRS_Community\toolchain\RISC-V Embedded GCC\lib\gcc\riscv-none-embed\8.2.0\include-fixed"
CFLAGS += -I"C:\MounRiver\MRS_Community\toolchain\RISC-V Embedded GCC\riscv-none-embed\include"






LDFLAGS = -nostartfiles -Wl,--gc-sections



# Файлы
SRCS = \
    ./GPIO_Toggle/User/main.c \
    ./SRC/Core/core_riscv.c \
	./SRC/Peripheral/src/ch32v00x_gpio.c \
	./SRC/Peripheral/src/ch32v00x_rcc.c \
	./SRC/Peripheral/src/ch32v00x_adc.c \
	./SRC/Peripheral/src/ch32v00x_dma.c \
	./SRC/Peripheral/src/ch32v00x_dbgmcu.c \
	./SRC/Peripheral/src/ch32v00x_exti.c \
	./SRC/Peripheral/src/ch32v00x_flash.c \
	./SRC/Peripheral/src/ch32v00x_i2c.c \
	./SRC/Peripheral/src/ch32v00x_iwdg.c \
	./SRC/Peripheral/src/ch32v00x_misc.c \
	./SRC/Peripheral/src/ch32v00x_opa.c \
	./SRC/Peripheral/src/ch32v00x_pwr.c \
	./SRC/Peripheral/src/ch32v00x_spi.c \
	./SRC/Peripheral/src/ch32v00x_tim.c \
	./SRC/Peripheral/src/ch32v00x_usart.c \
	./SRC/Peripheral/src/ch32v00x_wwdg.c \
	./SRC/Debug/debug.c \
	./GPIO_Toggle/User/ch32v00x_it.c \
	./GPIO_Toggle/User/system_ch32v00x.c \
    ./SRC/Startup/startup_ch32v00x.S

OBJS = $(SRCS:.c=.o)
LD_SCRIPT = ./SRC/Ld/Link.ld

# Цели
all: $(PROJECT).bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT).elf: $(OBJS)
	$(CC) $(CFLAGS) -T$(LD_SCRIPT) $(OBJS) -o $@ -Wl,--gc-sections

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
	$(SIZE) $<

clean:
	rm -f $(OBJS) $(PROJECT).elf $(PROJECT).bin
