/*
 * ============ Platform Configuration for XMC1100 Boot Kit ============
 *
 * This HAL was built using a DAVE CE project, and the S/W Apps provided.  Note that if the
 * apps (e.g. IO004) are assigned in a different order -- e.g. LED is not IO004/0, then the
 * #defines below will need to have the handle numbers changed.
 *
 * Also note that the SLEEP / WAKEUP functions are not implemented.  And the UART Watchdog is not
 * implemented.
 *
 * The following DAVE CE settings were used -- note that the order matters.
 *
 * 	MCLK/PCLK:		CLK002/0	Desired Frequency 2000 KHz, PCLK=MCLK, 32.768 Standby for RTC
 * 	Timer:			SYSTM001/0	SysTick Interval 100 mSec, 32 SWTimers, Priority 1
 * 	LED:   			IO004/0		Output Enabled, Default level High, Tristate, Push Pull
 * 	CONNECTED_LED:	IO004/1		Output Enabled, Default level High, Tristate, Push Pull
 * 	DEBUG1:			IO004/2		Output Enabled, Default level Low, Tristate, Push Pull
 * 	DEBUG2:			IO004/3		Output Enabled, Default level Low, Tristate, Push Pull
 * 	EAP_RX_ACK:		IO004/4		Output Enabled, Default level High, Tristate, Push Pull
 * 	EAP_TX_ACK:		IO002/0		Output Disabled, Tristate, Standard Hysteresis
 * 					ERU001/0	Event Request B, Falling Edge, Rising Edge, Not Sticky
 * 					ERU002/0	Pattern Edge Trigger disabled, No Output Gating
 * 					NVIC002/1	Priority 3, Not Enabled at initialization, User Handler: txAckIsr
 * 	EAP_RX + _TX:	UART001/0	Full Duplex, No Parity, One Stop Bit, 8 Data bits, RxFifo 16, TxFifo 16
 * 								Trigger Limit 1, Desired Baud Rate 115200, No Oversampling
 * 								No Interrupt configuration, Rx Pin Tristate
 * 					NVIC002/0	Priority 3, Enable at initialization, User Handler: rxIsr
 *
 * The following Manual Pin Assignments were used in this HAL:
 *
 *   - XMC1100 P0.0  -- output -- DEBUG1  used optionally for debugging
 *   - XMC1100 P0.1  -- output -- DEBUG2  used optionally for debugging
 *   - XMC1100 P0.2  -- output -- EAP_RX_ACK   connected to A2541 P0_4/CTS# through BoosterPack jumper JP3-1/JP3-2
 *   - XMC1100 P0.5  -- output -- LED
 *   - XMC1100 P0.6  -- output -- CONNECTED_LED
 *   - XMC1100 P2.0  -- output -- EAP_TX UART connected to A2541 module P0_3/TXD (115200,8N1N)
 *   - XMC1100 P2.1  -- input  -- EAP_RX UART connected to A2541 module P0_2/RXD (115200,8N1N)
 *   - XMC1100 P2.2  -- input  -- EAP_TX_ACK   connected to A2541 P0_5/RTS# through BoosterPack jumper JP4-1/JP4-2
 *   - XMC1100       -- input  -- BUTTON not implemented
 *
 * The following DAVE CE Signal Connections were used:
 * 
 * 	UART001/0 Standard Receive Interrupt	->	NVIC002/0 Interrupt Node
 * 	IO002/0 Pad Signal 						->	ERU001/0 Signal B Input
 * 	ERU001/0 Trigger Pulse Output			-> 	ERU002/0 Trigger Input
 * 	ERU002/0 Gated Trigger Output			->	NVIC002/1 Interrupt Node
 *
 */

#include <DAVE3.h>
#include "Hal.h"
#include "Em_Message.h"

//#include <XMC1100.h>						// SFR declarations of the selected device
//#include "gpio_XMC1100_tssop38.h"			// Contains definitions if not using Dave CE code generator


/* -------- INTERNAL FEATURES -------- */

#define BUTTON_CONFIG()
#define BUTTON_ENABLE()
#define BUTTON_PRESSED()            (0)

#define LED                         IO004_Handle0
#define CONNECTED_LED               IO004_Handle1
#define DEBUG1                      IO004_Handle2
#define DEBUG2                      IO004_Handle3
#define EAP_RX_ACK                  IO004_Handle4
#define EAP_RX_INT                  NVIC002_Handle0
#define EAP_TX_ACK_INT              NVIC002_Handle1
#define EAP_RX_BUF                  UART001_0_USIC_CH->RBUF
#define EAP_TX_BUF                  UART001_0_USIC_CH->IN[0]

#define LED_ON()                    (IO004_ResetPin(LED))
#define LED_OFF()                   (IO004_SetPin(LED))
#define LED_READ()                  (IO004_ReadPin(LED))
#define LED_TOGGLE()                (IO004_TogglePin(LED))

#define CONNECTED_LED_ON()          (IO004_ResetPin(CONNECTED_LED))
#define CONNECTED_LED_OFF()         (IO004_SetPin(CONNECTED_LED))

#define DEBUG1_ON()                 (IO004_SetPin(DEBUG1))
#define DEBUG1_OFF()                (IO004_ResetPin(DEBUG1))

#define DEBUG2_ON()                 (IO004_SetPin(DEBUG2))
#define DEBUG2_OFF()                (IO004_ResetPin(DEBUG2))

