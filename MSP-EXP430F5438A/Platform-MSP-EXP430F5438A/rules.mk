include $(PLATFORM)/common.mk

TOOLS ?= $(EMMOCO-ROOT)/msptools/bin
GCCARCH = msp430
MCU = msp430f5438a

COPTS = -mmcu=$(MCU)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

EXEC = $(EMMOCO-ROOT)/msptools/bin/MSP430Flasher -i USB -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s -q 

$(OUTFILE): $(OBJECTS)
	$(CC) -o $(OUTFILE) $^ $(LDOPTS)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(SIZE) $(OUTFILE)



