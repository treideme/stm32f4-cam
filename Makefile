## Makefile for STM32F4
# @author Thomas Reidemeister <treideme@uwaterloo.ca>
# @date 2013.01.27
TARGET=main
EXECUTABLE=main.elf

## Tool configuration
CC=arm-none-eabi-gcc
#LD=arm-none-eabi-ld 
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
SZ=arm-none-eabi-size
BIN=$(CP) -O ihex 

## Flags
LDFLAGS=-Wl,-T,stm32_flash.ld
CPU=cortex-m4
LIBS=-lm

# USE Peripheral library, use FPU
DEFS=-DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx
# -DUSE_USB_OTG_FS
OPTIMIZE=-Os -g -std=gnu99
MCFLAGS= -fno-common -mcpu=$(CPU) -mthumb -mthumb-interwork \
         -mfpu=fpv4-sp-d16 -fsingle-precision-constant -mfloat-abi=softfp \
         -Wall -Wextra -Wno-unused-parameter -Wno-pointer-sign -funsigned-char

## Configuration of paths
STM32_INCLUDES = -Isrc \
	-Iinc \
	-ICMSIS/Include \
	-ISTM32F4xx_StdPeriph_Driver/inc \
	-IUtilities/STM32F4-Discovery/ \
	-IUtilities/FatFs_vR0.08a/
	
	
#	-ISTM32_USB_OTG_Driver/inc \
#	-ISTM32_USB_Device_Library/Core/inc \
#	-ISTM32_USB_Device_Library/Class/cdc/inc/ \

CFLAGS	= $(MCFLAGS) $(OPTIMIZE) $(DEFS) $(STM32_INCLUDES)
AFLAGS	= $(MCFLAGS) 

## Source files
# - src:      all source files automatically
# - usb:      all source files automatically
# - periph:   to save code they are explicitly listed
	#$(wildcard STM32_USB_Device_Library/Class/cdc/src/*.c) \

SRC = $(wildcard src/*.c) \
	STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
	STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
	STM32F4xx_StdPeriph_Driver/src/misc.c \
	$(wildcard Utilities/STM32F4-Discovery/*.c) \
	$(wildcard Utilities/FatFs_vR0.08a/*.c)
	
	

#	$(wildcard vcp_driver/*.c) \
#	$(wildcard kcd/*.c) \
#	$(wildcard parsing/*.c) \
#	STM32_USB_Device_Library/Core/src/usbd_ioreq.c \
#	STM32_USB_Device_Library/Core/src/usbd_req.c \
#	STM32_USB_Device_Library/Core/src/usbd_core.c \
#	STM32_USB_Device_Library/Class/cdc/src/usbd_cdc_core.c \
#	STM32_USB_OTG_Driver/src/usb_core.c \
#	STM32_USB_OTG_Driver/src/usb_dcd.c \
#	STM32_USB_OTG_Driver/src/usb_dcd_int.c \

STARTUP = src/startup_stm32f40xx.s

OBJDIR = .
OBJ = $(SRC:%.c=$(OBJDIR)/%.o) 
OBJ += Startup.o

all: $(TARGET).hex

$(TARGET).hex: $(EXECUTABLE)
	$(CP) -O ihex $^ $@

$(EXECUTABLE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@
	$(OD) -h -S $@ > $(TARGET).lst
	$(SZ) $(TARGET).elf
	
program: $(TARGET).hex
	openocd -f openocd.cfg \
	-c 'init; reset halt; flash write_image erase $(TARGET).elf; \
	verify_image $(TARGET).elf; reset run; shutdown'

#kcd/kcd_scanner.c: kcd/kcd_scanner.y kcd/kcd_scanner.l
#	cd kcd && ./bootstrap.sh

debug:
	openocd -f openocd.cfg \
	-c 'telnet_port 4444; gdb_port 3333; init; reset halt'

#test:
#	./bin/test
#
#bootstrap:
#	./bin/bootstrap

clean:
	rm -f $(TARGET)  $(TARGET).lst $(OBJ) $(AUTOGEN)  $(TARGET).out  $(TARGET).hex  $(TARGET).map \
	 $(TARGET).dmp  $(TARGET).elf _test_*.so
