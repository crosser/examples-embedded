/**************************************************************************//**
 *
 * Copyright (C) 2011 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon’s microcontrollers.
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
** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : Mar 16, 2013                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** PAE    App Developer                                                       **
*******************************************************************************/

/**
 * @file IO002.h
 *
 * @brief Header file for IO_Digital_IO002 App
 */
/* Revision History 
 *
 * 01 Jan 2013 v1.0.12  Ported To XMC1000 Devices.
 * 16 Mar 2013 v1.0.14  Modified OMR register configuration (Direct assignment 
 *                        without reading) to upgrade performance.
 *
 */

#ifndef IO002_H_
#define IO002_H_

/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <DAVE3.h>


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/**
 * @ingroup IO002_publicparam
 * @{
 */

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/**
* PORTS
*/
typedef struct {
__IO uint32_t   OUT;     /*!<   Port 0 Output Register Offset  0x00000000   */
__O uint32_t    OMR;     /*!<   Port 0 Output Modification Register Offset  0x00000004   */
__I  uint32_t   RESERVED1[2];     /*!<      */
__IO uint32_t   IOCR0;     /*!<   Port 0 Input/Output Control Register 0 Offset  0x00000010   */
__IO uint32_t   IOCR4;     /*!<   Port 0 Input/Output Control Register 4 Offset  0x00000014   */
__IO uint32_t   IOCR8;     /*!<   Port 0 Input/Output Control Register 8 Offset  0x00000018   */
__IO uint32_t   IOCR12;     /*!<   Port 0 Input/Output Control Register 12 Offset  0x0000001C   */
__I  uint32_t   RESERVED2[1];     /*!<      */
__I uint32_t    IN;     /*!<   Port 0 Input Register Offset  0x00000024   */
__I  uint32_t   RESERVED3[6];     /*!<      */
__IO uint32_t   PDR0;     /*!<   Port 0 Pad Driver Mode 0 Register Offset  0x00000040   */
__IO uint32_t   PDR1;     /*!<   Port 0 Pad Driver Mode 1 Register Offset  0x00000044   */
__I  uint32_t   RESERVED4[6];     /*!<      */
__IO uint32_t   PDISC;     /*!<   Port 0 Pin Function Decision Control Register Offset  0x00000060   */
__I  uint32_t   RESERVED5[3];     /*!<      */
__IO uint32_t   PPS;     /*!<   Port 0 Pin Power Safe Register Offset  0x00000070   */
__IO uint32_t   HWSEL;     /*!<   Port 0 Pin Hardware Select Register Offset  0x00000074   */
}PORTS_TypeDef;

/**
 *This data type describes the App Handle
 */
typedef struct IO002_HandleType
{
  /** Port Number */
  uint8_t PortNr;
  /** Port pins */
  uint8_t PortPin;
  /** Port Regs */
  PORTS_TypeDef* PortRegs;
}IO002_HandleType;

/**
 * This data type describes the Input Mode type
 */ 

typedef enum IO002_InputModeType
{
  /** Tri-state */
  IO002_TRISTATE,
  /** Input pull-down device connected */
  IO002_PULL_DOWN_DEVICE,
  /** Input pull-up device connected */
  IO002_PULL_UP_DEVICE,
  /** Pn_OUTx continuously polls the input value */
  IO002_CONT_POLLING,
  /** Inverted tri-state */
  IO002_INV_TRISTATE,
  /** Inverted Input pull-down device connected */
  IO002_INV_PULL_DOWN_DEVICE,
  /** Inverted Input pull-up device connected */
  IO002_INV_PULL_UP_DEVICE,
  /** Inverted Pn_OUTx continuously polls the input value */
  IO002_INV_CONT_POLLING,
}IO002_InputModeType;

/**
 * This data type describes the Output Mode type
 */
typedef enum IO002_OutputModeType
{
  /** Push pull output */
  IO002_PUSHPULL =0x10,
  /** Open drain output */
  IO002_OPENDRAIN =0x18
}IO002_OutputModeType;
 
 /**
  * @}
  */
/*******************************************************************************
** FUNCTION PROTOTYPES                                                        **
*******************************************************************************/
/**
 * @ingroup IO002_apidoc
 * @{
 */

 /**
 * Initialises all the App instances based on user configuration
 *
 *
 *
 * @return     None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init();  // IO002_Init() is called within DAVE_Init()
 *    return 0;
 *  }
 * @endcode<BR> </p>
 */
void IO002_Init(void);

/**
 * @}
 */


/**
 * @ingroup IO002_apidoc
 * @{
 */

