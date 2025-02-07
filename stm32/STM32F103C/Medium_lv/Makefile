TARGET = firmware
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
PROGRAMMER = "C:/ST/STM32CubeCLT_1.16.0/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"

CFLAGS = -mcpu=cortex-m3 -mthumb -g -O2 -Wall -ffunction-sections -fdata-sections \
         -ICore/Inc -IDrivers/CMSIS/Include -IDrivers/CMSIS/Device/ST/STM32F1xx/Include \
         -IDrivers/STM32F1xx_HAL_Driver/Inc -DSTM32F103xB

LDFLAGS = -TSTM32F103C8TX_FLASH.ld -Wl,--gc-sections

SRCS = Core/Src/main.c \
       Core/Src/stm32f1xx_it.c \
       Core/Src/system_stm32f1xx.c \
       Core/Startup/startup_stm32f103c8tx.s \
       Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
       Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
       Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
       Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
       Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: $(TARGET).elf
	$(PROGRAMMER) -c port=SWD -w $(TARGET).elf

clean:
	rm -f $(TARGET).elf $(TARGET).bin $(OBJS)
