#include "Ex_Compound.h"
#include "Hal.h"

static Ex_Compound_infoArray_t infoArrayVal;

void main() {
    Hal_init();
    Ex_Compound_start();
    Hal_idleLoop();
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Compound_connectHandler(void) {
    Hal_connected();
}

void Ex_Compound_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Compound_infoArraySize_fetch(Ex_Compound_infoArraySize_t* output) {
    *output = sizeof(Ex_Compound_infoArray_t);
}

void Ex_Compound_infoArray_fetch(Ex_Compound_infoArray_t output) {

    // memcpy(output, &infoArrayVal, sizeof(Ex_Compound_infoArray_t));

    for (int i = 0; i < Ex_Compound_infoArray_length; i++) {
        for (int j = 0; j < Ex_Compound_Label_length; j++) {
            output[i].label[j] = infoArrayVal[i].label[j];
        }
        output[i].value = infoArrayVal[i].value;
    }
}

void Ex_Compound_infoArray_store(Ex_Compound_infoArray_t input) {

    // memcpy(&infoArrayVal, input, sizeof(Ex_Compound_infoArray_t));

    for (int i = 0; i < Ex_Compound_infoArray_length; i++) {
        for (int j = 0; j < Ex_Compound_Label_length; j++) {
            infoArrayVal[i].label[j] = input[i].label[j];
        }
        infoArrayVal[i].value = input[i].value;
    }
}

