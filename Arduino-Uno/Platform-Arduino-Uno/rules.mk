include $(PLATFORM)/common.mk

WINAVR = c:/progs/WinAVR-20100110
TOOLS ?= $(WINAVR)/bin/avr
MCU = atmega328p

COPTS = -c -mmcu=$(MCU)
CFLAGS = -I$(PLATFORM)/Hal -IEm -I$(WINAVR)/avr/include $(COPTS)
LFLAGS = -mmcu=$(MCU) --entry __init -u __init -nostdlib -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

EXEC = c:/emmoco/workspace/Platform-Arduino-Uno/Avr/avrdude -C $(PLATFORM)/Avr/avrdude.conf -c stk500v1 -p $(MCU) -P COM7

$(OUTFILE): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(PLATFORM)/Avr/crt0.o $^ -T $(PLATFORM)/Avr/lnk.cmd
	$(SIZE) $@
