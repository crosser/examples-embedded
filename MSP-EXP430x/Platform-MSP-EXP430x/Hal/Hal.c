/*
 * ============ Hardware Abstraction Layer for MSP-EXP430xx Platforms ============
 */
 
#include "Hal.h"
#include "Em_Message.h"

#include <msp430.h>

/* -------- INTERNAL FEATURES -------- */

///////////////////////////////////////////////////////////////////////////////////////////////
#if defined MSP_EXP430G2

#define LED_CONFIG()                (P1DIR |= BIT6)
#define LED_ON()                    (P1OUT |= BIT6)
#define LED_OFF()                   (P1OUT &= ~BIT6)
#define LED_READ()                  (P1OUT & BIT6)
#define LED_TOGGLE()                (P1OUT ^= BIT6)

#define CONNECTED_LED_CONFIG()      (P1DIR |= BIT0)
#define CONNECTED_LED_ON()          (P1OUT |= BIT0)
#define CONNECTED_LED_OFF()         (P1OUT &= ~BIT0)

#define BUTTON_CONFIG()             (P1DIR &= ~BIT3, P1REN |= BIT3, P1OUT |= BIT3, P1IES |= BIT3);
#define BUTTON_ENABLE()             (P1IFG &= ~BIT3, P1IE |= BIT3)
#define BUTTON_PRESSED()            (!(P1IN & BIT3))
#define BUTTON_DEBOUNCE_MSECS       100
#define BUTTON_VECTOR               PORT1_VECTOR

#define DEBUG1_CONFIG()             (P2DIR |= BIT3)
#define DEBUG1_ON()                 (P2OUT |= BIT3)
#define DEBUG1_OFF()                (P2OUT &= ~BIT3)

#define DEBUG2_CONFIG()             (P2DIR |= BIT4)
#define DEBUG2_ON()                 (P2OUT |= BIT4)
#define DEBUG2_OFF()                (P2OUT &= ~BIT4)

#define EAP_RX_BUF                  UCA0RXBUF
#define EAP_TX_BUF                  UCA0TXBUF
#define EAP_CTL                     UCA0CTL1
#define EAP_IV                      2

#define EAP_RX_VECTOR               USCIAB0RX_VECTOR
#define EAP_TX_VECTOR               USCIAB0TX_VECTOR
#define EAP_TX_ACK_VECTOR           PORT2_VECTOR

#define EAP_RX_ENABLE()             (P1SEL |= BIT1, P1SEL2 |= BIT1)
#define EAP_RX_DISABLE()            (P1SEL &= ~BIT1, P1SEL2 &= ~BIT1)
#define EAP_TX_ENABLE()             (P1SEL |= BIT2, P1SEL2 |= BIT2)
#define EAP_TX_DISABLE()            (P1SEL &= ~BIT2, P1SEL2 &= ~BIT2)

#define EAP_RX_ACK_CONFIG()         (P2DIR |= BIT0)
#define EAP_RX_ACK_SET()            (P2OUT |= BIT0)
#define EAP_RX_ACK_CLR()            (P2OUT &= ~BIT0)

#define EAP_TX_ACK_CONFIG()         (P2DIR &= ~BIT1, P2IES |= BIT1, P2IFG &= ~BIT1, P2IE |= BIT1)
#define EAP_TX_ACK_TST()            (P2IFG & BIT1)
#define EAP_TX_ACK_CLR()            (P2IFG &= ~BIT1)

#define EAP_RX_INT_CLR()            (IFG2 &= ~UCA0RXIFG)
#define EAP_RX_INT_ENABLE()         (IE2 |= UCA0RXIE)
#define EAP_TX_INT_CLR()            (IFG2 &= ~UCA0TXIFG)
#define EAP_TX_INT_DISABLE()        (IE2 &= ~UCA0TXIE)
#define EAP_TX_INT_ENABLE()         (IE2 |= UCA0TXIE)

#define ACLK_TICKS_PER_SECOND       12000L
#define SLEEP_LEVEL                 LPM3_bits

///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430F5529LP

#define LED_CONFIG()                (P4DIR |= BIT7)
#define LED_ON()                    (P4OUT |= BIT7)
#define LED_OFF()                   (P4OUT &= ~BIT7)
#define LED_READ()                  (P4OUT & BIT7)
#define LED_TOGGLE()                (P4OUT ^= BIT7)

