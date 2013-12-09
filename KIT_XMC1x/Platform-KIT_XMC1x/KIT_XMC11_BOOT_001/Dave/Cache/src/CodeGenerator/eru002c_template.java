package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class eru002c_template
{
  protected static String nl;
  public static synchronized eru002c_template create(String lineSeparator)
  {
    nl = lineSeparator;
    eru002c_template result = new eru002c_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + NL + "/*CODE_BLOCK_BEGIN[ERU002.c]*/" + NL + "/*******************************************************************************" + NL + " Copyright (c) 2011, Infineon Technologies AG                                 **" + NL + " All rights reserved.                                                         **" + NL + "                                                                              **" + NL + " Redistribution and use in source and binary forms, with or without           **" + NL + " modification,are permitted provided that the following conditions are met:   **" + NL + "                                                                              **" + NL + " *Redistributions of source code must retain the above copyright notice,      **" + NL + " this list of conditions and the following disclaimer.                        **" + NL + " *Redistributions in binary form must reproduce the above copyright notice,   **" + NL + " this list of conditions and the following disclaimer in the documentation    **" + NL + " and/or other materials provided with the distribution.                       **" + NL + " *Neither the name of the copyright holders nor the names of its contributors **" + NL + " may be used to endorse or promote products derived from this software without** " + NL + " specific prior written permission.                                           **" + NL + "                                                                              **" + NL + " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"  **" + NL + " AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **" + NL + " IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **" + NL + " ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **" + NL + " LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **" + NL + " CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **" + NL + " SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **" + NL + " INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **" + NL + " CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **" + NL + " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **" + NL + " POSSIBILITY OF SUCH DAMAGE.                                                  **" + NL + "                                                                              **" + NL + " To improve the quality of the software, users are encouraged to share        **" + NL + " modifications, enhancements or bug fixes with Infineon Technologies AG       **" + NL + " dave@infineon.com).                                                          **" + NL + "                                                                              **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000 Series/XMC1000 series                          **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : Mar 14, 2013                                             **" + NL + "**                                                                            **" + NL + "*******************************************************************************/" + NL + "/*******************************************************************************" + NL + "**                      Author(s) Identity                                    **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** Initials     Name                                                          **" + NL + "** ---------------------------------------------------------------------------**" + NL + "** NPJ        App Developer                                                   **" + NL + "*******************************************************************************/";
  protected final String TEXT_2 = NL + "/**" + NL + " * @file   ERU002.c" + NL + " *" + NL + " * Revision History" + NL + " * 25 Jan 2013 v1.0.4 Initial Version" + NL + " * 14 Mar 2013 v1.0.6 Porting to XMC42xx and XMC44xx" + NL + " *" + NL + " * @brief  ERU002 App Implementation" + NL + " *" + NL + " */" + NL + "/*******************************************************************************" + NL + " ** INCLUDE FILES                                                             **" + NL + " ******************************************************************************/" + NL + "" + NL + "/** Inclusion of header file */" + NL + "#include <DAVE3.h>" + NL;
  protected final String TEXT_3 = " " + NL + "\t ";
  protected final String TEXT_4 = "  " + NL + "/*****************************************************************************" + NL + "              DUMMY DEFINTIONS OF DEBUG LOG MACROS" + NL + "*****************************************************************************/" + NL + "/*These definitions are included here to avoid compilation errors," + NL + " since the DBG002 app is not part of the project. All the macros are defined" + NL + " as empty*/ " + NL + "#ifndef _DBG002_H_" + NL + "" + NL + "#define DBG002_RegisterCallBack(A,B,C)" + NL + "#define DBG002_I(e) " + NL + "#define DBG002_IG(e,g) " + NL + "#define DBG002_IH(e,h) " + NL + "#define DBG002_IP(e,p) " + NL + "#define DBG002_IGH(e,g,h) " + NL + "#define DBG002_IGP(e,g,p) " + NL + "#define DBG002_IHP(e,h,p) " + NL + "#define DBG002_IGHP(e,g,h,p) " + NL + "#define DBG002_N(e) " + NL + "#define DBG002_NG(e,g) " + NL + "#define DBG002_NH(e,h) " + NL + "#define DBG002_NP(e,p) " + NL + "#define DBG002_NGH(e,g,h) " + NL + "#define DBG002_NGP(e,g,p) " + NL + "#define DBG002_NHP(e,h,p) " + NL + "#define DBG002_NGHP(e,g,h,p) " + NL + "#define DBG002_ID(e) " + NL + "#define DBG002_IS(e) " + NL + "#define DBG002_ISG(e,g) " + NL + "#define DBG002_SAFETY_CRITICAL(groupid,messageid,length,value)" + NL + "#define DBG002_CRITICAL(groupid,messageid,length,value)" + NL + "#define DBG002_ERROR(groupid,messageid,length,value)" + NL + "#define DBG002_WARNING(groupid,messageid,length,value)" + NL + "#define DBG002_INFO(groupid,messageid,length,value)" + NL + "#define DBG002_TRACE(groupid,messageid,length,value)" + NL + "#define DBG002_FUNCTION_ENTRY(GID, Status) " + NL + "#define DBG002_FUNCTION_EXIT(GID, Status) " + NL + "" + NL + "#endif/* End of defintions of dummy Debug Log macros*/" + NL + "\t";
  protected final String TEXT_5 = "     " + NL + "" + NL + "#undef APP_GID" + NL + "#define APP_GID DBG002_GID_ERU001\t" + NL + NL;
  protected final String TEXT_6 = NL;
  protected final String TEXT_7 = NL;
  protected final String TEXT_8 = NL;
  protected final String TEXT_9 = NL;
  protected final String TEXT_10 = NL;
  protected final String TEXT_11 = "\t" + NL + "\t" + NL + "\t" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Macro Definitions                             **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "#define ERU_INVALID_INPUT     0x0000000FU" + NL + "#define ERU_INPUT_LEVEL_SET   0x00000001U" + NL + "#define ERU_OGU_Y_MAX          (uint8_t)3" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Type Definitions                              **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                 Private Function Declarations:" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Global Constant Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Global Variable Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Constant Definitions                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                 Function like macro definitions                            **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Function Definitions                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Public Function Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "/** @addtogroup ERU002_app Func" + NL + " * @{" + NL + " */" + NL + "" + NL + "void ERU002_Init(void)" + NL + "{" + NL + " " + NL + "    DBG002_FUNCTION_ENTRY(APP_GID,ERU002_FUNCTION_ENTRY);" + NL + "  " + NL + "  /* <<<DD_ERU001_API_1>>> */" + NL + "  /* Configure the register as per user configuration */" + NL;
  protected final String TEXT_12 = NL + "  /* Reset the ERU Unit 1*/" + NL + "  if(RESET001_GetStatus(PER0_ERU1) == 1)" + NL + "  {" + NL + "    /* De-assert the module */" + NL + "    RESET001_DeassertReset(PER0_ERU1);" + NL + "  }";
  protected final String TEXT_13 = NL + "   /* Deassert the clock gating under SCU module to enable the WDT peripheral" + NL + "  */" + NL + "  " + NL + "  WR_REG(SCU_CLK->CGATCLR0, SCU_CLK_CGATCLR0_ERU1_Msk, SCU_CLK_CGATCLR0_ERU1_Pos, 1U);";
  protected final String TEXT_14 = "  " + NL + "  ERU002_Handle";
  protected final String TEXT_15 = ".ERURegs->EXOCON[ERU002_Handle";
  protected final String TEXT_16 = ".OutputChannel] |=  (((uint32_t)((uint32_t)";
  protected final String TEXT_17 = "  << ERU_EXOCON_GP_Pos) & \\" + NL + "\tERU_EXOCON_GP_Msk) | \\" + NL + "\t((uint32_t)(";
  protected final String TEXT_18 = "  << ERU_EXOCON_GEEN_Pos) & \\" + NL + "\t\t\tERU_EXOCON_GEEN_Msk));\t  ";
  protected final String TEXT_19 = NL + "/* OUTPUT CHANNEL IS NOT MAPPED */";
  protected final String TEXT_20 = NL;
  protected final String TEXT_21 = NL + "\t\t\t\t\t\t\t\t " + NL + " " + NL + "    DBG002_FUNCTION_EXIT(APP_GID,ERU002_FUNCTION_EXIT);" + NL + "  " + NL + "}" + NL + "" + NL + "" + NL + "\t" + NL + "/*  Function to Select peripheral trigger input Source " + NL + " *  ERU_OGU_y = SIGNAL_ERU_OGU_y3 for signal 1" + NL + " *  ERU_OGU_y = SIGNAL_ERU_OGU_y1 for signal 0" + NL + " */" + NL + "" + NL + "uint32_t  ERU002_SetPeripheralTrigInputSrc(const ERU002_HandleType *handle, uint8_t ERU_OGU_y)" + NL + "{" + NL + "\t " + NL + "\tuint32_t status = 0;" + NL + "\tERU_GLOBAL_TypeDef *ERURegs = handle->ERURegs;" + NL + "\t/* Check the OGU_y value */" + NL + "\tif( ( ERU_OGU_y <= ERU_OGU_Y_MAX ) && ( ERURegs != NULL) )" + NL + "\t{" + NL + "\t\t/* ERUx_EXOCON[y]_ISS x =0 and 1, y = 0, 1, 2 and 3 */" + NL + "\t\tWR_REG(ERURegs->EXOCON[handle->OutputChannel], ERU_EXOCON_ISS_Msk, ERU_EXOCON_ISS_Pos, ERU_OGU_y);" + NL + "\t\tstatus = ERU_INPUT_LEVEL_SET;" + NL + "\t}" + NL + "\telse" + NL + "\t{" + NL + "\t\tstatus = ERU_INVALID_INPUT;" + NL + "\t}" + NL + "\treturn status;" + NL + "\t" + NL + "}" + NL + "" + NL + "\t" + NL + "" + NL + "/**" + NL + " *@}" + NL + " */" + NL + "" + NL + "" + NL + "" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_22 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
    stringBuffer.append(TEXT_1);
     String AppBaseuri = "app/eru002/";
    stringBuffer.append(TEXT_2);
     boolean DBGApp = false; 
    stringBuffer.append(TEXT_3);
     if (!DBGApp) { 
    stringBuffer.append(TEXT_4);
     } 
    stringBuffer.append(TEXT_5);
     int Is44Device = -1; 
    stringBuffer.append(TEXT_6);
     int Is42Device = -1; 
    stringBuffer.append(TEXT_7);
     int Is45Device = -1; 
    stringBuffer.append(TEXT_8);
     Is45Device = ((app.getSoftwareId().substring(0,2).compareTo("45")==0)?1:0); 
    stringBuffer.append(TEXT_9);
     Is44Device = ((app.getSoftwareId().substring(0,2).compareTo("44")==0)?1:0); 
    stringBuffer.append(TEXT_10);
     Is42Device = ((app.getSoftwareId().substring(0,2).compareTo("42")==0)?1:0); 
    stringBuffer.append(TEXT_11);
     String ERUuri = "http://www.infineon.com/0.1.28/peripheral/eru/"; 
     String MappedUri = null; 
     String appInst  = null; 
     String UnitInst = null; 
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/eru002/"));
 for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/ogu"); 
     if((MappedUri != null) && (MappedUri != "")) {  
     UnitInst = MappedUri.substring(ERUuri.length(),MappedUri.indexOf("/ogu/")); 
     int Unit = Integer.parseInt(UnitInst);
    if(Unit == 1) {
    stringBuffer.append(TEXT_12);
    if ((Is44Device==1)||(Is42Device==1))
  {
    stringBuffer.append(TEXT_13);
    }
    }
    stringBuffer.append(TEXT_14);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_15);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_16);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst + "/ogu/exocon/gp") );
    stringBuffer.append(TEXT_17);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst + "/ogu/exocon/geen") );
    stringBuffer.append(TEXT_18);
     } 
     else { 
    stringBuffer.append(TEXT_19);
     } 
    stringBuffer.append(TEXT_20);
    } 
    stringBuffer.append(TEXT_21);
    stringBuffer.append(TEXT_22);
    return stringBuffer.toString();
  }
}
