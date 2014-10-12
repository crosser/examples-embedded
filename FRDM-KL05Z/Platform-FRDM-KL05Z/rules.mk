include $(PLATFORM)/common.mk
-include $(PLATFORM)/local.mk
-include local.mk

TOOLS ?= $(EMMOCO-ROOT)/armtools/bin
GCCARCH = arm-none-eabi

COPTS = -mthumb -mcpu=cortex-m0 -I$(PLATFORM)/ProcessorExpert/Generated_Code -I$(PLATFORM)/ProcessorExpert/Sources -I$(PLATFORM)/ProcessorExpert/Static_Code/IO_Map -I$(PLATFORM)/ProcessorExpert/Static_Code/PDD 
LDOPTS = -Map=$(OUTDIR)/$(MAIN).map -T $(PLATFORM)/ProcessorExpert/Project_Settings/Linker_Files/ProcessorExpert.ld --gc-sections

EXEC = cmd /c copy $(OUTDIR)\$(MAIN).bin d:

COMPONENTS = \
    $(OUTDIR)/BUTTON.obj \
    $(OUTDIR)/CONNECTED.obj \
    $(OUTDIR)/DEBUG1.obj \
    $(OUTDIR)/DEBUG2.obj \
    $(OUTDIR)/EAP_RX_ACK.obj \
    $(OUTDIR)/EAP_TX_ACK.obj \
    $(OUTDIR)/LED.obj \
    $(OUTDIR)/TIMER.obj \
    $(OUTDIR)/TU1.obj \
    $(OUTDIR)/TU2.obj \
    $(OUTDIR)/UART.obj \
    $(OUTDIR)/WATCH.obj \

$(COMPONENTS):
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/BUTTON.c -o $(OUTDIR)/BUTTON.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/CONNECTED.c -o $(OUTDIR)/CONNECTED.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/DEBUG1.c -o $(OUTDIR)/DEBUG1.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/DEBUG2.c -o $(OUTDIR)/DEBUG2.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/EAP_RX_ACK.c -o $(OUTDIR)/EAP_RX_ACK.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/EAP_TX_ACK.c -o $(OUTDIR)/EAP_TX_ACK.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/LED.c -o $(OUTDIR)/LED.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/TIMER.c -o $(OUTDIR)/TIMER.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/TU1.c -o $(OUTDIR)/TU1.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/TU2.c -o $(OUTDIR)/TU2.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/UART.c -o $(OUTDIR)/UART.obj $(CFLAGS) 
	$(CC) $(PLATFORM)/ProcessorExpert/Generated_Code/WATCH.c -o $(OUTDIR)/WATCH.obj $(CFLAGS) 

$(OUTFILE): $(OBJECTS) $(COMPONENTS)
	$(CC) $(PLATFORM)/ProcessorExpert/Project_Settings/Startup_Code/startup.c -o $(OUTDIR)/startup.obj $(CFLAGS) 
	$(LD) -o $(OUTFILE) $^ $(OUTDIR)/startup.obj  $(LDOPTS)
	$(OBJCOPY) -O binary $(OUTFILE) $(BINFILE)
	$(SIZE) $(OUTFILE)