#define CONNECTED_LED_CONFIG()      (P1DIR |= BIT0)
#define CONNECTED_LED_ON()          (P1OUT |= BIT0)
#define CONNECTED_LED_OFF()         (P1OUT &= ~BIT0)

#define BUTTON_CONFIG()             (P1DIR &= ~BIT1, P1REN |= BIT1, P1OUT |= BIT1, P1IES |= BIT1);
#define BUTTON_ENABLE()             (P1IFG &= ~BIT1, P1IE |= BIT1)
#define BUTTON_PRESSED()            (!(P1IN & BIT1))
#define BUTTON_DEBOUNCE_MSECS       100
#define BUTTON_VECTOR               PORT1_VECTOR

#define DEBUG1_CONFIG()             (P4DIR |= BIT2)
#define DEBUG1_ON()                 (P4OUT |= BIT2)
#define DEBUG1_OFF()                (P4OUT &= ~BIT2)

#define DEBUG2_CONFIG()             (P4DIR |= BIT1)
#define DEBUG2_ON()                 (P4OUT |= BIT1)
#define DEBUG2_OFF()                (P4OUT &= ~BIT1)

#define EAP_RX_BUF                  UCA0RXBUF
#define EAP_TX_BUF                  UCA0TXBUF
#define EAP_CTL                     UCA0CTL1
#define EAP_IV                      UCA0IV

#define EAP_RX_VECTOR               USCI_A0_VECTOR
#define EAP_TX_VECTOR               USCI_A0_VECTOR
#define EAP_TX_ACK_VECTOR           PORT2_VECTOR

#define EAP_RX_ENABLE()             (P3SEL |= BIT4)
#define EAP_RX_DISABLE()            (P3SEL &= ~BIT4)
#define EAP_TX_ENABLE()             (P3SEL |= BIT3)
#define EAP_TX_DISABLE()            (P3SEL &= ~BIT3)

#define EAP_RX_ACK_CONFIG()         (P2DIR |= BIT6)
#define EAP_RX_ACK_SET()            (P2OUT |= BIT6)
#define EAP_RX_ACK_CLR()            (P2OUT &= ~BIT6)

#define EAP_TX_ACK_CONFIG()         (P2DIR &= ~BIT3, P2IES |= BIT3, P2IFG &= ~BIT3, P2IE |= BIT3)
#define EAP_TX_ACK_TST()            (P2IFG & BIT3)
#define EAP_TX_ACK_CLR()            (P2IFG &= ~BIT3)

#define EAP_RX_INT_CLR()            (UCA0IFG &= ~UCRXIFG)
#define EAP_RX_INT_ENABLE()         (UCA0IE |= UCRXIE)
#define EAP_TX_INT_CLR()            (UCA0IFG &= ~UCTXIFG)
#define EAP_TX_INT_DISABLE()        (UCA0IE &= ~UCTXIE)
#define EAP_TX_INT_ENABLE()         (UCA0IE |= UCTXIE)

#define ACLK_TICKS_PER_SECOND       32768L
#define SLEEP_LEVEL                 LPM0_bits

///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430F5438A

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
#define BUTTON_VECTOR               PORT2_VECTOR

#define DEBUG1_CONFIG()             (P4DIR |= BIT0)
#define DEBUG1_ON()                 (P4OUT |= BIT0)
#define DEBUG1_OFF()                (P4OUT &= ~BIT0)

#define DEBUG2_CONFIG()             (P4DIR |= BIT1)
#define DEBUG2_ON()                 (P4OUT |= BIT1)
#define DEBUG2_OFF()                (P4OUT &= ~BIT1)

#define EAP_RX_BUF                  UCA2RXBUF
#define EAP_TX_BUF                  UCA2TXBUF
#define EAP_CTL                     UCA2CTL1
#define EAP_IV                      UCA2IV

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
#define EAP_TX_INT_TST()            (UCA2IFG & UCTXIFG)

#define ACLK_TICKS_PER_SECOND       32768L
#define SLEEP_LEVEL                 LPM3_bits

///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430FR5739

#define LED_CONFIG()                (P3DIR |= BIT7)
#define LED_ON()                    (P3OUT |= BIT7)
#define LED_OFF()                   (P3OUT &= ~BIT7)
#define LED_READ()                  (P3OUT & BIT7)
#define LED_TOGGLE()                (P3OUT ^= BIT7)

