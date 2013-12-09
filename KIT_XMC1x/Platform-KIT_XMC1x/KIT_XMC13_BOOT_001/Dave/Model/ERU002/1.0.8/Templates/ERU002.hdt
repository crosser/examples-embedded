/******************************************************************************
 *
 * Copyright (C) 2011 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with 
 * Infineon's microcontrollers.  
 * This file can be freely distributed within development tools that are 
 * supporting such microcontrollers. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, 
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000 Series/XMC1000 series                          **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : Mar 14, 2013                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** NPJ         App Developer                                                  **
*******************************************************************************/

/**
 * @file ERU002.h
 *
 * Revision History
 * 25 Jan 2013 v1.0.4 Initial Version
 * 14 Mar 2013 v1.0.6 Porting to XMC42xx and XMC44xx
 * 
 * @brief  Header file for ERU002 App
 *
 */

#ifndef ERU002_H_
#define ERU002_H_
/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <DAVE3.h>
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/**
 * @ingroup ERU002_apidoc
 * @{
 */
/**
 * Macro to check the pattern detection result flag.
 * @param[in]  Handle  ERU002 device handle.

 * <b>Reentrant: NO </b><BR>
 * <b>Sync/Async:  Synchronous</b>
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *  int main(void)
 *	{
 *   uint8_t PDFlag =0;
 *	  // ... Initializes Apps configurations ...
 *	  DAVE_Init();
 *    //....
 *    PDFlag = ERU002_GetPatternResult(ERU002_Handle0);
 *	}
 *
 * @endcode<BR> </p>
 *
 */

#define ERU002_GetPatternResult(Handle)    RD_REG(Handle.ERURegs->EXOCON[Handle.OutputChannel],\
												  ERU_EXOCON_PDR_Msk,ERU_EXOCON_PDR_Pos)

/**
 * @}
 */

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

 /**
 * @ingroup ERU002_publicparam
 * @{
 */

/*******************************************************************************
 *                                STRUCTURES                                  **
 ******************************************************************************/
 
/**
 * @brief App Handle Data structure.
 * Mapped ERU base address and Output Channel parameters are stored in this
 * structure.
 */
typedef struct ERU002_HandleType
{
 /**
  * Baseaddress of ERU module 
  */
  ERU_GLOBAL_TypeDef* ERURegs;  
  /**
  * Input channel No  
  */
  uint8_t OutputChannel;        
}ERU002_HandleType;

/**
 * @brief Enumurated structure which indicates the Status flags.
 */
typedef enum ERU002_StatusType
{
  /**
   * Function Entry
   */
 /**
  * @cond INTERNAL_DOCS
  * @param MODULENAME ERU001
  * @endcond
  */
  ERU002_FUNCTION_ENTRY,
 /**
  * @cond INTERNAL_DOCS
  * @param ERRCODESTRING2 ERU001_FUN_EXIT
  * @param STRCODESTRING2 Exited function \%s
  * @endcond
  */
  ERU002_FUNCTION_EXIT
}ERU002_StatusType;
 
 /**
 * @}
 */




/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Extern Variables                                      **
*******************************************************************************/


/*******************************************************************************
**                     FUNCTION PROTOTYPES                                    **
*******************************************************************************/




/**
 * @ingroup ERU002_apidoc
 * @{
 */

/**
 * @brief     This function Initializes a  ERU002 App instances (OGUy) 
 *            based on user configuration.
 *
 *
 * @return     None
 *
 * <b>Reentrant: NO </b><BR>
 * <b>Sync/Async:  Synchronous</b>
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *  int main(void)
 *	{
 *	  // ... Initializes Apps configurations ...
 *	  DAVE_Init(); // ERU002_Init() will be called from DAVE_Init()
 *     while(1)
 *     {
 *     }
 *	}
 *
 * @endcode<BR> </p>
 */
void ERU002_Init(void);


/**
 * @brief     Function to Select peripheral trigger input Source.
 *
 * @param[in]  App instance handle and ERU_OGU_y sel( ERU_OGU_y = SIGNAL_ERU_OGU_y3 for signal 1 and 
 *             ERU_OGU_y = SIGNAL_ERU_OGU_y1 for signal 0)
 *
 * @return     status
 *
 * <b>Reentrant: NO </b><BR>
 * <b>Sync/Async:  Synchronous</b>
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *  int main(void)
 *	{
 *   uint32_t status;
 *	  // ... Initializes Apps configurations ...
 *	  DAVE_Init();
 *    //....
 *    //ERU_OGU_y = SIGNAL_ERU_OGU_y3 for signal 1 
 *    //ERU_OGU_y = SIGNAL_ERU_OGU_y1 for signal 0
 *    status = ERU002_SetPeripheralTrigInputSrc(&ERU002_Handle0, SIGNAL_ERU_OGU_y3) ; 
 *	}
 *
 * @endcode<BR> </p>
 *
 */
uint32_t  ERU002_SetPeripheralTrigInputSrc(const ERU002_HandleType *handle, uint8_t ERU_OGU_y);


/**
 *@}
 */

/* Inclusion of App config file */
#include "ERU002_Conf.h"

#endif /* ERU002_H_ */
