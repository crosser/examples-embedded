package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class nvic002_confh_template
{
  protected static String nl;
  public static synchronized nvic002_confh_template create(String lineSeparator)
  {
    nl = lineSeparator;
    nvic002_confh_template result = new nvic002_confh_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = "/*CODE_BLOCK_BEGIN[NVIC002_Conf.h]*/" + NL + "/**************************************************************************//**" + NL + " *" + NL + " * Copyright (C) 2011 Infineon Technologies AG. All rights reserved." + NL + " *" + NL + " * Infineon Technologies AG (Infineon) is supplying this software for use with " + NL + " * Infineon's microcontrollers.  " + NL + " * This file can be freely distributed within development tools that are " + NL + " * supporting such microcontrollers. " + NL + " *" + NL + " * THIS SOFTWARE IS PROVIDED \"AS IS\".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED" + NL + " * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF" + NL + " * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE." + NL + " * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, " + NL + " * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER." + NL + " *" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000/XMC1000 Series   \t\t\t                  **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : February 18, 2013                                      **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                       Author(s) Identity                                   **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** Initials     Name                                                          **" + NL + "** ---------------------------------------------------------------------------**" + NL + "** SSS        App Developer                                                 **" + NL + "*******************************************************************************/" + NL + "" + NL + "/**" + NL + " * @file   NVIC002_Conf.h" + NL + " *" + NL + " * @App    Version NVIC002 <";
  protected final String TEXT_2 = ">" + NL + " *" + NL + " * @brief  Configuration file generated based on UI settings " + NL + " *         of NVIC002 App" + NL + " *" + NL + " */" + NL + "/* Revision History\t" + NL + " * 18  Feb 2013   v1.0.12 " + NL + " */" + NL + "#ifndef _CONF_NVIC002_H_" + NL + "#define _CONF_NVIC002_H_" + NL + "" + NL + "/****************************************************************************" + NL + "@Defines" + NL + "****************************************************************************/" + NL + "" + NL + "#include <DAVE3.h>" + NL;
  protected final String TEXT_3 = NL;
  protected final String TEXT_4 = NL + "extern const NVIC002_HandleType NVIC002_Handle";
  protected final String TEXT_5 = ";";
  protected final String TEXT_6 = NL + "/* NVIC NODE NOT MAPPED FOR APP INSTANCE ";
  protected final String TEXT_7 = " */";
  protected final String TEXT_8 = " " + NL + "" + NL + "" + NL + "#endif  /* ifndef _CONF_NVIC002_H_ */" + NL + "" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_9 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
     String AppBaseuri = "app/nvic002/";
    stringBuffer.append(TEXT_1);
    stringBuffer.append( app.getAppVersion(AppBaseuri));
    stringBuffer.append(TEXT_2);
     String MappedUri = null; 
     String appInst  = null; 
    stringBuffer.append(TEXT_3);
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/nvic002/"));
 for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/nvicnode"); 
     if((MappedUri != null) && (MappedUri != "")) { 
    stringBuffer.append(TEXT_4);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_5);
     } 
     else { 
    stringBuffer.append(TEXT_6);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_7);
     } 
    } 
    stringBuffer.append(TEXT_8);
    stringBuffer.append(TEXT_9);
    return stringBuffer.toString();
  }
}
