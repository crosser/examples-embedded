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
BINFILE = $(OUTDIR)/$(MAIN).bin
OBJECTS = $(OUTDIR)/$(MAIN).obj $(OUTDIR)/$(APPNAME).obj $(OUTDIR)/Hal.obj 

CC = c:/progs/sourcery/bin/arm-stellaris-eabi-gcc
OBJCOPY = c:/progs/sourcery/bin/arm-stellaris-eabi-objcopy
SIZE = c:/progs/sourcery/bin/arm-stellaris-eabi-size
LMFLASH = c:/progs/lmflash/lmflash
COPTS = -std=gnu99 -O2 -w -fpack-struct=1 -fno-strict-aliasing -fomit-frame-pointer -c -g
CFLAGS = -Dsourcerygxx -DTARGET_IS_BLIZZARD_RA1 -DPART_LM4F120H5QR -I$(HAL) -I$(PLATFORM)/StellarisWare -I$(EM) $(COPTS)
LDOPTS = -Xlinker -Map=$(OUTDIR)/$(MAIN).map -L$(PLATFORM)/StellarisWare/driverlib/gcc-cm4f -ldriver-cm4f -lm -T ekc-lm4f232-rom.ld -T $(PLATFORM)/Hal/Hal.ld
RMFILES = *.out *.map *.bin *.obj
VPATH = $(PROGRAM-PROJ)$(SEP)$(EM)$(SEP)$(HAL)

build: $(OUTDIR) $(OUTFILE)

load: $(OUTFILE)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(LMFLASH) -v -r $(BINFILE) >nul

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
