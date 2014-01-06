OUTDIR = Output
EMDIR = Em
EMBUILDER = em-builder
COMMAND_PREFIX = $(GCCARCH)-
SCHEMAFILE = $(APPNAME).ems
MAIN = $(APPNAME)-Prog
BINFILE = $(OUTDIR)/$(MAIN).bin
HEXFILE = $(OUTDIR)/$(MAIN).hex
OUTFILE = $(OUTDIR)/$(MAIN).out
OBJECTS = $(OUTDIR)/$(MAIN).obj $(OUTDIR)/$(APPNAME).obj $(OUTDIR)/Hal.obj 

CC = $(COMMAND_PREFIX)gcc
LD = $(COMMAND_PREFIX)ld
OBJCOPY = $(COMMAND_PREFIX)objcopy
SIZE = $(COMMAND_PREFIX)size

CFLAGS = -std=gnu99 -O2 -w -ffunction-sections -fdata-sections -fpack-struct=1 -fno-strict-aliasing -fomit-frame-pointer -c -g -I$(PLATFORM)/Hal -IEm $(COPTS)

all: build

build: $(OUTFILE)

load: out-check
	$(EXEC)

clean:
ifeq (,$(findstring Windows,$(OS)))
	rm -rf $(EMDIR) $(OUTDIR)
else
ifneq (,$(wildcard $(EMDIR)))
	cmd /c rmdir /q /s $(subst /,\,$(EMDIR))
endif
ifneq (,$(wildcard $(OUTDIR)))
	cmd /c rmdir /q /s $(subst /,\,$(OUTDIR))
endif
endif

$(OUTDIR): | var-check
ifeq (,$(findstring Windows,$(OS)))
	mkdir $(OUTDIR)
else
	cmd /c mkdir $(OUTDIR)
endif

$(OUTDIR)/$(MAIN).obj: $(MAIN).c $(EMDIR)/$(APPNAME).c | $(OUTDIR)
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/$(APPNAME).obj: $(EMDIR)/$(APPNAME).c | $(OUTDIR)
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/Hal.obj: $(PLATFORM)/Hal/Hal.c | $(OUTDIR)
	$(CC) $< -o $@ $(CFLAGS) 

$(EMDIR)/$(APPNAME).c: $(SCHEMAFILE)
ifeq (,$(EMMOCO-ROOT))
	$(EMBUILDER) -v --root=$(<D) --outdir=$(EMDIR) --jsondir=$(EMDIR) $<
else
	@echo terminating because of prior schema errors 1>&2
	@exit 1
endif

local-clean: clean

out-check:
ifeq (,$(wildcard $(OUTFILE)))
	@echo error: $(OUTFILE): No such file or directory 1>&2
	@exit 1
endif

var-check:

.PHONY: all build load clean local-clean out-check var-check
