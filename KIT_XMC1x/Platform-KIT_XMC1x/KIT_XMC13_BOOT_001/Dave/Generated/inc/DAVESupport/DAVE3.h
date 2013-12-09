/*******************************************************************************
**  DAVE App Name : DAVESupport       App Version: 1.0.38               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/


/**************************************************************************//**
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
** PLATFORM : Infineon <Microcontroller name, step>                           **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** MODIFICATION DATE : June 26, 2013                                          **
**                                                                            **
*******************************************************************************/

/**
 * @file  DAVE3.h
 *
 * @brief This file contains all public data structures,enums and function
 *        prototypes
 *
 * Revision History
 * 26 June 2013 v1.0.32 Initial Version
 *
 */

#ifndef _DAVE3_H_
#define _DAVE3_H_

//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void DAVE_Init(void);
      
//****************************************************************************
// @Project Includes
//****************************************************************************


#include <XMC1300.h>

#include "../../inc/LIBS/types.h"
	
#include "../../inc/DAVESupport/MULTIPLEXER.h"


// #include APP HEADER FILES.
	#include "../../inc/LIBS/LIBS.h" 
	#include "../../inc/CLK002/CLK002.h" 
	#include "../../inc/UART001/UART001.h" 
	#include "../../inc/SYSTM001/SYSTM001.h" 
	#include "../../inc/NVIC002/NVIC002.h" 
	#include "../../inc/IO002/IO002.h" 
	#include "../../inc/ERU001/ERU001.h" 
	#include "../../inc/ERU002/ERU002.h" 
	#include "../../inc/IO004/IO004.h" 

                     
#endif  /** ifndef _DAVE3_H_ */

