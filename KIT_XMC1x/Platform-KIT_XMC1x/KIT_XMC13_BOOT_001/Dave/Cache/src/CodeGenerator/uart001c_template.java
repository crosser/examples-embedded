package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class uart001c_template
{
  protected static String nl;
  public static synchronized uart001c_template create(String lineSeparator)
  {
    nl = lineSeparator;
    uart001c_template result = new uart001c_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = "/*CODE_BLOCK_BEGIN[UART001.c]*/" + NL + "/******************************************************************************" + NL + " Copyright (c) 2011, Infineon Technologies AG                                **" + NL + " All rights reserved.                                                        **" + NL + "                                                                             **" + NL + " Redistribution and use in source and binary forms, with or without          **" + NL + " modification,are permitted provided that the following conditions are met:  **" + NL + "                                                                             **" + NL + " *Redistributions of source code must retain the above copyright notice,     **" + NL + " this list of conditions and the following disclaimer.                       **" + NL + " *Redistributions in binary form must reproduce the above copyright notice,  **" + NL + " this list of conditions and the following disclaimer in the documentation   **" + NL + " and/or other materials provided with the distribution.                      **" + NL + " *Neither the name of the copyright holders nor the names of its             **" + NL + " contributors may be used to endorse or promote products derived from this   **" + NL + " software without specific prior written permission.                         **" + NL + "                                                                             **" + NL + " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" **" + NL + " AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   **" + NL + " IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  **" + NL + " ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  **" + NL + " LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        **" + NL + " CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        **" + NL + " SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   **" + NL + " INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     **" + NL + " CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      **" + NL + " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  **" + NL + " POSSIBILITY OF SUCH DAMAGE.                                                 **" + NL + "                                                                             **" + NL + " To improve the quality of the software, users are encouraged to share       **" + NL + " modifications, enhancements or bug fixes with Infineon Technologies AG      **" + NL + " dave@infineon.com).                                                         **" + NL + "                                                                             **" + NL + "*******************************************************************************" + NL + "**                                                                           **" + NL + "**                                                                           **" + NL + "** PLATFORM : Infineon XMC4000/ XMC1000 Series                               **" + NL + "**                                                                           **" + NL + "** COMPILER : Compiler Independent                                           **" + NL + "**                                                                           **" + NL + "** AUTHOR   : App Developer                                                  **" + NL + "**                                                                           **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                      **" + NL + "**                                                                           **" + NL + "** MODIFICATION DATE : Jul 25, 2013                                          **" + NL + "**                                                                           **" + NL + "******************************************************************************/" + NL + "/******************************************************************************" + NL + "**                      Author(s) Identity                                   **" + NL + "*******************************************************************************" + NL + "**                                                                           **" + NL + "** Initials     Name                                                         **" + NL + "** --------------------------------------------------------------------------**" + NL + "** PAE          App Developer                                                **" + NL + "******************************************************************************/" + NL + "/**" + NL + " * @file UART001.c" + NL + " * " + NL + " * @App Version UART001 <";
  protected final String TEXT_2 = ">" + NL + " *" + NL + " * @brief  UART001 App provides non reentrant APIs for higher level Apps " + NL + " *          which can be used in a Non -RTOS environment. " + NL + " *           Limitations of Simple UART App" + NL + " *           a) Read/Write functions are non reentrant." + NL + " *           b) No support for DMA mode" + NL + " */" + NL + "/*" + NL + " * Revision History" + NL + " * 04 Dec 2012 v1.0.4  Changes from 1.0.2 are" + NL + " *                     1. Modified for baud calculation during initialization." + NL + " *                     2. Modified the macros FUNCTION_ENTRY, FUNCTION_EXIT and" + NL + " *                     ERROR" + NL + " *                     3. The hard coded values are replaced with macros in" + NL + " *                     UART001_lConfigureBaudRate() function." + NL + " *                     4. The PCTQ value update in BRG register is removed as" + NL + " *                     the value is taken as zero." + NL + " *                     5. Modified as per coding guidelines and MISRA checks" + NL + " * 26 Mar 2013 v1.0.10 1. Updated for the baud calculation in UART001_lInit()" + NL + " *                     function." + NL + " *                     2. Updated for the alignment in revision history." + NL + " *                     3. Updated the UART001_Init() function for disabling the" + NL + " *                     clock gating signal for XMC1000 devices." + NL + " *                     4. Updated function UART001_lConfigureBaudRate() for the" + NL + " *                     Baud rate calculation." + NL + " * 25 Jul 2013 v1.0.16 1. Removed TBIF bit configuration from UART001_lInit as " + NL + " *                     polling is not used in the UART001 App. " + NL + " *                     2. Added open-drain output configuration for Half duplex " + NL + " *                     operation mode to allow the wired-AND connection in" + NL + " *                     multiple transmitter communication." + NL + " *                     3. Added CCR.MODE configurations in UART001_lInit() " + NL + " *                     & UART001_Configure to disable the UART mode before " + NL + " *                     configuring USIC registers & to enable the UART mode " + NL + " *                     after configurations to avoid unintended edges." + NL + " *                     4. Modified the input parameter of " + NL + " *                     UART001_WriteDataMultiple() from const uint16_t* to " + NL + " *                     uint16_t* to maintain backward compatibility." + NL + " *                     5. TX pin set logic high (1) before configuring Open " + NL + " *                     Drain mode for Half Duplex operation mode.                     \t                                                     " + NL + " */" + NL + "/******************************************************************************" + NL + " ** INCLUDE FILES                                                            **" + NL + " *****************************************************************************/" + NL + "" + NL + "#include <DAVE3.h>" + NL;
  protected final String TEXT_3 = NL;
  protected final String TEXT_4 = "  " + NL + "/*****************************************************************************" + NL + "              DUMMY DEFINTIONS OF DEBUG LOG MACROS" + NL + "*****************************************************************************/" + NL + "/*These definitions are included here to avoid compilation errors," + NL + " since the DBG002 app is not part of the project. All the macros are defined" + NL + " as empty*/ " + NL + "#ifndef _DBG002_H_" + NL + "" + NL + "#define DBG002_RegisterCallBack(A,B,C)" + NL + "#define DBG002_I(e) " + NL + "#define DBG002_IG(e,g) " + NL + "#define DBG002_IH(e,h) " + NL + "#define DBG002_IP(e,p) " + NL + "#define DBG002_IGH(e,g,h) " + NL + "#define DBG002_IGP(e,g,p) " + NL + "#define DBG002_IHP(e,h,p) " + NL + "#define DBG002_IGHP(e,g,h,p) " + NL + "#define DBG002_N(e) " + NL + "#define DBG002_NG(e,g) " + NL + "#define DBG002_NH(e,h) " + NL + "#define DBG002_NP(e,p) " + NL + "#define DBG002_NGH(e,g,h) " + NL + "#define DBG002_NGP(e,g,p) " + NL + "#define DBG002_NHP(e,h,p) " + NL + "#define DBG002_NGHP(e,g,h,p) " + NL + "#define DBG002_ID(e) " + NL + "#define DBG002_IS(e) " + NL + "#define DBG002_ISG(e,g) " + NL + "#define DBG002_SAFETY_CRITICAL(groupid,messageid,length,value)" + NL + "#define DBG002_CRITICAL(groupid,messageid,length,value)" + NL + "#define DBG002_ERROR(groupid,messageid,length,value)" + NL + "#define DBG002_WARNING(groupid,messageid,length,value)" + NL + "#define DBG002_INFO(groupid,messageid,length,value)" + NL + "#define DBG002_TRACE(groupid,messageid,length,value)" + NL + "#define DBG002_FUNCTION_ENTRY(GID, Status) " + NL + "#define DBG002_FUNCTION_EXIT(GID, Status) " + NL + "" + NL + "#endif/* End of defintions of dummy Debug Log macros*/";
  protected final String TEXT_5 = "                  ";
  protected final String TEXT_6 = "  " + NL;
  protected final String TEXT_7 = " " + NL + "  /* System Core clock frequency in MHz */" + NL + "#define UART001_CLOCK  ";
  protected final String TEXT_8 = "F";
  protected final String TEXT_9 = NL + "// CHANNEL IS NOT MAPPED";
  protected final String TEXT_10 = NL + NL + "/******************************************************************************" + NL + "**                      Private Macro Definitions                            **" + NL + "******************************************************************************/" + NL + "#define APP_GID DBG002_GID_UART001" + NL + "" + NL + "/*Flag Offset Transmit Receive Buffer */" + NL + "#define UART001_FLAG_OFFSET                            (0x05U)" + NL + "" + NL + "#define UART001_MAX_VALUE                              (1024U)" + NL + "/* (DCTQ + 1) DCTQ value is 9 */" + NL + "#define UART001_DCTQ_VALUE                             (0x0AUL)" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Private Type Definitions                             **" + NL + "******************************************************************************/" + NL + "" + NL + "" + NL + "/******************************************************************************" + NL + "**                 Private Function Declarations:" + NL + "******************************************************************************/" + NL + "" + NL + "/* Initializes the App based on User provide configuration. */" + NL + "void UART001_lInit (const UART001_HandleType* Handle);" + NL + "" + NL + "/* Give optimized PDIV and STEP value for the given baud rate */ " + NL + "void UART001_lConfigureBaudRate\\" + NL + "                           (uint32_t BaudRate,uint32_t* Pdiv,uint32_t* Step);" + NL + "/* to find the real type */" + NL + "float UART001_labsRealType(float Number);                           " + NL + "/******************************************************************************" + NL + "**                      Global Constant Definitions                          **" + NL + "******************************************************************************/" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Global Variable Definitions                          **" + NL + "******************************************************************************/" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Private Constant Definitions                         **" + NL + "******************************************************************************/" + NL + "" + NL + "/******************************************************************************" + NL + "**                 Function like macro definitions                           **" + NL + "******************************************************************************/" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Private Function Definitions                         **" + NL + "******************************************************************************/" + NL + "/* Initializes the App based on User provide configuration. */" + NL + " " + NL + "void UART001_lInit (const UART001_HandleType* Handle)" + NL + "{" + NL + "  USIC_CH_TypeDef* UartRegs = Handle->UartRegs;" + NL + "" + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + " /* <<<DD_UART001_API_1>>>*/" + NL + " " + NL + "  /** UART initialization  */" + NL + "" + NL + "  /* Disable UART mode before configuring all USIC registers to avoid unintended edges */ " + NL + "  UartRegs->CCR &= ~( ((uint32_t)(UART_MODE  & USIC_CH_CCR_MODE_Msk))); " + NL + "" + NL + "  /* Enable the USIC Channel */" + NL + "  UartRegs->KSCFG |= ((((uint32_t)0x01  & USIC_CH_KSCFG_MODEN_Msk)) | \\" + NL + "                       (((uint32_t)0x01 << USIC_CH_KSCFG_BPMODEN_Pos) &  \\" + NL + "                         USIC_CH_KSCFG_BPMODEN_Msk)); " + NL + "   " + NL + "  /* Configuration of USIC Channel Fractional Divider */" + NL + "" + NL + "  /* Fractional divider mode selected */" + NL + "  UartRegs->FDR |= (((uint32_t)0x02 << USIC_CH_FDR_DM_Pos) \\" + NL + "                                                         & USIC_CH_FDR_DM_Msk);" + NL + "  " + NL + "  /* Step value */" + NL + "  UartRegs->FDR |= ((Handle->BGR_STEP) & USIC_CH_FDR_STEP_Msk);" + NL + "          " + NL + "  /* The PreDivider for CTQ, PCTQ = 0  */" + NL + "  /* The Denominator for CTQ, DCTQ = 16 */" + NL + "    " + NL + "  UartRegs->BRG |= \\" + NL + "\t  ((((uint32_t)(Handle->BGR_PCTQ) << USIC_CH_BRG_PCTQ_Pos) & \\" + NL + "\t\t  \t     USIC_CH_BRG_PCTQ_Msk) | \\" + NL + "      (((uint32_t)(Handle->BGR_DCTQ) << USIC_CH_BRG_DCTQ_Pos) & \\" + NL + "\t     USIC_CH_BRG_DCTQ_Msk) | \\" + NL + "      (((uint32_t)(Handle->BGR_PDIV) << USIC_CH_BRG_PDIV_Pos) &  \\" + NL + "\t     USIC_CH_BRG_PDIV_Msk));" + NL + " " + NL + "  /* Configuration of USIC Shift Control */" + NL + "  " + NL + "  /* Transmit/Receive LSB first is selected  */" + NL + "  /* Transmission Mode (TRM) = 1  */" + NL + "  /* Passive Data Level (PDL) = 1 */" + NL + "  UartRegs->SCTR |= ((((uint32_t)0x01  << USIC_CH_SCTR_PDL_Pos) & \\" + NL + "    USIC_CH_SCTR_PDL_Msk ) | \\" + NL + "    (((uint32_t)0x01  <<  USIC_CH_SCTR_TRM_Pos ) &   USIC_CH_SCTR_TRM_Msk ));" + NL + "  /* Set Word Length (WLE) & Frame Length (FLE) */" + NL + "  UartRegs->SCTR |= ((((uint32_t)Handle->DataBits  << USIC_CH_SCTR_FLE_Pos) & \\" + NL + "                      USIC_CH_SCTR_FLE_Msk ) | \\" + NL + "                     (((uint32_t)Handle->DataBits  << USIC_CH_SCTR_WLE_Pos) & \\" + NL + "                        USIC_CH_SCTR_WLE_Msk));" + NL + "" + NL + "       " + NL + "  /* Configuration of USIC Transmit Control/Status Register */ " + NL + "  /* TBUF Data Enable (TDEN) = 1 */" + NL + "  /* TBUF Data Single Shot Mode (TDSSM) = 1 */" + NL + "\t" + NL + "  UartRegs->TCSR |= ((((uint32_t)0x01  << USIC_CH_TCSR_TDEN_Pos) & \\" + NL + "    USIC_CH_TCSR_TDEN_Msk ) | \\" + NL + "    (((uint32_t)0x01  << USIC_CH_TCSR_TDSSM_Pos) & USIC_CH_TCSR_TDSSM_Msk));" + NL + "" + NL + "  /* Configuration of Protocol Control Register */ " + NL + "  /* Sample Mode (SMD) = 1 */" + NL + "  /* 1 Stop bit is selected */   " + NL + "  /* Sample Point (SP) as configured */" + NL + "  /* Pulse Length (PL) = 0 */" + NL + "  " + NL + "  UartRegs->PCR_ASCMode |= ((((uint32_t)0x01 & USIC_CH_PCR_ASCMode_SMD_Msk)) |\\" + NL + "    (((uint32_t)Handle->StopBit  << USIC_CH_PCR_ASCMode_STPB_Pos) & \\" + NL + "    USIC_CH_PCR_ASCMode_STPB_Msk) | \\" + NL + "    (((uint32_t)(Handle->BGR_SP) << USIC_CH_PCR_ASCMode_SP_Pos) & \\" + NL + "    USIC_CH_PCR_ASCMode_SP_Msk));" + NL + "      " + NL + "  if(Handle->RecvNoiseEn)" + NL + "  {" + NL + "   \t/* Enable Receiver Noise Interrupt*/  " + NL + "    UartRegs->PCR_ASCMode |=(((uint32_t)0x01  << USIC_CH_PCR_CTR5_Pos) & \\" + NL + "\t\t  \t  \t  \t  \t  USIC_CH_PCR_CTR5_Msk); " + NL + "  }" + NL + "  " + NL + "  if(Handle->FormatErrEn)" + NL + "  {" + NL + "   \t/* Enable Format Error Interrupt*/  " + NL + "    UartRegs->PCR_ASCMode |=(((uint32_t)0x01  << USIC_CH_PCR_CTR6_Pos) & \\" + NL + "\t\t  \t  \t  \t  \t                                    USIC_CH_PCR_CTR6_Msk); " + NL + "  }" + NL + "  " + NL + "  if(Handle->FrameFinEn)" + NL + "  {" + NL + "   \t/* Enable Frame Finished Interrupt*/  " + NL + "    UartRegs->PCR_ASCMode |=(((uint32_t)0x01  << USIC_CH_PCR_CTR7_Pos) & \\" + NL + "\t\t  \t                                   \t  \t  \t  USIC_CH_PCR_CTR7_Msk); " + NL + "  } " + NL + "\t" + NL + "  /* Configuration of Transmitter Buffer Control Register */ " + NL + "  UartRegs->TBCTR |= ((((uint32_t)Handle->TxLimit  << \\" + NL + "                    USIC_CH_TBCTR_LIMIT_Pos ) & USIC_CH_TBCTR_LIMIT_Msk));" + NL + "    " + NL + "  /* Configuration of Receiver Buffer Control Register */ " + NL + "  UartRegs->RBCTR |= ((((uint32_t)Handle->RxLimit  << \\" + NL + "                       USIC_CH_RBCTR_LIMIT_Pos) & USIC_CH_RBCTR_LIMIT_Msk) | \\" + NL + "\t                    (((uint32_t)0x01 << USIC_CH_RBCTR_LOF_Pos) & \\" + NL + "                       USIC_CH_RBCTR_LOF_Msk));" + NL + "   " + NL + "  /* Configuration of Channel Control Register */ " + NL + "  /* parity generation is disabled*/" + NL + "  UartRegs->CCR |= (((uint32_t)(UART_MODE  & USIC_CH_CCR_MODE_Msk)) | \\" + NL + "                    (((uint32_t)Handle->Parity  << USIC_CH_CCR_PM_Pos) & \\" + NL + "                     USIC_CH_CCR_PM_Msk));" + NL + "  " + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "}" + NL + "" + NL + "" + NL + "float UART001_labsRealType(float Number)" + NL + "{" + NL + "   float return_value;" + NL + "\tif (Number < 0.0){" + NL + "\t\treturn_value = -Number;" + NL + "\t}" + NL + "\telse{" + NL + "\t\treturn_value = Number;" + NL + "\t}" + NL + "\treturn return_value;" + NL + "}" + NL + "" + NL + "/* Give optimized PDIV and STEP value for the given baud rate */ " + NL + "void UART001_lConfigureBaudRate\\" + NL + "                              (uint32_t BaudRate,uint32_t* Pdiv,uint32_t* Step)" + NL + "{" + NL + "\tuint32_t fdr_step = 0x00U;" + NL + "\tuint32_t brg_pdiv = 0x00U;" + NL + "\tuint32_t divisor_in = BaudRate ;" + NL + "\t/* fPB / 1024 * (Brg_dctq + 1) */" + NL + "\tuint32_t dividend_in = 0U;" + NL + "\tuint32_t divisor[4];" + NL + "\tuint32_t dividend[4];" + NL + "\tuint32_t remainder[4];" + NL + "\tuint32_t divisor_array[4];" + NL + "\tuint32_t dividend_array[4];" + NL + "\tuint32_t div_array[4];" + NL + "\tuint32_t max, frac,divisor1,divisor2,dividend1,dividend2;" + NL + "\tuint32_t array_count,array_count_1,array_count_2;" + NL + "\tuint32_t do_while_break = 0U;" + NL + "\tuint32_t temp = 0U;" + NL + "\tfloat div_factor;" + NL + "\tuint8_t loop_cnt;" + NL + "\tbool swapped;" + NL + "\tdividend_in = (uint32_t)((uint32_t)(UART001_CLOCK * 1000000)/ \\" + NL + "                    \t(UART001_MAX_VALUE * UART001_DCTQ_VALUE)); " + NL + "\t/* swap if divisor_in/dividend_in > max_divisor/max_dividend */" + NL + "\tdiv_factor = (float) divisor_in/(float) dividend_in;" + NL + "\tif ( div_factor > 1.0)" + NL + "\t{" + NL + "\t\tmax = UART001_MAX_VALUE;" + NL + "\t\tswapped = 1U;" + NL + "\t\ttemp = divisor_in;" + NL + "\t\tdivisor_in = dividend_in;" + NL + "\t\tdividend_in = temp;" + NL + "\t}" + NL + "\telse" + NL + "\t{" + NL + "\t\tswapped = 0U;" + NL + "\t\tmax = UART001_MAX_VALUE;" + NL + "\t}" + NL + "\t/*Init parameters*/" + NL + "\tloop_cnt = 0U;" + NL + "\tarray_count = 0U;" + NL + "\tarray_count_1 = 0U;" + NL + "\tdivisor[0] = divisor_in;" + NL + "\tremainder[0] = dividend_in;" + NL + "\tdivisor_array[0] = 1U;" + NL + "\tdividend_array[0] = 0U;" + NL + "\tdo {" + NL + "\t\t\t++loop_cnt;" + NL + "\t\t\tarray_count_2 = array_count_1; /* on first loop is not used */" + NL + "\t\t\tarray_count_1 = array_count;" + NL + "\t\t\tarray_count = loop_cnt % 4U;" + NL + "\t\t\tdividend[array_count] = divisor[array_count_1];" + NL + "\t\t\t" + NL + "\t\t\tdivisor[array_count] = remainder[array_count_1];" + NL + "\t\t\t" + NL + "\t\t\tdiv_array[array_count] = dividend[array_count] / divisor[array_count];" + NL + "\t\t\t" + NL + "\t\t\tremainder[array_count] = dividend[array_count] % divisor[array_count];" + NL + "\t\t\t" + NL + "\t\t\t/* This executed only on first loop */" + NL + "\t\t\tif (loop_cnt == 1U)" + NL + "\t\t\t{ " + NL + "\t\t\t\tdivisor_array[1] = div_array[1];" + NL + "\t\t\t\tdividend_array[1] = 1U;" + NL + "\t\t\t}" + NL + "\t\t\telse" + NL + "\t\t\t{" + NL + "\t\t\t\tdivisor_array[array_count] = \\" + NL + "\t\t\t\t      (div_array[array_count] * divisor_array[array_count_1]) + \\" + NL + "\t\t\t\t       divisor_array[array_count_2];" + NL + "\t\t\t\tdividend_array[array_count] = \\" + NL + "\t\t\t\t      (div_array[array_count] * dividend_array[array_count_1]) + \\" + NL + "\t\t\t\t       dividend_array[array_count_2];" + NL + "\t\t\t}" + NL + "\t\t\tif (dividend_array[array_count] > max) " + NL + "\t\t\t{" + NL + "\t\t\t\tdivisor1 = divisor_array[array_count_1];" + NL + "\t\t\t\tdividend1 = dividend_array[array_count_1];" + NL + "\t\t\t\tfrac = (uint32_t)(max - dividend_array[array_count_2]) / \\" + NL + "\t\t\t\t                               dividend_array[array_count_1];" + NL + "\t\t\t\tdivisor2 = (uint32_t)(frac * divisor_array[array_count-1]) + \\" + NL + "\t\t\t\t                                divisor_array[array_count-2];" + NL + "\t\t\t\tdividend2 = (uint32_t)(frac * dividend_array[array_count-1]) + \\" + NL + "\t\t\t\t                               dividend_array[array_count_2];" + NL + "\t\t\t\t/* Swap if required */" + NL + "\t\t\t\tif (swapped) {" + NL + "\t\t\t\t\t\t/* Swap divisor1 and dividend1 */" + NL + "\t\t\t\t\t\ttemp = divisor1;" + NL + "\t\t\t\t\t\tdivisor1 = dividend1;" + NL + "\t\t\t\t\t\tdividend1 = temp;" + NL + "\t\t\t\t\t\t/* Swap divisor2 and dividend2 */" + NL + "\t\t\t\t\t\ttemp = divisor2;" + NL + "\t\t\t\t\t\tdivisor2 = dividend2;" + NL + "\t\t\t\t\t\tdividend2 = temp;" + NL + "\t\t\t\t\t}" + NL + "\t\t\t\t/* Remove if one of has divisor 0 */" + NL + "\t\t\t\tif ((dividend1 == 0U) || (divisor1 == 0U)) {" + NL + "\t\t\t\t\tfdr_step = divisor2;" + NL + "\t\t\t\t\tbrg_pdiv = dividend2;" + NL + "\t\t\t\t}else if ((dividend2 == 0U) || (divisor2 == 0U)) {" + NL + "\t\t\t\t\tfdr_step = divisor1;" + NL + "\t\t\t\t\tbrg_pdiv = dividend1;" + NL + "\t\t\t\t}else { " + NL + "\t\t\t\t\t/*  Find the most nearest to target division */" + NL + "\t\t\t\t\tif (UART001_labsRealType(div_factor - \\" + NL + "\t\t\t\t\t    ((float) divisor1 / (float) dividend1 )) > \\" + NL + "\t\t\t\t\t    UART001_labsRealType(div_factor - \\" + NL + "\t\t\t\t\t    ((float) divisor2 / (float) dividend2 ))) " + NL + "\t\t\t\t\t{" + NL + "\t\t\t\t\t\tfdr_step = divisor2;" + NL + "\t\t\t\t\t\tbrg_pdiv = dividend2;" + NL + "\t\t\t\t\t}else {" + NL + "\t\t\t\t\t\tfdr_step = divisor1;" + NL + "\t\t\t\t\t\tbrg_pdiv = dividend1;" + NL + "\t\t\t\t\t}" + NL + "\t\t\t\t}" + NL + "\t\t\t\tdo_while_break = 0x05U;" + NL + "\t\t\t}" + NL + "\t\t\telse if (remainder[array_count]== 0U) " + NL + "\t\t\t{" + NL + "\t\t\t\tfdr_step = divisor_array[array_count];" + NL + "\t\t\t\tbrg_pdiv = dividend_array[array_count];" + NL + "\t\t\t\tif (swapped)" + NL + "\t\t\t\t{" + NL + "\t\t\t\t\t/* Swap fdr_step and brg_pdiv */" + NL + "\t\t\t\t\ttemp = fdr_step;" + NL + "\t\t\t\t\tfdr_step = brg_pdiv;" + NL + "\t\t\t\t\tbrg_pdiv = temp;" + NL + "\t\t\t\t}" + NL + "\t\t\t\tdo_while_break = 0x05U;" + NL + "\t\t\t}" + NL + "\t\t\telse {" + NL + "\t\t\t  /* Do Nothing */" + NL + "\t\t\t}" + NL + "\t\t} while (do_while_break != 0x05U);" + NL + "" + NL + "\tif(fdr_step >= UART001_MAX_VALUE)" + NL + "\t{" + NL + "\t   fdr_step = 1023U;" + NL + "\t}" + NL + "" + NL + "\t*Step = (uint32_t)fdr_step;" + NL + "" + NL + "\t*Pdiv = (uint32_t)(brg_pdiv - 1U);" + NL + "}" + NL + "/******************************************************************************" + NL + "**                      Public Function Definitions                          **" + NL + "******************************************************************************/" + NL + "void UART001_Init(void)" + NL + "{" + NL;
  protected final String TEXT_11 = NL + "    /* Disable the USIC0 clock gating */" + NL + "    /* " + NL + "     * The disabling of the clock gating is applicable only for" + NL + "     * XMC4400, XMC4200 and XMC1000 devices." + NL + "     */";
  protected final String TEXT_12 = NL + "    SCU_GENERAL->PASSWD = 0x000000C0UL;" + NL + "    WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, \\" + NL + "                                  SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);";
  protected final String TEXT_13 = NL + "    SET_BIT(SCU_CLK->CGATCLR0, SCU_CLK_CGATCLR0_USIC0_Pos);";
  protected final String TEXT_14 = NL + "    while ((SCU_CLK->CLKCR)&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "    {" + NL + "  \t ;" + NL + "    }" + NL + "    SCU_GENERAL->PASSWD = 0x000000C3UL;     ";
  protected final String TEXT_15 = NL + "/* Reset the Peripheral*/" + NL + "    RESET001_DeassertReset(PER0_USIC";
  protected final String TEXT_16 = ");";
  protected final String TEXT_17 = NL + "    /* Disable the USIC1 clock gating */" + NL + "    /* " + NL + "     * The disabling of the clock gating is applicable only for" + NL + "     * XMC4400, XMC4200 and XMC1000 devices." + NL + "     */";
  protected final String TEXT_18 = NL + "    SCU_GENERAL->PASSWD = 0x000000C0UL;" + NL + "    WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, \\" + NL + "                                  SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);";
  protected final String TEXT_19 = NL + "    SET_BIT(SCU_CLK->CGATCLR1, SCU_CLK_CGATCLR1_USIC1_Pos);";
  protected final String TEXT_20 = NL + "    while ((SCU_CLK->CLKCR)&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "    {" + NL + "  \t  ;" + NL + "    }" + NL + "    SCU_GENERAL->PASSWD = 0x000000C3UL;     ";
  protected final String TEXT_21 = NL + "    /* Reset the Peripheral*/" + NL + "    RESET001_DeassertReset(PER1_USIC";
  protected final String TEXT_22 = "); ";
  protected final String TEXT_23 = " ";
  protected final String TEXT_24 = NL + "    UART001_lInit(&UART001_Handle";
  protected final String TEXT_25 = "); ";
  protected final String TEXT_26 = "   ";
  protected final String TEXT_27 = NL + "    /* Configure TX Pin in Open-drain mode to allow the Wired-AND connection */" + NL + "    PORT";
  protected final String TEXT_28 = "->OMR |= ((uint32_t)0x01 << ";
  protected final String TEXT_29 = ");";
  protected final String TEXT_30 = NL + "    PORT";
  protected final String TEXT_31 = "->IOCR0 |= (0x18 << ";
  protected final String TEXT_32 = ");";
  protected final String TEXT_33 = NL + "    PORT";
  protected final String TEXT_34 = "->IOCR4 |= (0x18 << ";
  protected final String TEXT_35 = ");";
  protected final String TEXT_36 = NL + "    PORT";
  protected final String TEXT_37 = "->IOCR8 |= (0x18 << ";
  protected final String TEXT_38 = ");";
  protected final String TEXT_39 = NL + "    PORT";
  protected final String TEXT_40 = "->IOCR12 |= (0x18 << ";
  protected final String TEXT_41 = ");";
  protected final String TEXT_42 = "    " + NL + "    /* Configuration of TX Pin ";
  protected final String TEXT_43 = ".";
  protected final String TEXT_44 = " based on User configuration */     ";
  protected final String TEXT_45 = NL + "    /* PDR_PD = ";
  protected final String TEXT_46 = "  */" + NL;
  protected final String TEXT_47 = NL + "    PORT";
  protected final String TEXT_48 = "->PDR0  &= (~(PORT";
  protected final String TEXT_49 = "_PDR0_PD";
  protected final String TEXT_50 = "_Msk));";
  protected final String TEXT_51 = NL + "    PORT";
  protected final String TEXT_52 = "->PDR0  |= (((uint32_t)";
  protected final String TEXT_53 = " << PORT";
  protected final String TEXT_54 = "_PDR0_PD";
  protected final String TEXT_55 = "_Pos) & \\" + NL + "                                             PORT";
  protected final String TEXT_56 = "_PDR0_PD";
  protected final String TEXT_57 = "_Msk);";
  protected final String TEXT_58 = NL + "    PORT";
  protected final String TEXT_59 = "->PDR1 &= (~(PORT";
  protected final String TEXT_60 = "_PDR1_PD";
  protected final String TEXT_61 = "_Msk));";
  protected final String TEXT_62 = NL + "    PORT";
  protected final String TEXT_63 = "->PDR1 |= (((uint32_t)";
  protected final String TEXT_64 = " << PORT";
  protected final String TEXT_65 = "_PDR1_PD";
  protected final String TEXT_66 = "_Pos) & \\" + NL + "                                        PORT";
  protected final String TEXT_67 = "_PDR1_PD";
  protected final String TEXT_68 = "_Msk);    ";
  protected final String TEXT_69 = " ";
  protected final String TEXT_70 = "   ";
  protected final String TEXT_71 = NL + "    /* TXPIN instance (no.";
  protected final String TEXT_72 = ") is not mapped to any port pin. */";
  protected final String TEXT_73 = "    ";
  protected final String TEXT_74 = " " + NL + "    /* Configuration of RX Pin ";
  protected final String TEXT_75 = ".";
  protected final String TEXT_76 = " based on User configuration */";
  protected final String TEXT_77 = NL + "\tPORT";
  protected final String TEXT_78 = "->IOCR0 |= ((uint32_t)";
  protected final String TEXT_79 = " << ";
  protected final String TEXT_80 = ");";
  protected final String TEXT_81 = NL + "\t";
  protected final String TEXT_82 = NL + "\tPORT";
  protected final String TEXT_83 = "->IOCR4 |= ((uint32_t)";
  protected final String TEXT_84 = " << ";
  protected final String TEXT_85 = ");";
  protected final String TEXT_86 = NL + "\t";
  protected final String TEXT_87 = NL + "\tPORT";
  protected final String TEXT_88 = "->IOCR8 |= ((uint32_t)";
  protected final String TEXT_89 = " << ";
  protected final String TEXT_90 = ");";
  protected final String TEXT_91 = NL + "\t";
  protected final String TEXT_92 = NL + "\tPORT";
  protected final String TEXT_93 = "->IOCR12 |= ((uint32_t)";
  protected final String TEXT_94 = " << ";
  protected final String TEXT_95 = ");";
  protected final String TEXT_96 = NL + "\t";
  protected final String TEXT_97 = "     ";
  protected final String TEXT_98 = NL + "     /* RXPIN instance (no.";
  protected final String TEXT_99 = ") is not mapped to any port pin. */";
  protected final String TEXT_100 = NL + "// CHANNEL IS NOT MAPPED";
  protected final String TEXT_101 = NL + "}" + NL + " /* Function provide to reset the App to default values. */" + NL + " void  UART001_DeInit (const UART001_HandleType* Handle)" + NL + "{" + NL + "  /* <<<DD_UART001_API_2>>> */" + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + "  " + NL + "    " + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "}" + NL + "" + NL + "/* Function which allows changing of baudrate,parity & stopbit at run time.*/" + NL + "status_t  UART001_Configure" + NL + "( " + NL + "  const UART001_HandleType* Handle," + NL + "  uint32_t BaudRate," + NL + "  UART_ParityType Parity," + NL + "  UART_StopBitType Stopbit" + NL + ")" + NL + "{" + NL + "   uint32_t Brg_Pdiv = 0x00U;" + NL + "   uint32_t Fdr_Step = 0x00U;" + NL + "   uint32_t TXIDLE_status;" + NL + "   uint32_t RXIDLE_status;" + NL + "   USIC_CH_TypeDef* UartRegs = Handle->UartRegs;" + NL + "   status_t Status = (status_t)UART001_ERROR;" + NL + "   " + NL + "   DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + "   /* <<<DD_UART001_API_3>>>*/" + NL + "" + NL + "   TXIDLE_status = (uint32_t)\\" + NL + "                 RD_REG(UartRegs->PSR_ASCMode,USIC_CH_PSR_ASCMode_TXIDLE_Msk, \\" + NL + "\t                       USIC_CH_PSR_ASCMode_TXIDLE_Pos);" + NL + "" + NL + "   RXIDLE_status = (uint32_t)\\" + NL + "                 RD_REG(UartRegs->PSR_ASCMode,USIC_CH_PSR_ASCMode_RXIDLE_Msk, \\" + NL + "\t                       USIC_CH_PSR_ASCMode_RXIDLE_Pos);" + NL + "   if(( TXIDLE_status & RXIDLE_status) == 0x01U)" + NL + "    {" + NL + "      /* Disable UART mode before configuring all USIC registers to avoid unintended edges */ " + NL + "      UartRegs->CCR &= ~( ((uint32_t)(UART_MODE  & USIC_CH_CCR_MODE_Msk)));  " + NL + "\t  " + NL + "      /* Configuration of USIC Channel Fractional Divider */" + NL + "      UART001_lConfigureBaudRate(BaudRate,&Brg_Pdiv,&Fdr_Step);" + NL + "" + NL + "      /* Step value: 0x3FF */" + NL + "      UartRegs->FDR &= ~(USIC_CH_FDR_STEP_Msk);" + NL + "      UartRegs->FDR |= ( Fdr_Step & USIC_CH_FDR_STEP_Msk);" + NL + "              " + NL + "      /* The PreDivider for CTQ, PCTQ = 0  */" + NL + "      /* The Denominator for CTQ, DCTQ = 16 */" + NL + "" + NL + "      UartRegs->BRG &= ~(USIC_CH_BRG_PDIV_Msk);" + NL + "      UartRegs->BRG |= ((((uint32_t)Brg_Pdiv  << USIC_CH_BRG_PDIV_Pos) \\" + NL + "    \t\t                                          &  USIC_CH_BRG_PDIV_Msk));" + NL + "" + NL + "      /* Configure StopBit */" + NL + "      UartRegs->PCR_ASCMode &= ~(USIC_CH_PCR_ASCMode_STPB_Msk);" + NL + "      UartRegs->PCR_ASCMode |= \\" + NL + "                      (((uint32_t)Stopbit << USIC_CH_PCR_ASCMode_STPB_Pos) & \\" + NL + "                       USIC_CH_PCR_ASCMode_STPB_Msk);" + NL + "          " + NL + "      /* Configure Parity*/" + NL + "      UartRegs->CCR &= ~(USIC_CH_CCR_PM_Msk);" + NL + "      UartRegs->CCR |= (((UART_MODE  & USIC_CH_CCR_MODE_Msk)) | \\" + NL + "                        (((uint32_t)Parity  << USIC_CH_CCR_PM_Pos) & \\" + NL + "                                                       USIC_CH_CCR_PM_Msk));" + NL + "" + NL + "      Status = (status_t)DAVEApp_SUCCESS;" + NL + "    }" + NL + "    else" + NL + "    {" + NL + "      Status = (status_t)UART001_BUSY;" + NL + "      DBG002_ERROR(APP_GID,Status, 0, NULL);" + NL + "    }" + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "  " + NL + "  return Status;" + NL + "}" + NL + "/* This function reads out  the content of the USIC receive FIFO Buffer. " + NL + " * Returns true in case FIFO is not empty.else  otherwise." + NL + " *" + NL + " */" + NL + "" + NL + "uint32_t UART001_ReadDataMultiple\\" + NL + "            (const UART001_HandleType* Handle,uint16_t* DataPtr,uint32_t Count)" + NL + "{ " + NL + "  uint32_t ReadCount = 0x00U;" + NL + "  USIC_CH_TypeDef* UartRegs = Handle->UartRegs;  " + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + "  /* <<<DD_UART001_API_1>>>*/" + NL + "  while(! USIC_ubIsRxFIFOempty(UartRegs) && Count)" + NL + "  {" + NL + "    *DataPtr = (uint16_t)UartRegs->OUTR;" + NL + "    Count--;" + NL + "    ReadCount++;" + NL + "    DataPtr++;" + NL + "  }" + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "  " + NL + "  return ReadCount;" + NL + "}" + NL + "" + NL + "uint32_t UART001_WriteDataMultiple" + NL + "(" + NL + "  const UART001_HandleType* Handle," + NL + "  uint16_t* DataPtr," + NL + "  uint32_t Count" + NL + ")" + NL + "{" + NL + "  uint32_t WriteCount = 0x00U;" + NL + "  USIC_CH_TypeDef* UartRegs = Handle->UartRegs;" + NL + "  " + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + "  /* <<<DD_UART001_API_2>>>*/" + NL + "  while(! USIC_IsTxFIFOfull(UartRegs)&& Count)" + NL + "  {" + NL + "    UartRegs->IN[0] = *DataPtr;" + NL + "    Count--;" + NL + "    WriteCount++;" + NL + "    DataPtr++;" + NL + "  }  " + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "  " + NL + "  return WriteCount;" + NL + "}" + NL + "" + NL + "" + NL + "/* Checks the specified Flag status bit.*/" + NL + "" + NL + "status_t UART001_GetFlagStatus " + NL + "(" + NL + "  const UART001_HandleType* Handle," + NL + "  UART001_FlagStatusType Flag" + NL + ")" + NL + "{" + NL + "  status_t Status = (status_t)UART001_RESET;" + NL + "  uint32_t TempValue = 0x00U;" + NL + "  USIC_CH_TypeDef* UartRegs = Handle->UartRegs;" + NL + "  " + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + "  /* <<<DD_UART001_API_6>>>*/" + NL + "  if(Flag <= UART001_ALT_REC_IND_FLAG)" + NL + "  {" + NL + "    TempValue = UartRegs->PSR_ASCMode;" + NL + "    TempValue  &= ((uint32_t)0x01 << (uint32_t)Flag);    " + NL + "  }" + NL + "  else if(Flag <= UART001_FIFO_ALTRECV_BUF_FLAG)" + NL + "  {" + NL + "    TempValue = UartRegs->TRBSR;" + NL + "    TempValue  &= ((uint32_t)0x01 << \\" + NL + "                  ((uint32_t)Flag - (uint32_t)UART001_FIFO_STD_RECV_BUF_FLAG));" + NL + "    " + NL + "  }" + NL + "  else" + NL + "  {" + NL + "    TempValue = UartRegs->TRBSR;" + NL + "    TempValue  &= ((uint32_t)0x01 << \\" + NL + "       (((uint32_t)Flag - (uint32_t)UART001_FIFO_STD_RECV_BUF_FLAG) + 0x05U ));" + NL + "  } " + NL + "" + NL + "  if(TempValue != 0x00U)" + NL + "  {" + NL + "    Status = (status_t)UART001_SET;" + NL + "  }" + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "  return Status;" + NL + "}" + NL + "" + NL + "/* Clears the specified flag status.*/" + NL + "void UART001_ClearFlag" + NL + "(" + NL + "  const UART001_HandleType* Handle," + NL + "  UART001_FlagStatusType Flag" + NL + ")" + NL + "{" + NL + "" + NL + "  USIC_CH_TypeDef* UartRegs = Handle->UartRegs;" + NL + "  " + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,UART001_FUN_ENTRY);" + NL + "" + NL + "  /* <<<DD_UART001_API_7>>>*/" + NL + "  if(Flag <= UART001_ALT_REC_IND_FLAG)" + NL + "  {" + NL + "    UartRegs->PSCR  |= ((uint32_t)0x01 << (uint32_t)Flag);    " + NL + "  }" + NL + "  else if(Flag <= UART001_FIFO_ALTRECV_BUF_FLAG)" + NL + "  {" + NL + "    UartRegs->TRBSCR  |= ((uint32_t)0x01 << \\" + NL + "                 ((uint32_t)Flag - (uint32_t)UART001_FIFO_STD_RECV_BUF_FLAG)); " + NL + "  }" + NL + "  else" + NL + "  {" + NL + "    UartRegs->TRBSCR  |= ((uint32_t)0x01 << \\" + NL + "               (((uint32_t)Flag - (uint32_t)UART001_FIFO_STD_RECV_BUF_FLAG) + \\" + NL + "                                                       UART001_FLAG_OFFSET ));" + NL + "  }  " + NL + "  DBG002_FUNCTION_EXIT(APP_GID,UART001_FUN_EXIT);" + NL + "}" + NL + "" + NL + "" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_102 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
     String Baseuri = "app/uart001/";
    stringBuffer.append(TEXT_1);
    stringBuffer.append( app.getAppVersion(Baseuri));
    stringBuffer.append(TEXT_2);
     String TempApps = null;
   String MyAppName = null;
   ArrayList<String> apps;
   String TempLowerApps = null; 
   boolean DBGApp = false;   
   apps=(ArrayList<String>)(app.getApps());
        for (int k = 0; k < apps.size(); k++) {
              TempApps = apps.get(k);
//            if(app.isAppInitProvider(apps.get(k)) == true) {
              MyAppName = TempApps.substring(TempApps.indexOf("/app/") + 5, TempApps.lastIndexOf("/"));
              TempLowerApps = MyAppName.toLowerCase();
              if (TempLowerApps.equalsIgnoreCase("dbg002")) {DBGApp = true;}   
//   }  
  } 
    stringBuffer.append(TEXT_3);
     if (!DBGApp) { 
    stringBuffer.append(TEXT_4);
     } 
    stringBuffer.append(TEXT_5);
     String Uarturi = "peripheral/usic/"; 
     String MappedUri = null; 
     String UnitInst = null; 
     String appInst  = null; 
     double clockfreq = 0; 
     int Is44Device = -1; 
     int Is42Device = -1; 
     int Is45Device = -1; 
     int Is1xDevice = -1; 
     Is44Device = ((app.getSoftwareId().substring(0,2).compareTo("44")==0)?1:0); 
     Is42Device = ((app.getSoftwareId().substring(0,2).compareTo("42")==0)?1:0); 
     Is45Device = ((app.getSoftwareId().substring(0,2).compareTo("45")==0)?1:0); 
     Is1xDevice = ((app.getSoftwareId().substring(0,1).compareTo("1")==0)?1:0); 
    stringBuffer.append(TEXT_6);
     ArrayList<String> appsList7 = (ArrayList<String>)(app.getApps("app/uart001/"));
 for (String appIns : appsList7 ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(Baseuri + appInst + "/channel"); 
     if((MappedUri != null) && (MappedUri != "")) {  
     if(Is1xDevice == 1){
  clockfreq = app.getDoubleValue (Baseuri + appInst + "/clockapp/clk002_irMCLK" );
  }
  else if ((Is45Device==1)||(Is44Device==1)||(Is42Device==1)){
  clockfreq = app.getDoubleValue (Baseuri + appInst + "/clockapp/clk001_iroActualFreqPB" );
  }
  else{}
  
    stringBuffer.append(TEXT_7);
    stringBuffer.append( clockfreq);
    stringBuffer.append(TEXT_8);
    break;
     } 
     else { 
    stringBuffer.append(TEXT_9);
     } 
    } 
    stringBuffer.append(TEXT_10);
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/uart001/"));
 for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(Baseuri + appInst + "/channel"); 
     if((MappedUri != null) && (MappedUri != "")) { 
 UnitInst = MappedUri.substring(MappedUri .length()-11,MappedUri.indexOf("/channel/")); 
 int Unit = Integer.parseInt(UnitInst); 
     if(Unit == 0)  { 
    if ((Is44Device==1)||(Is42Device==1)||(Is1xDevice==1))
  {
    stringBuffer.append(TEXT_11);
    if ((Is1xDevice==1))  {
    stringBuffer.append(TEXT_12);
    }
    stringBuffer.append(TEXT_13);
    if ((Is1xDevice==1))    {
    stringBuffer.append(TEXT_14);
    }
    }
    if ((Is45Device==1)||(Is44Device==1)||(Is42Device==1))
  {
    stringBuffer.append(TEXT_15);
    stringBuffer.append(UnitInst);
    stringBuffer.append(TEXT_16);
    }
     } else { 
    if ((Is44Device==1)||(Is42Device==1)||(Is1xDevice==1))
  {
    stringBuffer.append(TEXT_17);
    if ((Is1xDevice==1))  {
    stringBuffer.append(TEXT_18);
    }
    stringBuffer.append(TEXT_19);
    if ((Is1xDevice==1)) {
    stringBuffer.append(TEXT_20);
    }
    }
    if ((Is45Device==1)||(Is44Device==1)||(Is42Device==1))
  {
    stringBuffer.append(TEXT_21);
    stringBuffer.append(UnitInst);
    stringBuffer.append(TEXT_22);
     } 
    stringBuffer.append(TEXT_23);
    }
    stringBuffer.append(TEXT_24);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_25);
     String pinUri = app.getMappedUri(Baseuri + appInst +"/uart_txpin"); 
     if ((pinUri != null) && (pinUri.trim() != "")) { 
     String portNo = pinUri.substring(pinUri.indexOf("port/p/")+7,pinUri.indexOf("/pad/")); 
     String pinNo = pinUri.substring(pinUri.indexOf("/pad/")+5,pinUri.length()); 
    stringBuffer.append(TEXT_26);
     int PDR_PD1 = app.getIntegerValue(Baseuri + appInst +"/uart_txpin/pdr_pd"); 
     int Pin = Integer.parseInt(pinNo);
     int Oper_Mode = app.getIntegerValue(Baseuri + appInst +"/uart001_OprModeTemp"); 
    if ((Oper_Mode == 1)) {
    stringBuffer.append(TEXT_27);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_28);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_29);
    if(Pin < 4) { 
    stringBuffer.append(TEXT_30);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_31);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_32);
    }else if (Pin >= 4 && Pin <= 7) {  
    Pin = Pin - 4; 
    stringBuffer.append(TEXT_33);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_34);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_35);
    } else if (Pin >= 8 && Pin <= 11) { 
    Pin = Pin - 8; 
    stringBuffer.append(TEXT_36);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_37);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_38);
    } else if (Pin >= 12 && Pin <= 15) { 
    Pin = Pin - 12; 
    stringBuffer.append(TEXT_39);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_40);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_41);
    }}
    stringBuffer.append(TEXT_42);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_43);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_44);
    if ((Is45Device==1)||(Is44Device==1)||(Is42Device==1))
  {
    stringBuffer.append(TEXT_45);
    stringBuffer.append(PDR_PD1);
    stringBuffer.append(TEXT_46);
     if(Pin < 8) {
    stringBuffer.append(TEXT_47);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_48);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_49);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_50);
     if(PDR_PD1 != 0) {
    stringBuffer.append(TEXT_51);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_52);
    stringBuffer.append(PDR_PD1);
    stringBuffer.append(TEXT_53);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_54);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_55);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_56);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_57);
     }
     } else {
    stringBuffer.append(TEXT_58);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_59);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_60);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_61);
     if(PDR_PD1 != 0) {
    stringBuffer.append(TEXT_62);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_63);
    stringBuffer.append(PDR_PD1);
    stringBuffer.append(TEXT_64);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_65);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_66);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_67);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_68);
     }
    } 
    stringBuffer.append(TEXT_69);
     }
    stringBuffer.append(TEXT_70);
    } else { 
    stringBuffer.append(TEXT_71);
    stringBuffer.append( appInst );
    stringBuffer.append(TEXT_72);
    } 
    stringBuffer.append(TEXT_73);
     String pinUri2 = app.getMappedUri(Baseuri + appInst +"/uart_rxpin"); 
     if ((pinUri2 != null) && (pinUri2.trim() != "")) { 
     String portNo2 = pinUri2.substring(pinUri2.indexOf("port/p/")+7,pinUri2.indexOf("/pad/")); 
     String pinNo2 = pinUri2.substring(pinUri.indexOf("/pad/")+5,pinUri2.length());
    stringBuffer.append(TEXT_74);
    stringBuffer.append(portNo2);
    stringBuffer.append(TEXT_75);
    stringBuffer.append(pinNo2);
    stringBuffer.append(TEXT_76);
     int Pin2 = Integer.parseInt(pinNo2);
     int IOCR_PCR = app.getIntegerValue(Baseuri + appInst +"/uart001_inputchardummy");
     if(Pin2 < 4) { 
     if(IOCR_PCR != 0) {
    stringBuffer.append(TEXT_77);
    stringBuffer.append(portNo2);
    stringBuffer.append(TEXT_78);
    stringBuffer.append(IOCR_PCR);
    stringBuffer.append(TEXT_79);
    stringBuffer.append((3+(Pin2*8)));
    stringBuffer.append(TEXT_80);
     }
    stringBuffer.append(TEXT_81);
    }else if (Pin2 >= 4 && Pin2 <= 7) {  
	Pin2 = Pin2 - 4; 
     if(IOCR_PCR != 0) {
    stringBuffer.append(TEXT_82);
    stringBuffer.append(portNo2);
    stringBuffer.append(TEXT_83);
    stringBuffer.append(IOCR_PCR);
    stringBuffer.append(TEXT_84);
    stringBuffer.append((3+(Pin2*8)));
    stringBuffer.append(TEXT_85);
     }
    stringBuffer.append(TEXT_86);
    } else if (Pin2 >= 8 && Pin2 <= 11) { 
	Pin2 = Pin2 - 8; 
     if(IOCR_PCR != 0) {
    stringBuffer.append(TEXT_87);
    stringBuffer.append(portNo2);
    stringBuffer.append(TEXT_88);
    stringBuffer.append(IOCR_PCR);
    stringBuffer.append(TEXT_89);
    stringBuffer.append((3+(Pin2*8)));
    stringBuffer.append(TEXT_90);
     }
    stringBuffer.append(TEXT_91);
    } else if (Pin2 >= 12 && Pin2 <= 15) { 
	Pin2 = Pin2 - 12; 
     if(IOCR_PCR != 0) {
    stringBuffer.append(TEXT_92);
    stringBuffer.append(portNo2);
    stringBuffer.append(TEXT_93);
    stringBuffer.append(IOCR_PCR);
    stringBuffer.append(TEXT_94);
    stringBuffer.append((3+(Pin2*8)));
    stringBuffer.append(TEXT_95);
     }
    stringBuffer.append(TEXT_96);
    }
    stringBuffer.append(TEXT_97);
    } else { 
    stringBuffer.append(TEXT_98);
    stringBuffer.append( appInst );
    stringBuffer.append(TEXT_99);
    } 
     } 
     else { 
    stringBuffer.append(TEXT_100);
     } 
    } 
    stringBuffer.append(TEXT_101);
    stringBuffer.append(TEXT_102);
    return stringBuffer.toString();
  }
}
