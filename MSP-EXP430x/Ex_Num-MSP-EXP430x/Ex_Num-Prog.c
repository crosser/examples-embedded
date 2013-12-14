#include "Ex_Num.h"
#include "Hal.h"

static Ex_Num_raw_t rawVal;

void main() {
    Hal_init();
    Ex_Num_start();
    Hal_idleLoop();
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Num_connectHandler(void) {
    Hal_connected();
}

void Ex_Num_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Num_smRange_fetch(Ex_Num_smRange_t* const output) {
    *output = (Ex_Num_smRange_t) rawVal;
}

void Ex_Num_smRange_store(Ex_Num_smRange_t* const input) {
    rawVal = (Ex_Num_raw_t) *input;
}

void Ex_Num_mdRange_fetch(Ex_Num_mdRange_t* const output) {
    *output = (Ex_Num_mdRange_t) rawVal;
}

void Ex_Num_mdRange_store(Ex_Num_mdRange_t* const input) {
    rawVal = (Ex_Num_raw_t) *input;
}

void Ex_Num_lgRange_fetch(Ex_Num_lgRange_t* const output) {
    *output = (Ex_Num_lgRange_t) rawVal;
}

void Ex_Num_lgRange_store(Ex_Num_lgRange_t* const input) {
    rawVal = (Ex_Num_raw_t) *input;
}

void Ex_Num_raw_fetch(Ex_Num_raw_t* const output) {
    *output = rawVal;
}

void Ex_Num_raw_store(Ex_Num_raw_t* const input) {
    rawVal = *input;
}
