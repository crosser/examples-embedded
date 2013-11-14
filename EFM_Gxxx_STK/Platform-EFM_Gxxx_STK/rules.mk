include $(PLATFORM)/common.mk
include $(PLATFORM)/local.mk

TOOLS ?= $(EMMOCO-ROOT)/armtools/bin
GCCARCH = arm-none-eabi

COPTS = -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -DEFM32G890F128 $(CINCS) 
LDOPTS = -Map=$(OUTDIR)/$(MAIN).map -T $(PLATFORM)/efm32g.ld --entry Reset_Handler --gc-sections

CINCS = \
    -I$(EFM-PATH)/emlib/src \
    -I$(EFM-PATH)/emlib/inc \
    -I$(EFM-PATH)/Device/EnergyMicro/EFM32G/Source \
    -I$(EFM-PATH)/Device/EnergyMicro/EFM32G/Include \
    -I$(EFM-PATH)/CMSIS-3/Include

EXEC = cmd /c $(PLATFORM-PATH)/load.bat $(BINFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(PLATFORM)/startup_efm32g.S -o $(OUTDIR)/startup_efm32g.obj $(CFLAGS) 
	$(LD) -o $(OUTFILE) $^ $(OUTDIR)/startup_efm32g.obj $(LDOPTS)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(SIZE) $(OUTFILE)
