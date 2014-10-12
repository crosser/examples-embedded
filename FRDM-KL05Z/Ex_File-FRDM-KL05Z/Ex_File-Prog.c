#include "Ex_File.h"
#include "Hal.h"

static Ex_File_fileSize_t fileSizeVal = 10;
static int seed;

void main() {
    Hal_init();
    Ex_File_start();
    Hal_idleLoop();
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_File_connectHandler(void) {
    Hal_connected();
}

void Ex_File_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_File_fileSize_fetch(Ex_File_fileSize_t* const output) {
    *output = fileSizeVal;
}

void Ex_File_fileSize_store(Ex_File_fileSize_t* const input) {
    fileSizeVal = *input;
}


uint16_t Ex_File_fileData_fetch(Ex_File_fileData_t output, int32_t offset, uint16_t count) {

    int32_t rem = fileSizeVal - offset;
    if (rem < count) {
        count = (uint16_t)rem;          // lowering count means this is the end of the file.
        Hal_ledOn();                    // Blink LED to indicate end-of-file.
        Hal_delay(100);
        Hal_ledOff();
    }
    for (uint16_t i = 0; i < count; i++) {
        output[i] = (seed + (offset + i)) & 0xFF;
    }
    return count;                       // return count < input count => signals EOF to the client app.
}

uint16_t Ex_File_fileData_store(Ex_File_fileData_t input, int32_t offset, uint16_t count) {
    if (offset == 0 && count) {
        seed = input[0];                // for this demo, only save the first byte.
    }
    if (count < Em_Message_DATASIZE) {  // input count < DATASIZE => EOF signalled from the client app.
        Hal_ledOn();                    // for this demo, this indicates end of file.
        Hal_delay(100);
        Hal_ledOff();
    }
    return count;
}
