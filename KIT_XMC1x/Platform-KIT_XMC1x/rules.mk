include $(PLATFORM)/common.mk
-include $(PLATFORM)/local.mk
-include local.mk

ifeq ($(BOARD), KIT_XMC11_BOOT_001)
    UC_ID = 1101007
    MCU = XMC1100
    DEVICE = XMC1100-T038F0064
else ifeq ($(BOARD), KIT_XMC13_BOOT_001)
    UC_ID = 1301027
    MCU = XMC1300
    DEVICE = XMC1302-T038X0200
endif

TOOLS ?= $(EMMOCO-ROOT)/armtools/bin
GCCARCH = arm-none-eabi

COPTS = \
	-DUC_ID=$(UC_ID) -DDAVE_CE -D$(BOARD) $(CINCS) -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft \
	-c -fmessage-length=0 -MMD -MP -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2
	
LDLIBS = \
	-L$(DAVE-PATH)/CMSIS/Infineon/Lib \
	-L$(DAVE-PATH)/Examples/Lib \
	-L$(DAVE-PATH)/emWin/Start/GUI \
	-L$(DAVE-PATH)/ARM-GCC/lib/gcc/arm-none-eabi/4.7.4/armv6-m

LDOPTS = \
	-T $(PLATFORM)/$(BOARD)/ldfile.ld \
	-nostartfiles \
	$(LDLIBS) \
	-lgcc -Map=$(OUTDIR)/$(MAIN).map 

CINCS = \
	-I$(PLATFORM)/Hal \
	-I$(PLATFORM)/$(BOARD)/Dave/Generated/inc/LIBS \
	-I$(PLATFORM)/$(BOARD)/Dave/Generated/inc/MOTORLIBS \
	-I$(PLATFORM)/$(BOARD)/Dave/Generated/inc/MATHLIBS \
	-I$(PLATFORM)/$(BOARD)/Dave/Generated/inc/DAVESupport \
	-I$(DAVE-PATH)/CMSIS/Include \
	-I$(DAVE-PATH)/CMSIS/Infineon/Include \
	-I$(DAVE-PATH)/ARM-GCC/arm-none-eabi/include \
	-I$(DAVE-PATH)/emWin/Start/GUI/inc \
	-I$(DAVE-PATH)/CMSIS/Infineon/$(MCU)_series/Include

EXEC = cmd /c $(PLATFORM-PATH)/load.bat $(BINFILE) $(DEVICE)

DAVEOBJECTS = \
	$(OUTDIR)/startup_$(MCU).obj \
	$(OUTDIR)/system_$(MCU).obj \
	$(OUTDIR)/System_LibcStubs.obj \
	$(OUTDIR)/CLK002.obj \
	$(OUTDIR)/DAVE3.obj $(OUTDIR)/MULTIPLEXER.obj \
	$(OUTDIR)/ERU001_Conf.obj $(OUTDIR)/ERU001.obj \
	$(OUTDIR)/ERU002_Conf.obj $(OUTDIR)/ERU002.obj \
	$(OUTDIR)/IO002_Conf.obj $(OUTDIR)/IO002.obj \
	$(OUTDIR)/IO004_Conf.obj $(OUTDIR)/IO004.obj \
	$(OUTDIR)/NVIC002_Conf.obj $(OUTDIR)/NVIC002.obj \
	$(OUTDIR)/SYSTM001.obj \
	$(OUTDIR)/UART001_Conf.obj $(OUTDIR)/UART001.obj

$(OUTFILE): $(OBJECTS) $(DAVEOBJECTS)
	$(LD) $^ $(LDOPTS) -o $(OUTFILE)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(SIZE) $(OUTFILE)

$(OUTDIR)/startup_$(MCU).obj: $(PLATFORM)/$(BOARD)/Startup/startup_$(MCU).s
	$(CC) -x assembler-with-cpp $< -o $@ $(CFLAGS) 

$(OUTDIR)/system_$(MCU).obj: $(PLATFORM)/$(BOARD)/Startup/system_$(MCU).c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/System_LibcStubs.obj: $(PLATFORM)/Lib/System_LibcStubs.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/CLK002.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/CLK002/CLK002.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/DAVE3.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/DAVESupport/DAVE3.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/MULTIPLEXER.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/DAVESupport/MULTIPLEXER.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/ERU001_Conf.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/ERU001/ERU001_Conf.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/ERU001.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/ERU001/ERU001.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/ERU002_Conf.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/ERU002/ERU002_Conf.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/ERU002.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/ERU002/ERU002.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/IO002_Conf.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/IO002/IO002_Conf.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/IO002.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/IO002/IO002.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/IO004_Conf.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/IO004/IO004_Conf.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/IO004.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/IO004/IO004.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/NVIC002_Conf.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/NVIC002/NVIC002_Conf.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/NVIC002.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/NVIC002/NVIC002.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/SYSTM001.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/SYSTM001/SYSTM001.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/UART001_Conf.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/UART001/UART001_Conf.c
	$(CC) $< -o $@ $(CFLAGS) 

$(OUTDIR)/UART001.obj: $(PLATFORM)/$(BOARD)/Dave/Generated/src/UART001/UART001.c
	$(CC) $< -o $@ $(CFLAGS) 
	
