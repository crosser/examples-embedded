package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class io002_confh_template
{
  protected static String nl;
  public static synchronized io002_confh_template create(String lineSeparator)
  {
    nl = lineSeparator;
    io002_confh_template result = new io002_confh_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + "/*CODE_BLOCK_BEGIN[IO002_Conf.h]*/" + NL + "/**************************************************************************//**" + NL + " *" + NL + " * Copyright (C) 2011 Infineon Technologies AG. All rights reserved." + NL + " *" + NL + " * Infineon Technologies AG (Infineon) is supplying this software for use with " + NL + " * Infineon's microcontrollers.  " + NL + " * This file can be freely distributed within development tools that are " + NL + " * supporting such microcontrollers. " + NL + " *" + NL + " * THIS SOFTWARE IS PROVIDED \"AS IS\".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED" + NL + " * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF" + NL + " * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE." + NL + " * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, " + NL + " * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER." + NL + " *" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : Jan 1, 2013                                           **" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "*******************************************************************************/" + NL + "/**" + NL + " * @file   IO002_Conf.h" + NL + " *" + NL + " * @brief  Configuration file generated based on UI settings " + NL + " *         of IO002 App" + NL + " */" + NL + "/* Revision History " + NL + " * 1 Jan 2013 v1.0.12  Ported To XMC1000 Devices." + NL + " *" + NL + " */" + NL + "" + NL + "#ifndef _CONF_IO002_H_" + NL + "#define _CONF_IO002_H_" + NL + "" + NL + "/******************************************************************************" + NL + "@Defines" + NL + "******************************************************************************/" + NL + "" + NL + "#include <DAVE3.h>" + NL;
  protected final String TEXT_2 = NL;
  protected final String TEXT_3 = NL + "extern const IO002_HandleType IO002_Handle";
  protected final String TEXT_4 = ";" + NL;
  protected final String TEXT_5 = NL + "/* IO002 App instance (no.";
  protected final String TEXT_6 = ") is not mapped to any Port Pad. */";
  protected final String TEXT_7 = NL + NL + "#endif  /* ifndef _CONF_IO002_H_ */" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_8 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
    stringBuffer.append(TEXT_1);
     String P = "port/p/"; 
     String AppBaseuri = "app/io002/"; 
     String appInst  = null; 
    stringBuffer.append(TEXT_2);
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/io002/"));
 for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     String pinUri = app.getMappedUri(AppBaseuri + appInst +"/pin"); 
     if ((pinUri != null) && (pinUri.trim() != "")) { 
    stringBuffer.append(TEXT_3);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_4);
     } else { 
    stringBuffer.append(TEXT_5);
    stringBuffer.append( appInst );
    stringBuffer.append(TEXT_6);
     }} 
    stringBuffer.append(TEXT_7);
    stringBuffer.append(TEXT_8);
    return stringBuffer.toString();
  }
}
