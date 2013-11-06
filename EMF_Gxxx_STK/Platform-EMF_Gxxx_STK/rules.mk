include $(PLATFORM)/common.mk
include $(PLATFORM)/local.mk

#TOOLS ?= $(SOURCERY-PATH)/bin/arm-none-eabi
TOOLS ?= $(SOURCERY-PATH)/bin
GCCARCH = arm-none-eabi

COPTS = -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -DEFM32G890F128 $(CINCS) 
LDOPTS = -mthumb -mcpu=cortex-m3 -Wl,-Map=$(OUTDIR)/$(MAIN).map,--gc-sections -T $(EFM-PATH)/Device/EnergyMicro/EFM32G/Source/G++/efm32g.ld -Wl,--start-group -lgcc -lc -lcs3 -lcs3unhosted -Wl,--end-group

CINCS = \
    -I$(EFM-PATH)/emlib/src \
    -I$(EFM-PATH)/emlib/inc \
    -I$(EFM-PATH)/Device/EnergyMicro/EFM32G/Source \
    -I$(EFM-PATH)/Device/EnergyMicro/EFM32G/Include \
    -I$(EFM-PATH)/CMSIS-3/Include

EXEC = cmd /c $(PLATFORM-PATH)/load.bat $(BINFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(EFM-PATH)/Device/EnergyMicro/EFM32G/Source/G++/startup_efm32g.S -o $(OUTDIR)/startup_efm32g.obj $(CFLAGS) 
	$(CC) -o $(OUTFILE) $^ $(OUTDIR)/startup_efm32g.obj $(LDOPTS)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(SIZE) $(OUTFILE)

	