OUTDIR = Output
EMBUILDER ?=
SCHEMAFILE = $(APPNAME).ems
MAIN = $(APPNAME)-Prog
OUTFILE = $(OUTDIR)/$(MAIN).out
HEXFILE = $(OUTDIR)/$(MAIN).hex
OBJECTS = $(OUTDIR)/$(MAIN).obj $(OUTDIR)/$(APPNAME).obj $(OUTDIR)/Hal.obj 

TOOLS ?= $(EMMOCO-ROOT)/msptools/bin
MCU = msp430g2553
CC = $(TOOLS)/msp430-gcc
LD = $(TOOLS)/msp430-ld
OBJCOPY = $(TOOLS)/msp430-objcopy
SIZE = $(TOOLS)/msp430-size
MSPDEBUG = $(TOOLS)/mspdebug
MSP430FLASHER = $(TOOLS)/MSP430Flasher
COPTS = -std=gnu99 -O2 -w -ffunction-sections -fdata-sections -fpack-struct=1 -fno-strict-aliasing -fomit-frame-pointer -c -g -mmcu=$(MCU)
CFLAGS = -I$(PLATFORM)/Hal -IEm $(COPTS)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections
RMFILES = *.out *.map *.hex *.obj

ifeq (,$(findstring Windows,$(OS)))
load: out-check
	$(MSPDEBUG) rf2500 "prog $(OUTFILE)" 2>&1
else
load: $(OUTFILE)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(MSP430FLASHER) -i USB -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s -q
endif

build: $(OUTDIR) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDOPTS)
	$(SIZE) $@

$(OUTDIR):
ifeq (,$(findstring Windows,$(OS)))
	mkdir $(OUTDIR)
else
	cmd /c mkdir $(OUTDIR)
endif

$(OUTDIR)/$(MAIN).obj: $(MAIN).c Em/$(APPNAME).c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/$(APPNAME).obj: Em/$(APPNAME).c
	$(CC) $< -o $@ $(CFLAGS) 

Em/$(APPNAME).c: $(SCHEMAFILE)
ifneq (,$(EMBUILDER))
	$(EMBUILDER) -v --root=$(<D) --outdir=Em --jsondir=Em $<
else
	@echo terminating because of prior schema errors 1>&2
	@exit 1
endif

$(OUTDIR)/Hal.obj: $(PLATFORM)/Hal/Hal.c
	$(CC) $< -o $@ $(CFLAGS) 

local-clean:
ifeq (,$(findstring Windows,$(OS)))
	rm -rf $(OUTDIR)
else
ifneq (,$(wildcard $(OUTDIR)))
	cmd /c rmdir /q /s $(subst /,\,$(OUTDIR))
endif
endif

clean: local-clean
ifeq (,$(findstring Windows,$(OS)))
	rm -rf $(EM)
else
ifneq (,$(wildcard Em))
	cmd /c rmdir /q /s $(subst /,\,Em)
endif
endif

out-check:
ifeq (,$(wildcard $(OUTFILE)))
	@echo error: $(OUTFILE): No such file or directory 1>&2
	@exit 1
endif

.PHONY: all load clean local-clean out-check
