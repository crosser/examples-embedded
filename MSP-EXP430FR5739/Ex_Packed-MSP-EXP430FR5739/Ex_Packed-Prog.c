#include "Ex_Packed.h"
#include "Hal.h"

static Ex_Packed_p_t pVal;
static Ex_Packed_s_t sVal;

void main() {
    Hal_init();
    Ex_Packed_start();
    Hal_idleLoop();
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Packed_connectHandler(void) {
    Hal_connected();
}

void Ex_Packed_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Packed_p_fetch(Ex_Packed_p_t* const output) {
    *output = pVal;
}

void Ex_Packed_p_store(Ex_Packed_p_t* const input) {
    pVal = *input;      // copy into pVal before replicating in sVal
    sVal.e = Ex_Packed_P_e_get(pVal);
    for (int i = 0; i < Ex_Packed_A_length; i++) {
        sVal.a[i] = Ex_Packed_N_unpack(Ex_Packed_P_a_get(pVal, i));
    }
}

void Ex_Packed_s_fetch(Ex_Packed_s_t* const output) {
    *output = sVal;
}

void Ex_Packed_s_store(Ex_Packed_s_t* const input) {
    sVal = *input;      // copy into sVal before replicating in pVal
    Ex_Packed_P_e_set(&pVal, sVal.e);
    for (int i = 0; i < Ex_Packed_A_length; i++) {
        Ex_Packed_P_a_set(&pVal, i, Ex_Packed_N_pack(sVal.a[i]));
    }
}

void Ex_Packed_pSize_fetch(Ex_Packed_pSize_t* output) {
    *output = sizeof(Ex_Packed_p_t);
}

void Ex_Packed_sSize_fetch(Ex_Packed_sSize_t* output) {
    *output = sizeof(Ex_Packed_s_t);
}
