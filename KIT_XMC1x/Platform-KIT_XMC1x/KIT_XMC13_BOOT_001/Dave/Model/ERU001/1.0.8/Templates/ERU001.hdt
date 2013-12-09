/*******************************************************************************
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
 * @file ERU001.h
 *
 * Revision History
 * 25 Jan 2013 v1.0.4 Initial Version
 * 14 Mar 2013 v1.0.6 Porting to XMC42xx and XMC44xx
 *
 * @brief  ERU001 App implementation header file.
 *
 */

#ifndef ERU001_H_
#define ERU001_H_
/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <DAVE3.h>

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/**
 * @ingroup ERU001_apidoc
 * @{
 */
/**
 * Macro which clears the Status Flag of ETLx.
 * @param[in]  Handle  ERU001 device handle.
 *
 * @brief     Function to clear Status Flag for ETLx.
 *
 *
 * @param[in]  App instance handle
 *
 * @return     None
 *
 * <b>Reentrant: NO </b><BR>
 * <b>Sync/Async:  Synchronous</b>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *  int main(void)
 *	{
 *	  // ... Initializes Apps configurations ...
 *	  DAVE_Init();
 *    //....
 *    ERU001_ClearFlag(ERU001_Handle0);
 *	}
 *
 * @endcode<BR> </p>
 *
 */
#define  ERU001_ClearFlag(Handle) CLR_BIT(Handle.ERURegs->EXICON[Handle.InputChannel],ERU_EXICON_FL_Pos)
/**
 * @}
 */

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/**
 * @ingroup ERU001_publicparam
 * @{
 */

/*******************************************************************************
 *                                STRUCTURES                                  **
 ******************************************************************************/
 


/**
 * @brief This data type describes the App Handle
 */ 
typedef struct ERU001_HandleType
{
  /**
   * Baseaddress of ERU module 
   */
  ERU_GLOBAL_TypeDef* ERURegs;  
  /**
   * Input channel No  
   */
  uint8_t InputChannel;           
}ERU001_HandleType;

/**
 * @brief This data type describes the possible status values returned
 * by functions.
 */
typedef enum ERU001_StatusType
{
 /**
  * Function Entry
  */
 /**
  * @cond INTERNAL_DOCS
  * @param MODULENAME ERU001
  * @endcond
  */
  ERU001_FUNCTION_ENTRY,
 /**
  * @cond INTERNAL_DOCS
  * @param ERRCODESTRING2 ERU001_FUN_EXIT
  * @param STRCODESTRING2 Exited function \%s
  * @endcond
  */
  ERU001_FUNCTION_EXIT
}ERU001_StatusType;
 /**
 * @}
 */




/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Extern Variables                                      **
*******************************************************************************/



/**
 * @ingroup ERU001_apidoc
 * @{
 */

/*******************************************************************************
**                     FUNCTION PROTOTYPES                                    **
*******************************************************************************/
 
/**
 * @brief     This function Initializes a  ERU001 App instances (ERSx+ETLx) 
 *            based on user configuration.
 *
 * @param[in]  None
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
 *	  DAVE_Init(); // ERU001_Init() will be called from DAVE_Init()
 *     while(1)
 *     {
 *     }
 *	}
 *
 * @endcode<BR> </p>
 */
void ERU001_Init(void);



/**
 *@}
 */
/* Inclusion of App Conf  Header file */
#include "ERU001_Conf.h"

#endif /* ERU001_H_ */
