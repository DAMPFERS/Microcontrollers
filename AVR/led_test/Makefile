#Main application file name
MAIN_APP = test2
#Main hex file path in windows format
MAIN_HEX_PATH = C:\PROGRAMS\Microcontrollers\AVR\led_test\$(MAIN_APP).hex

# Compiler and other Section
CC = avr-gcc
OBJCOPY = avr-objcopy.exe
AVRDUDE := avrdude 

#Options for avr-gcc
CFLAGS = -g -Os -o

#Linking options for avr-gcc
LFLAGS = -Os -mmcu=atmega168 -o

#Options for HEX file generation
HFLAGS = -j .text -j .data -O ihex

#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -c
DUDEFLAGS += arduino 
DUDEFLAGS += -p
DUDEFLAGS += m168  
DUDEFLAGS += -P 
DUDEFLAGS += COM9 
DUDEFLAGS += -b 
DUDEFLAGS += 19200 
DUDEFLAGS += -U flash:w:$(MAIN_HEX_PATH):i
DUDEFLAGS += -F

# Sources files needed for building the application 
SRC = $(MAIN_APP).c
SRC += 

# The headers files needed for building the application
INCLUDE = -I. 
INCLUDE += 

# commands Section
Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)

Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(MAIN_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@