include $(PLATFORM)/common.mk

TOOLS ?= $(EMMOCO-ROOT)/msptools/bin
MCU = msp430fr5739

CC = $(TOOLS)/msp430-gcc
LD = $(TOOLS)/msp430-ld
OBJCOPY = $(TOOLS)/msp430-objcopy
SIZE = $(TOOLS)/msp430-size

COPTS = -std=gnu99 -O2 -w -ffunction-sections -fdata-sections -fpack-struct=1 -fno-strict-aliasing -fomit-frame-pointer -c -g -mmcu=$(MCU)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

EXEC = $(TOOLS)/MSP430Flasher -i USB -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s -q 

$(OUTFILE): $(OBJECTS)
	$(CC) -o $(OUTFILE) $^ $(LDOPTS)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(SIZE) $(OUTFILE)



