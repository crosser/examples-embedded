#include "Hal.h"
#include "Em_Message.h"

#include <em_cmu.c>
#include <em_chip.h>
#include <em_gpio.c>
#include <em_int.c>
#include <em_timer.c>
#include <em_usart.c>
#include <em_system.c>
#include <system_efm32g.c>

/* -------- INTERNAL FEATURES -------- */

#define LED_PORT                gpioPortC
#define LED_PIN                 0
#define LED_OFF()               GPIO_PinOutClear(LED_PORT, LED_PIN)
#define LED_ON()                GPIO_PinOutSet(LED_PORT, LED_PIN)
#define LED_READ()              GPIO_PinOutGet(LED_PORT, LED_PIN)
#define LED_TOGGLE()            GPIO_PinOutToggle(LED_PORT, LED_PIN)

#define CONNECTED_LED_PORT      gpioPortC
#define CONNECTED_LED_PIN       3
#define CONNECTED_LED_OFF()     GPIO_PinOutClear(CONNECTED_LED_PORT, CONNECTED_LED_PIN)
#define CONNECTED_LED_ON()      GPIO_PinOutSet(CONNECTED_LED_PORT, CONNECTED_LED_PIN)
#define CONNECTED_LED_READ()    GPIO_PinOutGet(CONNECTED_LED_PORT, CONNECTED_LED_PIN)
#define CONNECTED_LED_TOGGLE()  GPIO_PinOutToggle(CONNECTED_LED_PORT, CONNECTED_LED_PIN)

#define DEBUG1_PORT             gpioPortD
#define DEBUG1_PIN              2
#define DEBUG1_ON()             GPIO_PinOutSet(DEBUG1_PORT, DEBUG1_PIN)
#define DEBUG1_OFF()            GPIO_PinOutClear(DEBUG1_PORT, DEBUG1_PIN)
#define DEBUG2_PORT             gpioPortD
#define DEBUG2_PIN              3
#define DEBUG2_ON()             GPIO_PinOutSet(DEBUG2_PORT, DEBUG2_PIN)
#define DEBUG2_OFF()            GPIO_PinOutClear(DEBUG2_PORT, DEBUG2_PIN)

#define DINT()                  __disable_irq()
#define EINT()                  __enable_irq()
#define SLEEP()                 __enable_irq()
#define WAKEUP()

#define EAP_RX_PORT             gpioPortD
#define EAP_RX_PIN              1

#define EAP_TX_PORT             gpioPortD
#define EAP_TX_PIN              0

#define EAP_RX_ACK_PORT         gpioPortC
#define EAP_RX_ACK_PIN          12
#define EAP_RX_ACK_CLR()        GPIO_PinOutClear(EAP_RX_ACK_PORT, EAP_RX_ACK_PIN)
#define EAP_RX_ACK_SET()        GPIO_PinOutSet(EAP_RX_ACK_PORT, EAP_RX_ACK_PIN)

#define EAP_TX_ACK_PORT         gpioPortC
#define EAP_TX_ACK_PIN          5

#define BUTTON_PORT             gpioPortB
#define BUTTON_PIN              10

#define NUM_HANDLERS 3

#define BUTTON_HANDLER_ID      0
#define TICK_HANDLER_ID        1
#define DISPATCH_HANDLER_ID    2

static void buttonHandler(void);
static void postEvent(uint8_t handlerId);

static Hal_Handler appButtonHandler;
static volatile uint16_t handlerEvents = 0;
static Hal_Handler handlerTab[NUM_HANDLERS];

/* -------- APP-HAL INTERFACE -------- */

void Hal_buttonEnable(Hal_Handler handler) {
    handlerTab[BUTTON_HANDLER_ID] = buttonHandler;
    appButtonHandler = handler;
    GPIO_PinModeSet(BUTTON_PORT, BUTTON_PIN, gpioModeInput, 1);
    GPIO_IntConfig(BUTTON_PORT, BUTTON_PIN, false, true, false);  // falling edge
    GPIO_IntClear(1 << BUTTON_PIN);
    GPIO_IntEnable(1 << BUTTON_PIN);
    Hal_delay(100);
    NVIC_EnableIRQ(GPIO_EVEN_IRQn);  // for BUTTON_PIN
}

void Hal_connected(void) {
	CONNECTED_LED_ON();
}

void Hal_debugOn(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_ON();
        break;
    case 2:
        DEBUG2_ON();
    }
}

void Hal_debugOff(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_OFF();
        break;
    case 2:
        DEBUG2_OFF();
    }
}

void Hal_debugPulse(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_ON();
        DEBUG1_OFF();
        break;
    case 2:
        DEBUG2_ON();
        DEBUG2_OFF();
    }
}

