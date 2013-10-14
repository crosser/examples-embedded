include $(PLATFORM)/common.mk

TOOLS ?= $(EMMOCO-ROOT)/armtools/bin/arm-none-eabi

CC = $(TOOLS)-gcc
LD = $(TOOLS)-ld
OBJCOPY = $(TOOLS)-objcopy
SIZE = $(TOOLS)-size

COPTS = -mthumb -mcpu=cortex-m4 -std=gnu99 -O2 -w -ffunction-sections -fdata-sections -fpack-struct=1 -fno-strict-aliasing -fomit-frame-pointer -c -g
CFLAGS = -Dsourcerygxx -DTARGET_IS_BLIZZARD_RA1 -DPART_LM4F120H5QR -I$(PLATFORM)/Hal -I$(PLATFORM)/StellarisWare -IEm $(COPTS)
LDOPTS = -Map=$(OUTDIR)/$(MAIN).map -L$(PLATFORM)/StellarisWare/driverlib/gcc-cm4f -ldriver-cm4f -T $(PLATFORM)/ek-lm4f232.ld --entry ResetISR --gc-sections

EXEC = $(EMMOCO-ROOT)/armtools/LMFlash/LMFlash -v -r $(BINFILE) >nul

$(OUTFILE): $(OBJECTS)
	$(CC) $(PLATFORM)/startup_gcc.c -o $(OUTDIR)/startup_gcc.obj $(CFLAGS) 
	$(LD) -o $(OUTFILE) $^ $(OUTDIR)/startup_gcc.obj $(LDOPTS)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(SIZE) $(OUTFILE)