#define CONNECTED_LED_CONFIG()      (PJDIR |= BIT0)
#define CONNECTED_LED_ON()          (PJOUT |= BIT0)
#define CONNECTED_LED_OFF()         (PJOUT &= ~BIT0)

#define BUTTON_CONFIG()             (P4DIR &= ~BIT0, P4REN |= BIT0, P4OUT |= BIT0, P4IES |= BIT0);
#define BUTTON_ENABLE()             (P4IFG &= ~BIT0, P4IE |= BIT0)
#define BUTTON_PRESSED()            (!(P4IN & BIT0))
#define BUTTON_DEBOUNCE_MSECS       100
#define BUTTON_VECTOR               PORT4_VECTOR

#define DEBUG1_CONFIG()             (P1DIR |= BIT1)
#define DEBUG1_ON()                 (P1OUT |= BIT1) 
#define DEBUG1_OFF()                (P1OUT &= ~BIT1)

#define DEBUG2_CONFIG()             (P1DIR |= BIT2)
#define DEBUG2_ON()                 (P1OUT |= BIT2) 
#define DEBUG2_OFF()                (P1OUT &= ~BIT2)

#define EAP_RX_BUF                  UCA1RXBUF
#define EAP_TX_BUF                  UCA1TXBUF
#define EAP_CTL                     UCA1CTLW0
#define EAP_IV                      UCA1IV

#define EAP_RX_VECTOR               USCI_A1_VECTOR
#define EAP_TX_VECTOR               USCI_A1_VECTOR
#define EAP_TX_ACK_VECTOR           PORT1_VECTOR

#define EAP_RX_ENABLE()             (P2SEL1 |= BIT6, P2SEL0 &= ~BIT6)
#define EAP_RX_DISABLE()            (P2SEL1 &= ~BIT6, P2SEL0 &= ~BIT6)
#define EAP_TX_ENABLE()             (P2SEL1 |= BIT5, P2SEL0 &= ~BIT5)
#define EAP_TX_DISABLE()            (P2SEL1 &= ~BIT5, P2SEL0 &= ~BIT5)

#define EAP_RX_ACK_CONFIG()         (P1DIR |= BIT5)
#define EAP_RX_ACK_SET()            (P1OUT |= BIT5)
#define EAP_RX_ACK_CLR()            (P1OUT &= ~BIT5)

#define EAP_TX_ACK_CONFIG()         (P1DIR &= ~BIT4, P1IES |= BIT4, P1IFG &= ~BIT4, P1IE |= BIT4)
#define EAP_TX_ACK_TST()            (P1IFG & BIT4)
#define EAP_TX_ACK_CLR()            (P1IFG &= ~BIT4)

#define EAP_RX_INT_CLR()            (UCA1IFG &= ~UCRXIFG)
#define EAP_RX_INT_ENABLE()         (UCA1IE |= UCRXIE)
#define EAP_TX_INT_CLR()            (UCA1IFG &= ~UCTXIFG)
#define EAP_TX_INT_DISABLE()        (UCA1IE &= ~UCTXIE)
#define EAP_TX_INT_ENABLE()         (UCA1IE |= UCTXIE)

#define ACLK_TICKS_PER_SECOND       12000L
#define SLEEP_LEVEL                 LPM0_bits

///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430FR5969

#define LED_CONFIG()                (P1DIR |= BIT0)
#define LED_ON()                    (P1OUT |= BIT0)
#define LED_OFF()                   (P1OUT &= ~BIT0)
#define LED_READ()                  (P1OUT & BIT0)
#define LED_TOGGLE()                (P1OUT ^= BIT0)

#define CONNECTED_LED_CONFIG()      (P4DIR |= BIT6)
#define CONNECTED_LED_ON()          (P4OUT |= BIT6)
#define CONNECTED_LED_OFF()         (P4OUT &= ~BIT6)

#define BUTTON_CONFIG()             (P1DIR &= ~BIT1, P1REN |= BIT1, P1OUT |= BIT1, P1IES |= BIT1);
#define BUTTON_ENABLE()             (P1IFG &= ~BIT1, P1IE |= BIT1)
#define BUTTON_PRESSED()            (!(P1IN & BIT1))
#define BUTTON_DEBOUNCE_MSECS       100
#define BUTTON_VECTOR               PORT1_VECTOR

