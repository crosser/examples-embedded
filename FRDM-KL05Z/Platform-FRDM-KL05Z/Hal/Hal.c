/*
 * ============ Hardware Abstraction Layer for FRDM-KL05Z ============
 */

#include "Hal.h"
#include "Em_Message.h"

/* -------- INTERNAL FEATURES -------- */

#include "Cpu.c"
#include "Events.c"
#include "PE_LDD.c"
#include "Vectors.c"

#include "BUTTON.h"
#include "CONNECTED.h"
#include "DEBUG1.h"
#include "DEBUG2.h"
#include "EAP_RX_ACK.h"
#include "EAP_TX_ACK.h"
#include "LED.h"
#include "TIMER.h"
#include "UART.h"
#include "WATCH.h"

#define DINT()                      (Cpu_DisableInt())
#define EINT()                      (Cpu_EnableInt())
#define SLEEP()                     do { PE_WFI(); Cpu_EnableInt(); } while (0)
#define WAKEUP()

#define NUM_HANDLERS 3

#define BUTTON_HANDLER_ID      0
#define TICK_HANDLER_ID        1
#define DISPATCH_HANDLER_ID    2

static void buttonHandler(void);
static void postEvent(uint8_t handlerId);

static Hal_Handler appButtonHandler;
static uint16_t clockTick = 0;
static volatile uint16_t handlerEvents = 0;
static Hal_Handler handlerTab[NUM_HANDLERS];
static uint8_t inByte;

/* -------- APP-HAL INTERFACE -------- */

void Hal_buttonEnable(Hal_Handler handler) {
    handlerTab[BUTTON_HANDLER_ID] = buttonHandler;
    appButtonHandler = handler;
    BUTTON_Enable(BUTTON_DeviceData);
}

void Hal_connected(void) {
    CONNECTED_ClrVal(CONNECTED_DeviceData);
}

void Hal_debugOn(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_SetVal(DEBUG1_DeviceData);
        break;
    case 2:
        DEBUG2_SetVal(DEBUG2_DeviceData);
        break;
    }
}

void Hal_debugOff(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_ClrVal(DEBUG1_DeviceData);
        break;
    case 2:
        DEBUG2_ClrVal(DEBUG2_DeviceData);
        break;
    }
}

void Hal_debugPulse(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_SetVal(DEBUG1_DeviceData);
        DEBUG1_ClrVal(DEBUG1_DeviceData);
        break;
    case 2:
        DEBUG2_SetVal(DEBUG2_DeviceData);
        DEBUG2_ClrVal(DEBUG2_DeviceData);
        break;
    }
}

void Hal_delay(uint16_t msecs) {
    volatile uint32_t cnt = msecs * 1024;
    volatile uint32_t dummy;
    while (cnt--) {
        dummy = 0;
        dummy = 0;
        dummy = 0;
        dummy = 0;
        dummy = 0;
        dummy = 0;
        dummy = 0;
    }
}

void Hal_disconnected(void) {
    CONNECTED_SetVal(CONNECTED_DeviceData);
}

void Hal_init() {
    PE_low_level_init();
    TIMER_Disable(TIMER_DeviceData);
    handlerTab[DISPATCH_HANDLER_ID] = Em_Message_dispatch;
}

void Hal_idleLoop(void) {
    EINT();
    for (;;) {
        // atomically read/clear all handlerEvents
        DINT();
        uint16_t events = handlerEvents;
        handlerEvents = 0;
        if (events) {   // dispatch all current events
            EINT();
            uint16_t mask;
            uint8_t id;
            for (id = 0, mask = 0x1; id < NUM_HANDLERS; id++, mask <<= 1) {
                if ((events & mask) && handlerTab[id]) {
                    handlerTab[id]();
                }
            }
        }
        else {          // await more events
            SLEEP();
        }
    }
}

void Hal_ledOn(void) {
    LED_ClrVal(LED_DeviceData);
}

void Hal_ledOff(void) {
    LED_SetVal(LED_DeviceData);
}

bool Hal_ledRead(void) {
    return !LED_GetVal(LED_DeviceData);
}

void Hal_ledToggle(void) {
    LED_PutVal(LED_DeviceData, !LED_GetVal(LED_DeviceData));
}

void Hal_tickStart(uint16_t msecs, void (*handler)(void)) {
    handlerTab[TICK_HANDLER_ID] = handler;
    PIT_LDVAL0 = PIT_LDVAL_TSV(0x51EB * msecs);
    TIMER_Enable(TIMER_DeviceData);
}

/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
    EnterCritical();
    return 0;
}

void Em_Hal_reset(void) {
    uint8_t key = Em_Hal_lock();
    EAP_RX_ACK_ClrVal(EAP_RX_ACK_DeviceData);    // suspend the MCM
    Hal_delay(100);
    EAP_RX_ACK_SetVal(EAP_RX_ACK_DeviceData);    // reset the MCM
    Hal_delay(500);
    EAP_TX_ACK_Enable(EAP_TX_ACK_DeviceData);
    UART_Enable(UART_DeviceData);    
    UART_ReceiveBlock(UART_DeviceData, &inByte, 1);
    Em_Hal_unlock(key);
}

void Em_Hal_startSend(void) {
    uint8_t b = Em_Message_startTx();
    UART_SendBlock(UART_DeviceData, &b, 1);
}

void Em_Hal_unlock(uint8_t key) {
    ExitCritical();
}

void Em_Hal_watchOn(void) {
    WATCH_Enable(WATCH_DeviceData);
}

void Em_Hal_watchOff(void) {
    WATCH_Disable(WATCH_DeviceData);
}

/* -------- INTERNAL FUNCTIONS -------- */

static void buttonHandler(void) {
    Hal_delay(100);
    if (BUTTON_GetVal(NULL) == 0 && appButtonHandler) {
        appButtonHandler();
    }
}

static void postEvent(uint8_t handlerId) {
    uint8_t key = Em_Hal_lock();
    handlerEvents |= 1 << handlerId;
    Em_Hal_unlock(key);
}

/* -------- INTERRUPT SERVICE ROUTINES -------- */

void Hal_buttonIsr(void) {
    postEvent(BUTTON_HANDLER_ID);
    WAKEUP();
}

void Hal_rxIsr(void) {
    uint8_t b = inByte;
    Em_Message_startRx();
    EAP_RX_ACK_ClrVal(EAP_RX_ACK_DeviceData);
    EAP_RX_ACK_SetVal(EAP_RX_ACK_DeviceData);
    if (Em_Message_addByte(b)) {
        postEvent(DISPATCH_HANDLER_ID);
    }
    UART_ReceiveBlock(UART_DeviceData, &inByte, 1);
    WAKEUP();
}

void Hal_timerIsr(void) {
    postEvent(TICK_HANDLER_ID);
    WAKEUP();
}

void Hal_txAckIsr(void) {
    Hal_debugPulse(1);
    Hal_debugPulse(1);
    uint8_t b;
    if (Em_Message_getByte(&b)) {
        UART_SendBlock(UART_DeviceData, &b, 1);
    }
}