#define EAP_RX_ACK_SET()            (IO004_SetPin(EAP_RX_ACK))
#define EAP_RX_ACK_CLR()            (IO004_ResetPin(EAP_RX_ACK))

#define EAP_TX_ACK_CONFIG()         (NVIC002_EnableIRQ(&EAP_TX_ACK_INT))
#define EAP_TX_ACK_CLR()            (NVIC_ClearPendingIRQ ((IRQn_Type)EAP_TX_ACK_INT.NodeID))

#define EAP_RX_INT_CLR()            (NVIC_ClearPendingIRQ((IRQn_Type)EAP_RX_INT.NodeID))
#define EAP_RX_INT_ENABLE()         (NVIC002_EnableIRQ(&EAP_RX_INT))
#define EAP_TX_INT_CLR()            // EAP_TX_INT not used

#define MCLK_TICKS_PER_MS           8000L
#define ACLK_TICKS_PER_SECOND       8000000L
#define UART_WATCHDOG_PERIOD        (ACLK_TICKS_PER_SECOND * 250) / 1000

#define UART_WATCH_DISABLE()
#define UART_WATCH_ENABLE()

#define DINT()                      (__disable_irq())
#define EINT()                      (__enable_irq())
#define SLEEP()                     (__enable_irq())
#define WAKEUP()

#define NUM_HANDLERS 3

#define BUTTON_HANDLER_ID      0
#define TICK_HANDLER_ID        1
#define DISPATCH_HANDLER_ID    2

extern uint32_t SystemCoreClock;
extern void SystemCoreClockUpdate();

static void buttonHandler(void);
static void postEvent(uint8_t handlerId);
void myTick_Handler(void);
//
static Hal_Handler appButtonHandler;
static volatile uint16_t handlerEvents = 0;
//static uint16_t clockTick = 0;
static Hal_Handler handlerTab[NUM_HANDLERS];
static handle_t TimerId = 0;

/* -------- APP-HAL INTERFACE -------- */

void Hal_buttonEnable(Hal_Handler handler) {
    handlerTab[BUTTON_HANDLER_ID] = buttonHandler;
    appButtonHandler = handler;
    BUTTON_CONFIG();
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
	volatile uint32_t x;
	while (msecs--) {
		for (x=0; x<155; x++) ;
	}
}

void Hal_disconnected(void) {
    CONNECTED_LED_OFF();
}

void Hal_init(void) {

	/* Setup all the Dave resources */
	DAVE_Init();

    /* setup debug pins */

    DEBUG1_OFF();					// Pulse the Debug1 line for yucks.
    DEBUG1_ON();
    DEBUG1_OFF();

    DEBUG2_OFF();

	/* setup LEDs */
    LED_OFF();
    CONNECTED_LED_OFF();

    /* setup UART */

    EAP_RX_ACK_SET();
    EAP_TX_ACK_CONFIG();
    EAP_RX_ACK_CLR();				// Suspend the MCM

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

void Hal_tickStart(uint16_t msecs, Hal_Handler handler) {
	status_t Status;
    handlerTab[TICK_HANDLER_ID] = handler;
    TimerId = SYSTM001_CreateTimer(msecs, SYSTM001_PERIODIC, (SYSTM001_TimerCallBackPtr)myTick_Handler, NULL);
    if(TimerId != 0)
    {
    //Timer is created successfully
    	Status = SYSTM001_StartTimer(TimerId);
    	if(Status == DAVEApp_SUCCESS)
    	{
    	   	         //Timer started
    	}
    }
}


/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
	DINT();
	return 0;
}

void Em_Hal_reset(void) {
    uint8_t key = Em_Hal_lock();
    EAP_RX_ACK_CLR();    // suspend the MCM
    Hal_delay(100);
    EAP_RX_ACK_SET();    // reset the MCM
    Hal_delay(500);
    EAP_RX_INT_CLR();
    EAP_TX_INT_CLR();
    EAP_TX_ACK_CLR();
    EAP_RX_INT_ENABLE();
    Em_Hal_unlock(key);
}

void Em_Hal_startSend() {
    EAP_TX_BUF = Em_Message_startTx();
}

void Em_Hal_unlock(uint8_t key) {
	EINT();
}

void Em_Hal_watchOff(void) {
    UART_WATCH_DISABLE();
}

void Em_Hal_watchOn(void) {
    UART_WATCH_ENABLE();
}


/* -------- INTERNAL FUNCTIONS -------- */

static void buttonHandler(void) {
    Hal_delay(100);
    if (BUTTON_PRESSED() && appButtonHandler) {
        appButtonHandler();
    }
}

static void postEvent(uint8_t handlerId) {
    uint8_t key = Em_Hal_lock();
    handlerEvents |= 1 << handlerId;
    Em_Hal_unlock(key);
}

///* -------- INTERRUPT SERVICE ROUTINES -------- */

void rxIsr(void) {
    volatile uint8_t b = EAP_RX_BUF;
    Em_Message_startRx();
    EAP_RX_ACK_CLR();
    EAP_RX_ACK_SET();
    if (Em_Message_addByte(b)) {
        postEvent(DISPATCH_HANDLER_ID);
    }
    WAKEUP();
}

void myTick_Handler(void) {
    postEvent(TICK_HANDLER_ID);
    WAKEUP();
}

void txAckIsr(void) {
    uint8_t b;
    if (Em_Message_getByte(&b)) {
        EAP_TX_BUF = b;
    }
    EAP_TX_ACK_CLR();
    WAKEUP();
}
