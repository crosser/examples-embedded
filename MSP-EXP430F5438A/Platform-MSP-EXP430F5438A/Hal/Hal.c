/*
 * ============ Hardware Abstraction Layer for MSP-EXP430F5438A Experimenter Board ============
 */

#include "Hal.h"
#include "Em_Message.h"

#include <msp430.h>


/* -------- INTERNAL FEATURES -------- */

#define LED_CONFIG()                (P1DIR |= BIT1)
#define LED_ON()                    (P1OUT |= BIT1)
#define LED_OFF()                   (P1OUT &= ~BIT1)
#define LED_READ()                  (P1OUT & BIT1)
#define LED_TOGGLE()                (P1OUT ^= BIT1)

#define CONNECTED_LED_CONFIG()      (P1DIR |= BIT0)
#define CONNECTED_LED_ON()          (P1OUT |= BIT0)
#define CONNECTED_LED_OFF()         (P1OUT &= ~BIT0)

#define BUTTON_CONFIG()             (P2DIR &= ~BIT6, P2REN |= BIT6, P2OUT |= BIT6, P2IES |= BIT6);
#define BUTTON_ENABLE()             (P2IFG &= ~BIT6, P2IE |= BIT6)
#define BUTTON_PRESSED()            (!(P2IN & BIT6))
#define BUTTON_DEBOUNCE_MSECS       100

#define DEBUG1_CONFIG()             (P4DIR |= BIT0)
#define DEBUG1_ON()                 (P4OUT |= BIT0)
#define DEBUG1_OFF()                (P4OUT &= ~BIT0)

#define DEBUG2_CONFIG()             (P4DIR |= BIT1)
#define DEBUG2_ON()                 (P4OUT |= BIT1)
#define DEBUG2_OFF()                (P4OUT &= ~BIT1)

#define EAP_RX_BUF                  UCA2RXBUF
#define EAP_TX_BUF                  UCA2TXBUF

#define EAP_RX_VECTOR               USCI_A2_VECTOR
#define EAP_TX_VECTOR               USCI_A2_VECTOR
#define EAP_TX_ACK_VECTOR           PORT1_VECTOR

#define EAP_RX_ENABLE()             (P9SEL |= BIT5)
#define EAP_RX_DISABLE()            (P9SEL &= ~BIT5)
#define EAP_TX_ENABLE()             (P9SEL |= BIT4)
#define EAP_TX_DISABLE()            (P9SEL &= ~BIT4)

#define EAP_RX_ACK_CONFIG()         (P1DIR |= BIT3)
#define EAP_RX_ACK_SET()            (P1OUT |= BIT3)
#define EAP_RX_ACK_CLR()            (P1OUT &= ~BIT3)

#define EAP_TX_ACK_CONFIG()         (P1DIR &= ~BIT2, P1IES |= BIT2, P1IFG &= ~BIT2, P1IE |= BIT2)
#define EAP_TX_ACK_TST()            (P1IFG & BIT2)
#define EAP_TX_ACK_CLR()            (P1IFG &= ~BIT2)

#define EAP_RX_INT_CLR()            (UCA2IFG &= ~UCRXIFG)
#define EAP_RX_INT_ENABLE()         (UCA2IE |= UCRXIE)
#define EAP_TX_INT_CLR()            (UCA2IFG &= ~UCTXIFG)
#define EAP_TX_INT_DISABLE()        (UCA2IE &= ~UCTXIE)
#define EAP_TX_INT_ENABLE()         (UCA2IE |= UCTXIE)
#define EAP_TX_INT_TST()			(UCA2IFG & UCTXIFG)

#define MCLK_TICKS_PER_MS 			1000L
#define ACLK_TICKS_PER_SECOND       32768L
#define UART_WATCHDOG_PERIOD        (ACLK_TICKS_PER_SECOND * 250) / 1000

#define UART_WATCH_DISABLE()        (TA1CCTL1 = 0)                                              // Turn off CCR1 Interrupt
#define UART_WATCH_ENABLE()         (TA1CCR1 = TA1R + UART_WATCHDOG_PERIOD, TA1CCTL1 = CCIE)    // Set CCR1, and Enable CCR1 Interrupt

#ifdef __TI_COMPILER_VERSION__
#define UNUSED_VECTORS				DMA_VECTOR, RTC_VECTOR, SYSNMI_VECTOR, \
									TIMER0_A0_VECTOR, TIMER0_A1_VECTOR, TIMER0_B0_VECTOR, TIMER0_B1_VECTOR, \
									UNMI_VECTOR, USCI_A0_VECTOR, USCI_A1_VECTOR, USCI_A3_VECTOR, \
									USCI_B0_VECTOR, USCI_B1_VECTOR, USCI_B2_VECTOR, USCI_B3_VECTOR, \
									ADC12_VECTOR, WDT_VECTOR
#endif

#ifdef __GNUC__
#define DINT()                      (__disable_interrupt())
#define EINT()                      (__enable_interrupt())
#define INTERRUPT
#define SLEEP()                     (_BIS_SR(LPM3_bits + GIE))
#define WAKEUP()                    (_BIC_SR_IRQ(LPM3_bits))
#endif

#ifdef __TI_COMPILER_VERSION__
#define DINT()                      (_disable_interrupt())
#define EINT()                      (_enable_interrupt())
#define INTERRUPT interrupt
#define SLEEP()						(__bis_SR_register(LPM3_bits + GIE))
#define WAKEUP()					(__bic_SR_register_on_exit(LPM3_bits))
#endif

#define NUM_HANDLERS 3