/**
 * This macro reads value at  port pin.
 *              
 *
 * @param[in]  Handle to Port Pin App Instance
 *
 * @return     Value at Pin
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    bool Value = 0;
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    Value = IO002_ReadPin(IO002_Handle0);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 *
 */
   /* <<<DD_IO002_API_2>>> */
#define IO002_ReadPin(Handle ) (((Handle.PortRegs->IN) >> Handle.PortPin) & 1U)

/**
 * This macro sets the chosen port pin to '1'.
 *              
 *
 * @param[in] Handle to Port Pin App Instance
 *
 * @return    None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    IO002_SetPin(IO002_Handle0);
 *    return 0;
 *  }
 * @endcode <BR> </p>
 */
   /* <<<DD_IO002_API_3>>> */
#define IO002_SetPin(Handle) (Handle.PortRegs->OMR = 1U << Handle.PortPin)



/**
 * This macro sets the chosen port pin to '0'.
 *              
 *
 * @param[in] Handle to Port Pin App Instance
 *
 * @return    None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    IO002_ResetPin(IO002_Handle0);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 */
   /* <<<DD_IO002_API_4>>> */
#define IO002_ResetPin(Handle) (Handle.PortRegs->OMR  = 0x10000UL << Handle.PortPin)


/**
 * This macro sets the chosen port pin with the boolean value provided.
 *
 * @param[in] Handle Handle to Port Pin App Instance
 * @param[in] Value Pin Status(0/1)
 *
 * @return    None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    IO002_SetOutputValue(IO002_Handle0,1);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 */
#define IO002_SetOutputValue(Handle,Value) (Handle.PortRegs->OMR = Value  ? (1U << Handle.PortPin):(0x10000UL << Handle.PortPin))


/**
 * This macro toggles the chosen port pin.
 *              
 *
 * @param[in]  Handle to Port Pin App Instance
 *
 * @return    None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    IO002_TogglePin(IO002_Handle0);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 */
    /* <<<DD_IO002_API_6>>> */
#define IO002_TogglePin(Handle) (Handle.PortRegs->OMR  = 0x10001UL << Handle.PortPin)



/**
 * Note: Currently this function is a place holder function. <BR>
 * The chosen port pin is configured as input.
 *            The following definitions for Mode are available:<BR>
 *              IO002_TRISTATE              (no pull device connected)<BR>
 *              IO002_PULL_DOWN_DEVICE      (pull-down device connected)<BR>
 *              IO002_PULL_UP_DEVICE        (pull-up device connected)<BR>
 *              IO002_CONT_POLLING          (Pn_OUTx continuously samples input value)<BR>
 *              IO002_INV_TRISTATE          (Inverted no pull device connected)<BR>
 *              IO002_INV_PULL_DOWN_DEVICE  (Inverted pull-down device connected)<BR>
 *              IO002_INV_PULL_UP_DEVICE    (Inverted pull-up device connected)<BR>
 *              IO002_INV_CONT_POLLING 	    (Pn_OUTx continuously samples input value)<BR>
 *
 *
 * @param[in]  Handle to Port Pin App Instance
 * @param[in]  Mode Input selection(Pull-Down,Pull-Up,Inv-Pull-Down,Inv-Pull-Up)
 *             for chosen port pin
 *
 * @return    None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    IO002_DisableOutputDriver(&IO002_Handle0,IO002_PULL_UP_DEVICE);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 */

void IO002_DisableOutputDriver(const IO002_HandleType* Handle,IO002_InputModeType Mode);


/**
 * Note: Currently this function is a place holder function. <BR>
 * The chosen port pin is configured as output.
 *            The following definitions for Mode are available:
 *            IO002_PUSHPULL  (push-pull mode)
 *            IO002_OPENDRAIN (open drain mode)
 *
 *
 * @param[in]  Handle to Port Pin App Instance
 * @param[in]  Mode - Output Characteristic(Push-Pull,Open-Drain)for chosen port Pin
 *
 * @return    None
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 * #include <DAVE3.h>
 *
 *  int main(void)
 *  {
 *    DAVE_Init(); // IO002_Init() is called within DAVE_Init()
 *    IO002_EnableOutputDriver(&IO002_Handle0,IO002_OPENDRAIN);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 *
 */
void IO002_EnableOutputDriver(const IO002_HandleType* Handle,IO002_OutputModeType Mode);

/**
 * @}
 */

/* Inclusion of App config file */
#include "IO002_Conf.h"

#endif /* IO002_H_ */

/*CODE_BLOCK_END*/

