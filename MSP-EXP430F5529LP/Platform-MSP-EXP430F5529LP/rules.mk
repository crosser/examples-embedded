include $(PLATFORM)/common.mk
-include $(PLATFORM)/local.mk
-include local.mk

ifeq (,$(COMPORT))
	COMPORT = USB
endif

TOOLS ?= $(EMMOCO-ROOT)/msptools/bin
GCCARCH = msp430
MCU = msp430f5529

COPTS = -mmcu=$(MCU)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

EXEC = $(EMMOCO-ROOT)/msptools/bin/MSP430Flasher -i $(COMPORT) -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s 

$(OUTFILE): $(OBJECTS)
	$(CC) -o $(OUTFILE) $^ $(LDOPTS)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(SIZE) $(OUTFILE)



