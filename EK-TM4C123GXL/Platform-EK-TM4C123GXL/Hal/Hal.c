#include "Hal.h"
#include "Em_Message.h"

#include "lm4f120h5qr_pin_map.h"
#include "inc/lm4f120h5qr.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

/* -------- INTERNAL FEATURES -------- */

#define EAP_RX_ACK_PORT			GPIO_PORTA_BASE
#define EAP_RX_ACK_PIN			GPIO_PIN_5
#define EAP_RX_ACK_SET()		GPIOPinWrite(EAP_RX_ACK_PORT, EAP_RX_ACK_PIN, EAP_RX_ACK_PIN)
#define EAP_RX_ACK_CLR()		GPIOPinWrite(EAP_RX_ACK_PORT, EAP_RX_ACK_PIN, ~EAP_RX_ACK_PIN)

#define EAP_TX_ACK_PORT			GPIO_PORTA_BASE
#define EAP_TX_ACK_PIN			GPIO_PIN_6

#define LED_PORT				GPIO_PORTF_BASE
#define LED_PIN					GPIO_PIN_2
#define LED_OFF()   			GPIOPinWrite(LED_PORT, LED_PIN, ~LED_PIN)
#define LED_ON()    			GPIOPinWrite(LED_PORT, LED_PIN, LED_PIN)
#define LED_READ()				GPIOPinRead(LED_PORT, LED_PIN) == LED_PIN
#define LED_TOGGLE()			GPIOPinWrite(LED_PORT, LED_PIN, LED_READ() ? ~LED_PIN : LED_PIN)

#define BLUE_LED_PIN			GPIO_PIN_3
#define BLUE_LED_OFF()   		GPIOPinWrite(LED_PORT, BLUE_LED_PIN, ~BLUE_LED_PIN)
#define BLUE_LED_ON()    		GPIOPinWrite(LED_PORT, BLUELED_PIN, BLUE_LED_PIN)

#define CONNECTED_LED_PIN		GPIO_PIN_1
#define CONNECTED_LED_ON()		GPIOPinWrite(LED_PORT, CONNECTED_LED_PIN, CONNECTED_LED_PIN)
#define CONNECTED_LED_OFF()		GPIOPinWrite(LED_PORT, CONNECTED_LED_PIN, ~CONNECTED_LED_PIN)
#define CONNECTED_LED_READ()	GPIOPinRead(LED_PORT, CONNECTED_LED_PIN) == CONNECTED_LED_PIN
#define CONNECTED_LED_TOGGLE()	GPIOPinWrite(LED_PORT, CONNECTED_LED_PIN, CONNECTED_LED_READ() ? ~CONNECTED_LED_PIN : CONNECTED_LED_PIN)

#define BUTTON_PORT             GPIO_PORTF_BASE
#define BUTTON_PIN              GPIO_PIN_4
#define BUTTON_ENABLE()         GPIOPinIntEnable(BUTTON_PORT, BUTTON_PIN)
#define BUTTON_PRESSED()        GPIOPinRead(BUTTON_PORT, BUTTON_PIN) == BUTTON_PIN

#define DEBUG1_PORT             GPIO_PORTA_BASE
#define DEBUG1_PIN              GPIO_PIN_2
#define DEBUG1_ON()             GPIOPinWrite(DEBUG1_PORT, DEBUG1_PIN, DEBUG1_PIN)
#define DEBUG1_OFF()            GPIOPinWrite(DEBUG1_PORT, DEBUG1_PIN, ~DEBUG1_PIN)
#define DEBUG2_PORT             GPIO_PORTA_BASE
#define DEBUG2_PIN              GPIO_PIN_3
#define DEBUG2_ON()             GPIOPinWrite(DEBUG2_PORT, DEBUG2_PIN, DEBUG2_PIN)
#define DEBUG2_OFF()            GPIOPinWrite(DEBUG2_PORT, DEBUG2_PIN, ~DEBUG2_PIN)

#define MSEC_CYCLES				16000

#define DINT()                  IntMasterDisable()
#define EINT()                  IntMasterEnable()
#define SLEEP()                 IntMasterEnable()
#define WAKEUP()

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
    Hal_delay(100);
    BUTTON_ENABLE();
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
    SysCtlDelay(msecs * MSEC_CYCLES / 3);
}

void Hal_disconnected(void) {
	CONNECTED_LED_OFF();
}

void Hal_init() {

	// Set the clocking to run directly from the crystal.
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

	GPIOPinTypeGPIOOutput(EAP_RX_ACK_PORT, EAP_RX_ACK_PIN);
	GPIOPinTypeGPIOInput(EAP_TX_ACK_PORT, EAP_TX_ACK_PIN);

	GPIOPinTypeGPIOOutput(LED_PORT, LED_PIN);
	GPIOPinTypeGPIOOutput(LED_PORT, CONNECTED_LED_PIN);
    GPIOPinTypeGPIOOutput(LED_PORT, BLUE_LED_PIN);

    GPIOPinTypeGPIOOutput(DEBUG1_PORT, DEBUG1_PIN);
    GPIOPinTypeGPIOOutput(DEBUG2_PORT, DEBUG2_PIN);

    GPIOPinTypeGPIOInput(BUTTON_PORT, BUTTON_PIN);
    GPIOPadConfigSet(BUTTON_PORT, BUTTON_PIN, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOIntTypeSet(BUTTON_PORT, BUTTON_PIN, GPIO_FALLING_EDGE);

    IntEnable(INT_GPIOA);
    IntEnable(INT_GPIOF);
    GPIOPinIntEnable(EAP_TX_ACK_PORT, EAP_TX_ACK_PIN);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |  UART_CONFIG_PAR_NONE));

    LED_OFF();
    BLUE_LED_OFF();
    CONNECTED_LED_OFF();
    DEBUG1_OFF();
    DEBUG2_OFF();

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
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, MSEC_CYCLES * msecs);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
    return IntMasterDisable() ? 0 : 1;
}

void Em_Hal_reset(void) {
    uint8_t key = Em_Hal_lock();
    EAP_RX_ACK_CLR();   // suspend the MCM
    Hal_delay(100);
    EAP_RX_ACK_SET();   // reset the MCM
    Hal_delay(500);
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RT);
    Em_Hal_unlock(key);
}

void Em_Hal_startSend(void) {
    UARTCharPutNonBlocking(UART1_BASE, Em_Message_startTx());
}

void Em_Hal_unlock(uint8_t key) {
    if (key) {
        IntMasterEnable();
    }
    else {
        IntMasterDisable();
    }
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

void Hal_buttonIsr(void) {
    GPIOPinIntClear(BUTTON_PORT, BUTTON_PIN);
    postEvent(BUTTON_HANDLER_ID);
}

void Hal_rxIsr(void) {
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ulStatus);
    Em_Message_startRx();
    EAP_RX_ACK_CLR();
    EAP_RX_ACK_SET();
    if (Em_Message_addByte(UARTCharGetNonBlocking(UART1_BASE))) {
        postEvent(DISPATCH_HANDLER_ID);
    }
}

void Hal_timerIsr(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    postEvent(TICK_HANDLER_ID);
}

void Hal_txAckIsr(void) {
    uint8_t b;
    GPIOPinIntClear(EAP_TX_ACK_PORT, EAP_TX_ACK_PIN);
    if (Em_Message_getByte(&b)) {
    	UARTCharPutNonBlocking(UART1_BASE, b);
    }
}

