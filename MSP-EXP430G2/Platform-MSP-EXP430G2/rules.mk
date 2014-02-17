include $(PLATFORM)/common.mk
-include $(PLATFORM)/local.mk
-include local.mk

GCCARCH = msp430
MCU = msp430g2553

COPTS = -mmcu=$(MCU)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

ifeq (,$(findstring Windows,$(OS)))
EXEC = $(EMMOCO-ROOT)/msptools/bin/mspdebug rf2500 "prog $(OUTFILE)" 2>&1
else
EXEC = $(EMMOCO-ROOT)/msptools/bin/MSP430Flasher -i USB -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s -q 
endif

$(OUTFILE): $(OBJECTS)
	$(CC) -o $(OUTFILE) $^ $(LDOPTS)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(SIZE) $(OUTFILE)



