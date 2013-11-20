include $(PLATFORM)/common.mk
include $(PLATFORM)/local.mk

TOOLS ?= $(EMMOCO-ROOT)/armtools/bin
GCCARCH = arm-none-eabi

ifeq ($(FAMILY), efm32g)
    MCU = EFM32G890F128
else ifeq ($(FAMILY), efm32gg)
    MCU = EFM32GG990F1024
endif

COPTS = -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -D$(MCU) -D$(FAMILY) -DSYSTEM=\"system_$(FAMILY).c\" $(CINCS) 
LDOPTS = -Map=$(OUTDIR)/$(MAIN).map -T $(PLATFORM)/$(FAMILY).ld --entry Reset_Handler --gc-sections

CINCS = \
    -I$(EFM-PATH)/emlib/src \
    -I$(EFM-PATH)/emlib/inc \
    -I$(EFM-PATH)/Device/EnergyMicro/$(FAMILY)/Source \
    -I$(EFM-PATH)/Device/EnergyMicro/$(FAMILY)/Include \
    -I$(EFM-PATH)/CMSIS-3/Include

EXEC = cmd /c $(PLATFORM-PATH)/load.bat $(MCU) $(BINFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(PLATFORM)/startup_$(FAMILY).S -o $(OUTDIR)/startup_$(FAMILY).obj $(CFLAGS) 
	$(LD) -o $(OUTFILE) $^ $(OUTDIR)/startup_$(FAMILY).obj $(LDOPTS)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(SIZE) $(OUTFILE)