#define DEBUG1_CONFIG()             (P1DIR |= BIT3)
#define DEBUG1_ON()                 (P1OUT |= BIT3)
#define DEBUG1_OFF()                (P1OUT &= ~BIT3)

#define DEBUG2_CONFIG()             (P1DIR |= BIT4)
#define DEBUG2_ON()                 (P1OUT |= BIT4)
#define DEBUG2_OFF()                (P1OUT &= ~BIT4)

#define EAP_RX_BUF                  UCA1RXBUF
#define EAP_TX_BUF                  UCA1TXBUF
#define EAP_CTL                     UCA1CTLW0
#define EAP_IV                      UCA1IV

#define EAP_RX_VECTOR               USCI_A1_VECTOR
#define EAP_TX_VECTOR               USCI_A1_VECTOR
#define EAP_TX_ACK_VECTOR           PORT3_VECTOR

#define EAP_RX_ENABLE()             (P2SEL1 |= BIT6, P2SEL0 &= ~BIT6)
#define EAP_RX_DISABLE()            (P2SEL1 &= ~BIT6, P2SEL0 &= ~BIT6)
#define EAP_TX_ENABLE()             (P2SEL1 |= BIT5, P2SEL0 &= ~BIT5)
#define EAP_TX_DISABLE()            (P2SEL1 &= ~BIT5, P2SEL0 &= ~BIT5)

#define EAP_RX_ACK_CONFIG()         (P3DIR |= BIT4)
#define EAP_RX_ACK_SET()            (P3OUT |= BIT4)
#define EAP_RX_ACK_CLR()            (P3OUT &= ~BIT4)

#define EAP_TX_ACK_CONFIG()         (P3DIR &= ~BIT5, P3IES |= BIT5, P3IFG &= ~BIT5, P3IE |= BIT5)
#define EAP_TX_ACK_TST()            (P3IFG & BIT5)
#define EAP_TX_ACK_CLR()            (P3IFG &= ~BIT5)

#define EAP_RX_INT_CLR()            (UCA1IFG &= ~UCRXIFG)
#define EAP_RX_INT_ENABLE()         (UCA1IE |= UCRXIE)
#define EAP_TX_INT_CLR()            (UCA1IFG &= ~UCTXIFG)
#define EAP_TX_INT_DISABLE()        (UCA1IE &= ~UCTXIE)
#define EAP_TX_INT_ENABLE()         (UCA1IE |= UCTXIE)

#define ACLK_TICKS_PER_SECOND       32768L
#define SLEEP_LEVEL                 LPM0_bits

#endif
///////////////////////////////////////////////////////////////////////////////////////////////

#define MCLK_TICKS_PER_MS           1000L
#define UART_WATCHDOG_PERIOD        (ACLK_TICKS_PER_SECOND * 250) / 1000
 
#define UART_WATCH_DISABLE()        (TA1CCTL1 = 0)                                              // Turn off CCR1 Interrupt
#define UART_WATCH_ENABLE()         (TA1CCR1 = TA1R + UART_WATCHDOG_PERIOD, TA1CCTL1 = CCIE)    // Set CCR1, and Enable CCR1 Interrupt

#ifdef __GNUC__
#define DINT()                      (__disable_interrupt())
#define EINT()                      (__enable_interrupt())
#define INTERRUPT
#define SLEEP()                     (_BIS_SR(SLEEP_LEVEL + GIE))
#define WAKEUP()                    (_BIC_SR_IRQ(SLEEP_LEVEL))
#endif

#ifdef __TI_COMPILER_VERSION__
#define DINT()                      (_disable_interrupt())
#define EINT()                      (_enable_interrupt())
#define INTERRUPT interrupt
#define SLEEP()                     (__bis_SR_register(SLEEP_LEVEL + GIE))
#define WAKEUP()                    (__bic_SR_register_on_exit(SLEEP_LEVEL))
#endif

#define NUM_HANDLERS 3

#define BUTTON_HANDLER_ID      0
#define TICK_HANDLER_ID        1
#define DISPATCH_HANDLER_ID    2

static void buttonHandler(void);
static void oscInit(void);
static void postEvent(uint8_t handlerId);
static void uartInit(void);

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
        break;
    }
}

