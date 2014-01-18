include $(PLATFORM)/common.mk

COMMAND_PREFIX =

$(OUTFILE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(OUTFILE) $^ -lpthread
	$(SIZE) $(OUTFILE)