void Hal_delay(uint16_t msecs) {
    while (msecs-- > 0) {
        for (uint16_t i = 0; i < 500; i++) {    
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
            __asm("nop");
        }
    }
}

void Hal_disconnected(void) {
	CONNECTED_LED_OFF();
}

void Hal_init() {

    CHIP_Init();
    SystemCoreClockUpdate();

    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_USART1, true);

    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(CONNECTED_LED_PORT, CONNECTED_LED_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(DEBUG1_PORT, DEBUG1_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(DEBUG2_PORT, DEBUG2_PIN, gpioModePushPull, 0);

    // UART

    GPIO_PinModeSet(EAP_RX_PORT, EAP_RX_PIN, gpioModeInput, 0);
    GPIO_PinModeSet(EAP_RX_ACK_PORT, EAP_RX_ACK_PIN, gpioModePushPull, 1);
    GPIO_PinModeSet(EAP_TX_PORT, EAP_TX_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(EAP_TX_ACK_PORT, EAP_TX_ACK_PIN, gpioModeInput, 0);

    GPIO_IntConfig(EAP_TX_ACK_PORT, EAP_TX_ACK_PIN, true, false, false);  // rising edge
    GPIO_IntClear(1 << EAP_TX_ACK_PIN);
    GPIO_IntEnable(1 << EAP_TX_ACK_PIN);

    USART_TypeDef *usart = USART1;
    USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
    USART_InitAsync(usart, &init);
    usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC1;
    USART_IntClear(usart, _UART_IF_MASK);
    USART_IntEnable(usart, UART_IF_RXDATAV);

    NVIC_EnableIRQ(USART1_RX_IRQn);
    NVIC_EnableIRQ(GPIO_ODD_IRQn);  // for EAP_TX_ACK

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
	LED_ON();
}

void Hal_ledOff(void) {
	LED_OFF();
}

bool Hal_ledRead(void) {
	return LED_READ();
}

void Hal_ledToggle(void) {
	LED_TOGGLE();
}

void Hal_tickStart(uint16_t msecs, void (*handler)(void)) {
    handlerTab[TICK_HANDLER_ID] = handler;
    TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;
    init.prescale = timerPrescale1024;
    CMU_ClockEnable(cmuClock_TIMER1, true);
    TIMER_Init(TIMER1, &init);
    TIMER_TopSet(TIMER1, msecs * 16);
    TIMER_CounterSet(TIMER1, 0);
    TIMER_IntClear(TIMER1, 0x1);
    TIMER_IntEnable(TIMER1, 0x1);
    TIMER_Enable(TIMER1, true);
    NVIC_EnableIRQ(TIMER1_IRQn);
}

/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
    INT_Disable();
    return 0;
}

void Em_Hal_reset(void) {
    Hal_debugPulse(1);
    uint8_t key = Em_Hal_lock();
    EAP_RX_ACK_CLR();   // suspend the MCM
    Hal_delay(100);
    EAP_RX_ACK_SET();   // reset the MCM
    Hal_delay(500);
    Em_Hal_unlock(key);
}

void Em_Hal_startSend(void) {
    USART_Tx(USART1, Em_Message_startTx());
}

void Em_Hal_unlock(uint8_t key) {
    INT_Enable();
}

void Em_Hal_watchOn(void) {
}

void Em_Hal_watchOff(void) {
}

/* -------- INTERNAL FUNCTIONS -------- */

static void buttonHandler(void) {
    if (appButtonHandler) {
        appButtonHandler();
    }
}

static void postEvent(uint8_t handlerId) {
    uint8_t key = Em_Hal_lock();
    handlerEvents |= 1 << handlerId;
    Em_Hal_unlock(key);
}

/* -------- INTERRUPT SERVICE ROUTINES -------- */

// Hal_buttonIsr
void GPIO_EVEN_IRQHandler(void) {
    GPIO_IntClear(1 << BUTTON_PIN);
    postEvent(BUTTON_HANDLER_ID);
}

// Hal_rxIsr
void USART1_RX_IRQHandler(void) {
    USART_IntClear(USART1, usartEnableRx);
    Em_Message_startRx();
    EAP_RX_ACK_CLR();
    EAP_RX_ACK_SET();
    if (Em_Message_addByte(USART_Rx(USART1))) {
        Hal_debugPulse(2);
        postEvent(DISPATCH_HANDLER_ID);
    }
}

// Hal_timerIsr
void TIMER1_IRQHandler(void) {
    Hal_debugPulse(2);
    TIMER_IntClear(TIMER1, 0x1);
    postEvent(TICK_HANDLER_ID);
}

// Hal_txAckIsr
void GPIO_ODD_IRQHandler(void) {
    uint8_t b;
    GPIO_IntClear(1 << EAP_TX_ACK_PIN);
    if (Em_Message_getByte(&b)) {
        USART_Tx(USART1, b);
    }
}