#define BUTTON_HANDLER_ID      0
#define TICK_HANDLER_ID        1
#define DISPATCH_HANDLER_ID    2

static void buttonHandler(void);
static void postEvent(uint8_t handlerId);

static Hal_Handler appButtonHandler;
static volatile uint16_t handlerEvents = 0;
static uint16_t clockTick = 0;
static Hal_Handler handlerTab[NUM_HANDLERS];


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
    while (msecs--) {
	        __delay_cycles(MCLK_TICKS_PER_MS);
	    }
}

void Hal_disconnected(void) {
    CONNECTED_LED_OFF();
}

void Hal_init(void) {

    /* setup clocks */

    WDTCTL = WDTPW + WDTHOLD;
    P7SEL |= BIT0 | BIT1;                     // Select XT1
    UCSCTL6 &= ~(XT1OFF);                     // XT1 On
    UCSCTL6 |= XCAP_3;                        // Internal load cap
    // Loop until XT1,XT2 & DCO stabilizes
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                              // Clear XT2,XT1,DCO fault flags
      SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    } while (SFRIFG1&OFIFG);                  // Test oscillator fault flag
    UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                              // strength

    /* setup LEDs */

    LED_CONFIG();
    LED_OFF();
    CONNECTED_LED_CONFIG();
    CONNECTED_LED_OFF();

    /* setup debug pins */

    DEBUG1_CONFIG(); DEBUG1_OFF();
    DEBUG2_CONFIG(); DEBUG2_OFF();

    DEBUG1_ON(); DEBUG1_OFF();

    /* setup TimerA1 */
    TA1CTL = TASSEL_1 + MC_2;                 // ACLK, Continuous mode
    UART_WATCH_ENABLE();

    /* setup UART */

    UCA2CTL1 = UCSWRST;

    EAP_RX_ENABLE();
    EAP_TX_ENABLE();

    EAP_RX_ACK_CONFIG();
    EAP_RX_ACK_SET();

    EAP_TX_ACK_CONFIG();

    // suspend the MCM
    EAP_RX_ACK_CLR();

    UCA2CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA2CTL1 |= UCSSEL_2;                     // SMCLK
    UCA2BR0 = 9;                              // 1MHz 115200 (see User's Guide)
    UCA2BR1 = 0;                              // 1MHz 115200
    UCA2MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA2CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

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
    handlerTab[TICK_HANDLER_ID] = handler;
    clockTick = (ACLK_TICKS_PER_SECOND * msecs) / 1000;
    TA1CCR0 = TA1R + clockTick;                 // Set the CCR0 interrupt for msecs from now.
    TA1CCTL0 = CCIE;                            // Enable the CCR0 interrupt
}


/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
    #ifdef __GNUC__
        uint8_t key = READ_SR & 0x8;
        __disable_interrupt();
        return key;
    #endif
    #ifdef __TI_COMPILER_VERSION__
        uint8_t key = _get_interrupt_state();
        _disable_interrupt();
        return key;
    #endif
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
    #ifdef __GNUC__
        __asm__("bis %0,r2" : : "ir" ((uint16_t) key));
    #endif
    #ifdef __TI_COMPILER_VERSION__
        _set_interrupt_state(key);
    #endif
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

/* -------- INTERRUPT SERVICE ROUTINES -------- */

#ifdef __GNUC__
	__attribute__((interrupt(PORT2_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
	#pragma vector=PORT2_VECTOR
#endif
INTERRUPT void buttonIsr(void) {
    postEvent(BUTTON_HANDLER_ID);
    BUTTON_ENABLE();
    WAKEUP();
}

#ifdef __TI_COMPILER_VERSION__
    #pragma vector=UNUSED_VECTORS
INTERRUPT void ISR_trap(void)
{
  /* For debugging purposes, you can trap the CPU & code execution here with an
     infinite loop */
  while (1);
}
#endif

#ifdef __GNUC__
	__attribute__((interrupt(EAP_RX_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
	#pragma vector=EAP_RX_VECTOR
#endif
INTERRUPT void rxIsr(void) {
  uint8_t b;
  switch(UCA2IV)
  {
  case 2:                                   // Vector 2 - RXIFG
      b = EAP_RX_BUF;
      Em_Message_startRx();
      EAP_RX_ACK_CLR();
      EAP_RX_ACK_SET();
      if (Em_Message_addByte(b)) {
          postEvent(DISPATCH_HANDLER_ID);
      }
      WAKEUP();
    break;
  }
}

#ifdef __GNUC__
	__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
	#pragma vector=TIMER1_A0_VECTOR
#endif
INTERRUPT void timerIsr(void) {
    TA1CCR0 += clockTick;
    postEvent(TICK_HANDLER_ID);
    WAKEUP();
}

#ifdef __GNUC__
	__attribute__((interrupt(EAP_TX_ACK_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
	#pragma vector=EAP_TX_ACK_VECTOR
#endif
INTERRUPT void txAckIsr(void) {
    if (EAP_TX_ACK_TST()) {
        uint8_t b;
        if (Em_Message_getByte(&b)) {
            EAP_TX_BUF = b;
        }
        EAP_TX_ACK_CLR();
    }
    WAKEUP();
}

#ifdef __GNUC__
	__attribute__((interrupt(TIMER1_A1_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
	#pragma vector=TIMER1_A1_VECTOR
#endif
INTERRUPT void uartWatchdogIsr(void) {
	    switch (TA1IV) {
  case  2:                                  // CCR1
    UART_WATCH_DISABLE();
    Em_Message_restart();
    WAKEUP();
           break;
  }
}