void Hal_debugOff(uint8_t line) {
    switch (line) {
    case 1:
        DEBUG1_OFF();
        break;
    case 2:
        DEBUG2_OFF();
        break;
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
        break;
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
    oscInit();

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
    TA1CTL = TASSEL_1 + MC_2;           // ACLK, Continuous mode
    UART_WATCH_DISABLE();

    /* setup UART */
    uartInit();

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

static void oscInit() {
    WDTCTL = WDTPW + WDTHOLD;
///////////////////////////////////////////////////////////////////////////////////////////////
#if defined MSP_EXP430G2
    BCSCTL2 = SELM_0 + DIVM_0 + DIVS_0;
    if (CALBC1_1MHZ != 0xFF) {
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1MHz */
        DCOCTL = CALDCO_1MHZ;
    }
    BCSCTL1 |= XT2OFF + DIVA_0;
    BCSCTL3 = XT2S_0 + LFXT1S_2 + XCAP_1;
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430F5529LP
    P5SEL |= BIT4 + BIT5;                     // Select XT1
    UCSCTL6 &= ~(XT1OFF);                     // XT1 On
    UCSCTL6 |= XCAP_3;                        // Internal load cap
    UCSCTL3 = 0;                              // FLL Reference Clock = XT1
    // Loop until XT1,XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                              // Clear XT2,XT1,DCO fault flags
      SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    } while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
    UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
    UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430F5438A
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
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430FR5739
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430FR5969
    PM5CTL0 &= ~LOCKLPM5;         // Disable the GPIO power-on default high-impedance mode
                                  // to activate previously configured port settings
///////////////////////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////////////////////
}

static void postEvent(uint8_t handlerId) {
    uint8_t key = Em_Hal_lock();
    handlerEvents |= 1 << handlerId;
    Em_Hal_unlock(key);
}

static void uartInit() {
    EAP_CTL = UCSWRST;
    EAP_RX_ENABLE();
    EAP_TX_ENABLE();
    EAP_RX_ACK_CONFIG();
    EAP_RX_ACK_SET();
    EAP_TX_ACK_CONFIG();

    // suspend the MCM
    EAP_RX_ACK_CLR();
    
    // Setup the UART for 115200 baud
///////////////////////////////////////////////////////////////////////////////////////////////
#if defined MSP_EXP430G2
    EAP_CTL = UCSSEL_2 + UCSWRST;
    UCA0MCTL = UCBRF_0 + UCBRS_6;
    UCA0BR0 = 8;
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430F5529LP
    EAP_CTL = UCSSEL_2 + UCSWRST;
    UCA0BR0 = 9;                              // 1MHz 115200 (see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 115200
    UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430F5438A
    EAP_CTL = UCSSEL_2 + UCSWRST;
    UCA2BR0 = 9;                              // 1MHz 115200 (see User's Guide)
    UCA2BR1 = 0;                              // 1MHz 115200
    UCA2MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430FR5739
    EAP_CTL |= UCSSEL__SMCLK;               // Put eUSCI in reset, select SMCLK
    UCA1BRW = 8;                              // Settings from Users Guide
    UCA1MCTLW |= 0xD600;                      // 1000000 Hz SMCLK, 115200 baud
///////////////////////////////////////////////////////////////////////////////////////////////
#elif defined MSP_EXP430FR5969
    EAP_CTL |= UCSSEL__SMCLK;               // Put eUSCI in reset, select SMCLK
    UCA1BRW = 8;                              // Settings from Users Guide
    UCA1MCTLW |= 0xD600;                      // 1000000 Hz SMCLK, 115200 baud
///////////////////////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////////////////////
    EAP_CTL &= ~UCSWRST;
}

/* -------- INTERRUPT SERVICE ROUTINES -------- */

#ifdef __GNUC__
    __attribute__((interrupt(BUTTON_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
    #pragma vector=BUTTON_VECTOR
#endif
INTERRUPT void buttonIsr(void) {
    postEvent(BUTTON_HANDLER_ID);
    BUTTON_ENABLE();
    WAKEUP();
}

#ifdef __GNUC__
    __attribute__((interrupt(EAP_RX_VECTOR)))
#endif
#ifdef __TI_COMPILER_VERSION__
    #pragma vector=EAP_RX_VECTOR
#endif
INTERRUPT void rxIsr(void) {
  uint8_t b;
  switch(EAP_IV)
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
    case  2:  // CCR1
        UART_WATCH_DISABLE();
        Em_Message_restart();
        WAKEUP();
        break;
    }
}
