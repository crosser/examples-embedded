/* ###################################################################
**     Filename    : Events.c
**     Project     : Eap-FRDM-KL05Z
**     Processor   : MKL05Z32VLF4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-10, 19:14, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

extern void Hal_buttonIsr(void);
extern void Hal_rxIsr(void);
extern void Hal_timerIsr(void);
extern void Hal_txAckIsr(void);

/*
** ===================================================================
**     Event       :  TIMER_OnInterrupt (module Events)
**
**     Component   :  TIMER [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TIMER_OnInterrupt(LDD_TUserData *UserDataPtr)
{
    Hal_timerIsr();
}

/*
** ===================================================================
**     Event       :  BUTTON_OnInterrupt (module Events)
**
**     Component   :  BUTTON [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void BUTTON_OnInterrupt(LDD_TUserData *UserDataPtr)
{
    Hal_buttonIsr();
}

/*
** ===================================================================
**     Event       :  UART_OnBlockReceived (module Events)
**
**     Component   :  UART [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void UART_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
    Hal_rxIsr();
}

/*
** ===================================================================
**     Event       :  EAP_TX_ACK_OnInterrupt (module Events)
**
**     Component   :  EAP_TX_ACK [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EAP_TX_ACK_OnInterrupt(LDD_TUserData *UserDataPtr)
{
    Hal_txAckIsr();
}

/*
** ===================================================================
**     Event       :  WATCH_OnInterrupt (module Events)
**
**     Component   :  WATCH [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void WATCH_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
