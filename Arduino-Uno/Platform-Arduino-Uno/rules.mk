include $(PLATFORM)/common.mk

TOOLS = c:/progs/WinAVR-20100110
MCU = atmega328p

CC = $(TOOLS)/bin/avr-gcc
OBJCOPY = $(TOOLS)/bin/avr-objcopy
SIZE = $(TOOLS)/bin/avr-size

COPTS = -std=gnu99 -w -g -O3 -fpack-struct=1 -ffunction-sections -fdata-sections -c -mmcu=$(MCU)
CFLAGS = -I$(PLATFORM)/Hal -IEm -I$(TOOLS)/avr/include $(COPTS)
LFLAGS = -mmcu=$(MCU) --entry __init -u __init -nostdlib -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

EXEC = c:/emmoco/workspace/Platform-Arduino-Uno/Avr/avrdude -C $(PLATFORM)/Avr/avrdude.conf -c stk500v1 -p $(MCU) -P COM7

$(OUTFILE): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(PLATFORM)/Avr/crt0.o $^ -T $(PLATFORM)/Avr/lnk.cmd
	$(SIZE) $@
