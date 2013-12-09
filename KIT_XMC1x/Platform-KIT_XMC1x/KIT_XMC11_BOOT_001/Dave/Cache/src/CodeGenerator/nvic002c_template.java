package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class nvic002c_template
{
  protected static String nl;
  public static synchronized nvic002c_template create(String lineSeparator)
  {
    nl = lineSeparator;
    nvic002c_template result = new nvic002c_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + "/*CODE_BLOCK_BEGIN[NVIC002.c]*/";
  protected final String TEXT_2 = NL + NL + "/*******************************************************************************" + NL + " Copyright (c) 2011, Infineon Technologies AG                                 **" + NL + " All rights reserved.                                                         **" + NL + "                                                                              **" + NL + " Redistribution and use in source and binary forms, with or without           **" + NL + " modification,are permitted provided that the following conditions are met:   **" + NL + "                                                                              **" + NL + " *Redistributions of source code must retain the above copyright notice,      **" + NL + " this list of conditions and the following disclaimer.                        **" + NL + " *Redistributions in binary form must reproduce the above copyright notice,   **" + NL + " this list of conditions and the following disclaimer in the documentation    **" + NL + " and/or other materials provided with the distribution.                       **" + NL + " *Neither the name of the copyright holders nor the names of its contributors **" + NL + " may be used to endorse or promote products derived from this software without** " + NL + " specific prior written permission.                                           **" + NL + "                                                                              **" + NL + " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"  **" + NL + " AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **" + NL + " IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **" + NL + " ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **" + NL + " LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **" + NL + " CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **" + NL + " SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **" + NL + " INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **" + NL + " CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **" + NL + " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **" + NL + " POSSIBILITY OF SUCH DAMAGE.                                                  **" + NL + "                                                                              **" + NL + " To improve the quality of the software, users are encouraged to share        **" + NL + " modifications, enhancements or bug fixes with Infineon Technologies AG       **" + NL + " dave@infineon.com).                                                          **" + NL + "                                                                              **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000/XMC1000 Series   \t\t\t                  **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : March 25 , 2013                                        **" + NL + "**                                                                            **" + NL + "*******************************************************************************/" + NL + "/**" + NL + " * @file   NVIC002.c" + NL + " *" + NL + " * @App    Version NVIC002 <";
  protected final String TEXT_3 = ">" + NL + " *" + NL + " * @brief  NVIC_Empty_Handler_NVIC002 App" + NL + " *         " + NL + " *  NVIC002 App is used by top level Apps when a user defined interrupt handler " + NL + " *  needs to be reassigned to the actual mapped interrupt node" + NL + " *\t(based on App connectivity)." + NL + " *" + NL + " *\tThe use case is as follows: " + NL + " *\tInterrupt handler has to be provided by the user and function name is defined" + NL + " *  by user in the App GUI. " + NL + " *" + NL + " *\tNVIC002 App creates a header file (NVIC002.h) with a #define to reassign the" + NL + " *  interrupt function name defined by the user to the fixed name based on the" + NL + " *\tnode number." + NL + " *\tNote: " + NL + " *\tPreemption priority for NVIC  interrupt is fixed to 64." + NL + " *\tThe App GUI provides lowest priority level as default value.      " + NL + " *\tIt is also possible for top level App to be self-contained(by consuming NVIC" + NL + " *  node directly instead of requiring an NVIC App for defining the interrupt" + NL + " *  handler.)" + NL + " *" + NL + " */" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Author(s) Identity                                    **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** Initials     Name                                                          **" + NL + "** ---------------------------------------------------------------------------**" + NL + "** AKW      App Developer                                                   **" + NL + "*******************************************************************************/" + NL + "/* Revision History\t" + NL + " * 18-Feb-13 V1.0.12  1. Porting to XMC1000 Devices." + NL + " *                    2. Conditional Codes are added to support both XMC1000 " + NL + " *                    and XMC4000 devices." + NL + " *                    3. Debug related dummy Macros are added. " + NL + " * 25-Mar-13 V1.0.14  1. Interrupt mapping bug fixing. " + NL + " *                    2. Removed Array of irq_numbers. " + NL + " */" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + " ** INCLUDE FILES                                                             **" + NL + " ******************************************************************************/" + NL + "/* Inclusion of header file */" + NL + "#include <DAVE3.h>" + NL;
  protected final String TEXT_4 = NL;
  protected final String TEXT_5 = "  " + NL + "/*****************************************************************************" + NL + "              DUMMY DEFINTIONS OF DEBUG LOG MACROS" + NL + "*****************************************************************************/" + NL + "/*These definitions are included here to avoid compilation errors," + NL + " since the DBG002 app is not part of the project. All the macros are defined" + NL + " as empty*/ " + NL + "#ifndef _DBG002_H_" + NL + "" + NL + "#define DBG002_RegisterCallBack(A,B,C)" + NL + "#define DBG002_I(e) " + NL + "#define DBG002_IG(e,g) " + NL + "#define DBG002_IH(e,h) " + NL + "#define DBG002_IP(e,p) " + NL + "#define DBG002_IGH(e,g,h) " + NL + "#define DBG002_IGP(e,g,p) " + NL + "#define DBG002_IHP(e,h,p) " + NL + "#define DBG002_IGHP(e,g,h,p) " + NL + "#define DBG002_N(e) " + NL + "#define DBG002_NG(e,g) " + NL + "#define DBG002_NH(e,h) " + NL + "#define DBG002_NP(e,p) " + NL + "#define DBG002_NGH(e,g,h) " + NL + "#define DBG002_NGP(e,g,p) " + NL + "#define DBG002_NHP(e,h,p) " + NL + "#define DBG002_NGHP(e,g,h,p) " + NL + "#define DBG002_ID(e) " + NL + "#define DBG002_IS(e) " + NL + "#define DBG002_ISG(e,g) " + NL + "#define DBG002_SAFETY_CRITICAL(groupid,messageid,length,value)" + NL + "#define DBG002_CRITICAL(groupid,messageid,length,value)" + NL + "#define DBG002_ERROR(groupid,messageid,length,value)" + NL + "#define DBG002_WARNING(groupid,messageid,length,value)" + NL + "#define DBG002_INFO(groupid,messageid,length,value)" + NL + "#define DBG002_TRACE(groupid,messageid,length,value)" + NL + "#define DBG002_FUNCTION_ENTRY(GID, Status) " + NL + "#define DBG002_FUNCTION_EXIT(GID, Status) " + NL + "" + NL + "#endif/* End of defintions of dummy Debug Log macros*/";
  protected final String TEXT_6 = "                  " + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Macro Definitions                             **" + NL + "*******************************************************************************/" + NL;
  protected final String TEXT_7 = NL + "/*******************************************************************************" + NL + "**                      Private Type Definitions                              **" + NL + "*******************************************************************************/" + NL + "#define APP_GID DBG002_GID_NVIC002" + NL + "/*******************************************************************************" + NL + "**                 Private Function Declarations:" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Global Constant Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Global Variable Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Constant Definitions                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                 Function like macro definitions                            **" + NL + "*******************************************************************************/" + NL + "/*******************************************************************************" + NL + "**                      Private Function Definitions                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Public Function Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "/**  Function to initialize the NVIC node parameters based on " + NL + " *  UI configuration." + NL + " */" + NL + "void NVIC002_Init(void)" + NL + "{" + NL + "  /*<<<DD_NVIC002_API_1>>>*/  " + NL + "   DBG002_FUNCTION_ENTRY(APP_GID,NVIC002_FUNC_ENTRY);\t";
  protected final String TEXT_8 = NL + "  /* Set Interrupt Priority for NVIC ";
  protected final String TEXT_9 = " Node App Instance ";
  protected final String TEXT_10 = "  */";
  protected final String TEXT_11 = NL + "   NVIC_SetPriority((IRQn_Type)";
  protected final String TEXT_12 = ", ";
  protected final String TEXT_13 = ");";
  protected final String TEXT_14 = NL + "   NVIC_SetPriority((IRQn_Type)";
  protected final String TEXT_15 = ", NVIC_EncodePriority(NVIC_GetPriorityGrouping(),";
  protected final String TEXT_16 = ",";
  protected final String TEXT_17 = "));";
  protected final String TEXT_18 = "   " + NL + "  /* Enable Interrupt */" + NL + "   NVIC_EnableIRQ((IRQn_Type)";
  protected final String TEXT_19 = ");";
  protected final String TEXT_20 = NL + "   DBG002_FUNCTION_EXIT(APP_GID,NVIC002_FUNC_EXIT);" + NL + "}" + NL + "" + NL + "/**  Function to enable Interrupt" + NL + " * " + NL + " */" + NL + "void NVIC002_EnableIRQ(const NVIC002_HandleType* Handle)" + NL + "{" + NL + "  /*<<<DD_NVIC002_API_2>>>*/" + NL + "   DBG002_FUNCTION_ENTRY(APP_GID,NVIC002_FUNC_ENTRY);" + NL + "  /* Enable Interrupt */" + NL + "   NVIC_EnableIRQ((IRQn_Type)Handle->NodeID);" + NL + "   DBG002_FUNCTION_EXIT(APP_GID,NVIC002_FUNC_EXIT);" + NL + "\t" + NL + "}" + NL + "" + NL + "/**  Function to disable Interrupt" + NL + " * " + NL + " */" + NL + "void NVIC002_DisableIRQ(const NVIC002_HandleType* Handle)" + NL + "{" + NL + "  /*<<<DD_NVIC002_API_3>>>*/" + NL + "  DBG002_FUNCTION_ENTRY(APP_GID,NVIC002_FUNC_ENTRY);" + NL + "  /* Disable Interrupt */" + NL + "  NVIC_DisableIRQ((IRQn_Type)Handle->NodeID);" + NL + "  DBG002_FUNCTION_EXIT(APP_GID,NVIC002_FUNC_EXIT);" + NL + "}" + NL + "" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_21 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
    stringBuffer.append(TEXT_1);
     String AppBaseuri = "app/nvic002/";
     String MappedUri = null; 
     String NodeID = null; 
    stringBuffer.append(TEXT_2);
    stringBuffer.append( app.getAppVersion(AppBaseuri));
    stringBuffer.append(TEXT_3);
     String TempApps = null;
   String MyAppName = null;
   ArrayList<String> apps;
   String TempLowerApps = null; 
   boolean DBGApp = false;   
   apps=(ArrayList<String>)(app.getApps());
   for (int k = 0; k < apps.size(); k++) {
   TempApps = apps.get(k);
// if(app.isAppInitProvider(apps.get(k)) == true) {
   MyAppName = TempApps.substring(TempApps.indexOf("/app/") + 5, TempApps.lastIndexOf("/"));
  TempLowerApps = MyAppName.toLowerCase();
   if (TempLowerApps.equalsIgnoreCase("dbg002")) {DBGApp = true;}   
 //  }  
  } 
    stringBuffer.append(TEXT_4);
     if (!DBGApp) { 
    stringBuffer.append(TEXT_5);
     } 
    stringBuffer.append(TEXT_6);
     int IsTIMM1Device = -1; 
     IsTIMM1Device = ((app.getSoftwareId().substring(0,1).compareTo("1")==0)?1:0); 
    stringBuffer.append(TEXT_7);
     String appInst  = null; 
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/nvic002/"));
  for (String appIns : appsList ) {
  appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/nvicnode"); 
     if((MappedUri != null) && (MappedUri != "")) { 
     NodeID = MappedUri.substring(MappedUri.lastIndexOf('/')+ 1 );
  int Offset = Integer.parseInt(NodeID); 
  int Priority = 0;
  int SubPriority=0;
  if(IsTIMM1Device ==1)
  {
  Priority = app.getIntegerValue(AppBaseuri + appInst +"/NVIC002_TIMMirwInterruptPriority");
  }
  else
  {
  Priority = app.getIntegerValue(AppBaseuri + appInst +"/NVIC002_irwInterruptPriority");
  SubPriority = app.getIntegerValue(AppBaseuri + appInst +"/NVIC002_irwInterruptSubPriority");
  }
 
  int IntEnable = app.getIntegerValue(AppBaseuri + appInst +"/NVIC002_erwEnableInt/0");
    stringBuffer.append(TEXT_8);
    stringBuffer.append(NodeID);
    stringBuffer.append(TEXT_9);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_10);
     if(IsTIMM1Device ==1) 
    { 
    stringBuffer.append(TEXT_11);
    stringBuffer.append(NodeID);
    stringBuffer.append(TEXT_12);
    stringBuffer.append(Priority);
    stringBuffer.append(TEXT_13);
    } 
     else 
    { 
    stringBuffer.append(TEXT_14);
    stringBuffer.append(NodeID);
    stringBuffer.append(TEXT_15);
    stringBuffer.append(Priority);
    stringBuffer.append(TEXT_16);
    stringBuffer.append(SubPriority);
    stringBuffer.append(TEXT_17);
    } 
       if(IntEnable ==1) { 
    stringBuffer.append(TEXT_18);
    stringBuffer.append(NodeID);
    stringBuffer.append(TEXT_19);
     }}} 
    stringBuffer.append(TEXT_20);
    stringBuffer.append(TEXT_21);
    return stringBuffer.toString();
  }
}
