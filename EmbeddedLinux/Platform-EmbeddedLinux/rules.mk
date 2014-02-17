include $(PLATFORM)/common.mk
-include $(PLATFORM)/local.mk
-include local.mk

COMMAND_PREFIX =
OBJECTS += $(OUTDIR)/$(BOARD).obj

$(OUTDIR)/%.obj: $(PLATFORM)/Hal/%.c | $(OUTDIR)
	$(CC) $< -o $@ $(CFLAGS)

var-check:
ifeq (,$(BOARD))
	$(error Error: BOARD not defined - edit local.mk in the Platform-EmbeddedLinux project)
endif

bb-uart1: /lib/firmware/BB-UART1-00A0.dtbo

/lib/firmware/BB-UART1-00A0.dtbo:
	dtc -O dtb -o $@ -b 0 -@ $(PLATFORM)/Setup/BB-UART1-00A0.dts

$(OUTFILE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(OUTFILE) $^
	$(SIZE) $(OUTFILE)

.PHONY: bb-uart1
