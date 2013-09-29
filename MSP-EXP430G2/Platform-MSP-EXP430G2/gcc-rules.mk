ifeq (,$(findstring Windows,$(OS)))
    SEP = :
else
    SEP = ;
endif

MCU = msp430g2553

OUTDIR = Output

include $(PLATFORM)/init.mk

PROGRAM-PROJ ?= ../$(APPNAME)-Program
SCHEMA-PROJ ?= ../$(APPNAME)-Schema
EMBUILDER ?=

SCHEMAFILE = $(SCHEMA-PROJ)/$(APPNAME).ems
EM = $(SCHEMA-PROJ)/Em
HAL = $(PLATFORM)/Hal
MAIN = $(APPNAME)-Prog
OUTFILE = $(OUTDIR)/$(MAIN).out
HEXFILE = $(OUTDIR)/$(MAIN).hex
OBJECTS = $(OUTDIR)/$(MAIN).obj $(OUTDIR)/$(APPNAME).obj $(OUTDIR)/Hal.obj 

CC = msp430-gcc
LD = msp430-ld
OBJCOPY = msp430-objcopy
SIZE = msp430-size
MSPDEBUG = mspdebug
MSP430FLASHER = MSP430Flasher
COPTS = -std=gnu99 -O2 -w -fpack-struct=1 -fno-strict-aliasing -fomit-frame-pointer -c -g -mmcu=$(MCU)
CFLAGS = -I$(HAL) -I$(EM) $(COPTS)
LDOPTS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(MAIN).map
RMFILES = *.out *.map *.hex *.obj
VPATH = $(PROGRAM-PROJ)$(SEP)$(EM)$(SEP)$(HAL)

build: $(OUTDIR) $(OUTFILE)

ifeq (,$(findstring Windows,$(OS)))
load: out-check
	$(MSPDEBUG) rf2500 "prog $(OUTFILE)" 2>&1
else
load: $(OUTFILE)
	$(OBJCOPY) -O ihex $(OUTFILE) $(HEXFILE)
	$(MSP430FLASHER) -i USB -m AUTO -e ERASE_MAIN -n $(MCU) -w $(HEXFILE) -v -z [VCC] -g -s -q
endif

$(OUTFILE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDOPTS)
	$(SIZE) $@

$(OUTDIR):
ifeq (,$(findstring Windows,$(OS)))
	mkdir $(OUTDIR)
else
	cmd /c mkdir $(OUTDIR)
endif

$(OUTDIR)/$(MAIN).obj: $(MAIN).c $(EM)/$(APPNAME).c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/$(APPNAME).obj: $(EM)/$(APPNAME).c
	$(CC) $< -o $@ $(CFLAGS) 

$(EM)/$(APPNAME).c: $(SCHEMAFILE)
ifneq (,$(EMBUILDER))
	$(EMBUILDER) -v --root=$(<D) --outdir=$(EM) --jsondir=$(EM) $<
else
	@echo terminating because of prior schema errors 1>&2
	@exit 1
endif

$(OUTDIR)/Hal.obj: $(HAL)/Hal.c
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
ifneq (,$(wildcard $(EM)))
	cmd /c rmdir /q /s $(subst /,\,$(EM))
endif
endif

out-check:
ifeq (,$(wildcard $(OUTFILE)))
	@echo error: $(OUTFILE): No such file or directory 1>&2
	@exit 1
endif

.PHONY: all load clean local-clean out-check
