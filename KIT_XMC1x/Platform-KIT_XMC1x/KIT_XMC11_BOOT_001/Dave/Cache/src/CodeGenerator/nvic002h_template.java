package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class nvic002h_template
{
  protected static String nl;
  public static synchronized nvic002h_template create(String lineSeparator)
  {
    nl = lineSeparator;
    nvic002h_template result = new nvic002h_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + "/*CODE_BLOCK_BEGIN[NVIC002.h]*/";
  protected final String TEXT_2 = NL + "/**************************************************************************//**" + NL + " *" + NL + " * Copyright (C) 2011 Infineon Technologies AG. All rights reserved." + NL + " *" + NL + " * Infineon Technologies AG (Infineon) is supplying this software for use with " + NL + " * Infineon's microcontrollers.  " + NL + " * This file can be freely distributed within development tools that are " + NL + " * supporting such microcontrollers. " + NL + " *" + NL + " * THIS SOFTWARE IS PROVIDED \"AS IS\".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED" + NL + " * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF" + NL + " * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE." + NL + " * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, " + NL + " * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER." + NL + " *" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : February 18, 2013                                      **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                       Author(s) Identity                                   **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** Initials     Name                                                          ** " + NL + "** ---------------------------------------------------------------------------**" + NL + "** SSS          App Developer                                                 **" + NL + "*******************************************************************************/" + NL + "/**" + NL + " * @file NVIC002.h" + NL + " *" + NL + " * @App    Version NVIC002 <";
  protected final String TEXT_3 = ">" + NL + " * " + NL + " * @brief  Header file for NVIC SRGeneral (NVIC002) App." + NL + " *" + NL + " */" + NL + " /* Revision History" + NL + "  * 18  Feb 2013   v1.0.12  Comments are added." + NL + "  */" + NL + "" + NL + "#ifndef NVIC002_H_" + NL + "#define NVIC002_H_" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Include Files                                        **" + NL + "******************************************************************************/" + NL + "#include <DAVE3.h>" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Global Macro Definitions                             **" + NL + "******************************************************************************/" + NL + "" + NL + "/******************************************************************************" + NL + "**                      Global Type Definitions                              **" + NL + "******************************************************************************/" + NL + "/**" + NL + " * @ingroup NVIC002_publicparam" + NL + " * @{" + NL + " */" + NL + "" + NL + "/**" + NL + " * Mapping of User defined functions to Interrupt Handlers." + NL + " */";
  protected final String TEXT_4 = NL;
  protected final String TEXT_5 = "   " + NL + "" + NL + "#define ";
  protected final String TEXT_6 = "         IRQ_Hdlr_";
  protected final String TEXT_7 = " /* User defined function mapped to IRQ_Hdlr_";
  protected final String TEXT_8 = " */" + NL;
  protected final String TEXT_9 = NL + NL + NL + "/**" + NL + " * Structure which holds the UI configuration mapped for the App" + NL + " *        instance." + NL + " *  Note: Sub-Priority is not available for TIMM Devices" + NL + " */" + NL + "" + NL + "typedef struct NVIC002_HandleType" + NL + "{" + NL + "  /** Mapped NVIC Node */" + NL + "  uint8_t NodeID;     " + NL + "  /**  Node Interrupt Priority */" + NL + "  uint8_t Priority;    " + NL + "  /**  Node Interrupt SubPriority */" + NL + "  uint8_t SubPriority;  " + NL + "}NVIC002_HandleType;" + NL + "" + NL + "/**" + NL + " * Structure which holds NVIC002 Status Codes" + NL + " */" + NL + "typedef enum NVIC002_StatusType {" + NL + "  /*  " + NL + "  MODULENAME = NVIC002" + NL + "  */" + NL + "" + NL + "  /*" + NL + "  ERRCODESTRING = NVIC002_FUNC_ENTRY" + NL + "  STRCODESTRING = Entered Function %s" + NL + "  */" + NL + "  NVIC002_FUNC_ENTRY = 1," + NL + "  /**" + NL + "   * Exit specific function" + NL + "   */" + NL + "" + NL + "    /*" + NL + "  ERRCODESTRING = NVIC002_FUNC_EXIT" + NL + "  STRCODESTRING = Exited Function %s" + NL + "  */" + NL + "  NVIC002_FUNC_EXIT" + NL + "  /*" + NL + "  ERRORCODEEND" + NL + "  */" + NL + "" + NL + "}NVIC002_StatusType;" + NL + "" + NL + "/**" + NL + " * @}" + NL + " */" + NL + "/*******************************************************************************" + NL + "**                      Global Constant Declarations                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Extern Variables                                      **" + NL + "*******************************************************************************/" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "** FUNCTION PROTOTYPES                                                        **" + NL + "*******************************************************************************/" + NL + "" + NL + "/**" + NL + " * @ingroup NVIC002_apidoc" + NL + " * @{" + NL + " */" + NL + "" + NL + "/**" + NL + " * Function to configure and initialize  the NVIC002 App instances" + NL + " *" + NL + " *" + NL + " * @param[in] None" + NL + " *" + NL + " * @return     void" + NL + " *" + NL + " * <BR><P ALIGN=\"LEFT\"><B>Example:</B>" + NL + " * @code" + NL + " *  #include <DAVE3.h>" + NL + " *" + NL + " *  int main(void)" + NL + " *  {" + NL + " *    DAVE_Init(); // NVIC002_Init() is called within DAVE_Init()" + NL + " *    return 0;" + NL + " *  }" + NL + " * @endcode<BR> </p>" + NL + " *" + NL + " */" + NL + "void  NVIC002_Init(void);" + NL + "" + NL + "/**" + NL + " * Function to enable the IRQ" + NL + " *" + NL + " * @param[in]  Handle Instance Handle" + NL + " *" + NL + " * @return     void" + NL + " *" + NL + " * <BR><P ALIGN=\"LEFT\"><B>Example:</B>" + NL + " * @code" + NL + " *  #include <DAVE3.h>" + NL + " *" + NL + " *  int main(void)" + NL + " *  {" + NL + " *    DAVE_Init(); // NVIC002_Init() is called within DAVE_Init()" + NL + " *    NVIC002_EnableIRQ(&NVIC002_Handle0);" + NL + " *    return 0;" + NL + " *  }" + NL + " * @endcode<BR> </p>" + NL + " */" + NL + "void NVIC002_EnableIRQ(const NVIC002_HandleType* Handle);" + NL + "" + NL + "/**" + NL + " * Function to disable the IRQ" + NL + " *" + NL + " * @param[in]  Handle Instance Handle" + NL + " *" + NL + " * @return     void" + NL + " * <BR><P ALIGN=\"LEFT\"><B>Example:</B>" + NL + " * @code" + NL + " * #include <DAVE3.h>" + NL + " *" + NL + " *  int main(void)" + NL + " *  {" + NL + " *    DAVE_Init(); // NVIC002_Init() is called within DAVE_Init()" + NL + " *    NVIC002_DisableIRQ(&NVIC002_Handle0);" + NL + " *    return 0;" + NL + " *  }" + NL + " * @endcode<BR> </p>" + NL + " */" + NL + "void NVIC002_DisableIRQ(const NVIC002_HandleType* Handle);" + NL + "" + NL + "/**" + NL + " *@}" + NL + " */" + NL + "" + NL + "/* Inclusion of App config file */" + NL + "#include \"NVIC002_Conf.h\"" + NL + "" + NL + "#endif /* NVIC002_H_ */" + NL + "/*CODE_BLOCK_END*/" + NL;
  protected final String TEXT_10 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
    stringBuffer.append(TEXT_1);
    String AppBaseuri = "app/nvic002/";
  String MappedUri = null;
  String NodeID = null;
  String UserFunc = null;
 
    stringBuffer.append(TEXT_2);
    stringBuffer.append( app.getAppVersion(AppBaseuri));
    stringBuffer.append(TEXT_3);
     String appInst  = null; 
    stringBuffer.append(TEXT_4);
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/nvic002/"));
 for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/nvicnode"); 
     if((MappedUri != null) && (MappedUri != "")) { 
     NodeID = MappedUri.substring(MappedUri.lastIndexOf('/')+ 1 );
int Offset = Integer.parseInt(NodeID);
UserFunc = app.getStringValue(AppBaseuri + appInst +"/NVIC002_srwUserFunction"); 
if((UserFunc != null) && (UserFunc != "")) { 
    stringBuffer.append(TEXT_5);
    stringBuffer.append(UserFunc);
    stringBuffer.append(TEXT_6);
    stringBuffer.append(Offset);
    stringBuffer.append(TEXT_7);
    stringBuffer.append(Offset);
    stringBuffer.append(TEXT_8);
     }}} 
    stringBuffer.append(TEXT_9);
    stringBuffer.append(TEXT_10);
    return stringBuffer.toString();
  }
}
