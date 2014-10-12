#include "Ex_Rename.h"
#include "Hal.h"

static Ex_Rename_newName_t nameVal;
static bool renameFlag = false;

void main() {
	Hal_init();
    // most apps will bind a "known" name here 
    // Ex_Rename_setDeviceName(...);
	Ex_Rename_start();    
	Hal_idleLoop();
}

void Ex_Rename_connectHandler(void) {
    Hal_connected();
}

void Ex_Rename_disconnectHandler(void) {
    Hal_disconnected();
    if (renameFlag) {
        renameFlag = false;
        Ex_Rename_setDeviceName(nameVal[0] ? nameVal : 0);
        Ex_Rename_reset();
        Ex_Rename_start();
    }
}

void Ex_Rename_newName_store(Ex_Rename_newName_t input) {
    for (int i = 0; i < Ex_Rename_newName_length; i++) {
        nameVal[i] = input[i];
    }
    renameFlag = true;
}
