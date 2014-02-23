include $(PLATFORM)/common.mk
-include $(PLATFORM)/local.mk
-include local.mk

ifeq (,$(COMPORT))
	COMPORT = USB
endif

ifeq ($(BOARD), MSP_EXP430G2)
    MCU = msp430g2553
else ifeq ($(BOARD), MSP_EXP430F5529LP)
    MCU = msp430f5529
else ifeq ($(BOARD), MSP_EXP430F5438A)
    MCU = msp430f5438a
else ifeq ($(BOARD), MSP_EXP430FR5739)
    MCU = msp430fr5739
else ifeq ($(BOARD), MSP_EXP430FR5969)
    MCU = msp430fr5969
endif

GCCARCH = msp430

COPTS = -D$(BOARD) -mmcu=$(MCU)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections

ifeq (,$(findstring Windows,$(OS)))
EXEC = $(EMMOCO-ROOT)/msptools/bin/mspdebug rf2500 "prog $(OUTFILE)" 2>&1
else
EXEC = $(EMMOCO-ROOT)/msptools/bin/MSP430Flasher -i $(COMPORT) -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s 
endif

var-check:
ifeq (,$(BOARD))
	$(error Error: BOARD not defined - edit local.mk in the Platform-MSP-EXP430x project)
endif
ifeq (,$(MCU))
	$(error Error: BOARD "$(BOARD)" not known)
endif

$(OUTFILE): $(OBJECTS)
	$(CC) -o $(OUTFILE) $^ $(LDOPTS)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(SIZE) $(OUTFILE)



