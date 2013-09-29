__cs3_heap_end = __cs3_region_end_ram - 512;

EXTERN(Hal_buttonIsr)
__cs3_isr_gpio_f = Hal_buttonIsr;

EXTERN(Hal_rxIsr)
__cs3_isr_uart1 = Hal_rxIsr;

EXTERN(Hal_txAckIsr)
__cs3_isr_gpio_a = Hal_txAckIsr;

EXTERN(Hal_timerIsr)
__cs3_isr_timer0a = Hal_timerIsr;
