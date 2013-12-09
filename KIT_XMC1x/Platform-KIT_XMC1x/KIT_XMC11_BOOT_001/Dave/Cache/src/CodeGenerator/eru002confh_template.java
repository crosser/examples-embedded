package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class eru002confh_template
{
  protected static String nl;
  public static synchronized eru002confh_template create(String lineSeparator)
  {
    nl = lineSeparator;
    eru002confh_template result = new eru002confh_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + "/*CODE_BLOCK_BEGIN[ERU002_Conf.h]*/" + NL + "/**************************************************************************//**" + NL + " *" + NL + " * Copyright (C) 2011 Infineon Technologies AG. All rights reserved." + NL + " *" + NL + " * Infineon Technologies AG (Infineon) is supplying this software for use with " + NL + " * Infineon's microcontrollers.  " + NL + " * This file can be freely distributed within development tools that are " + NL + " * supporting such microcontrollers. " + NL + " *" + NL + " * THIS SOFTWARE IS PROVIDED \"AS IS\".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED" + NL + " * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF" + NL + " * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE." + NL + " * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, " + NL + " * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER." + NL + " *" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000 Series/XMC1000 series                          **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "*******************************************************************************/";
  protected final String TEXT_2 = NL + "/**" + NL + " * @file   ERU002_Conf.h" + NL + " *" + NL + " * Revision History" + NL + " * 25 Jan 2013 v1.0.4 Initial Version" + NL + " *" + NL + " * @brief  Configuration file generated based on UI settings " + NL + " *         of ERU002 App" + NL + " *" + NL + " */" + NL + "#ifndef _CONF_ERU002_H_" + NL + "#define _CONF_ERU002_H_" + NL + "" + NL + "/*****************************************************************************" + NL + "** @Defines" + NL + "*****************************************************************************/" + NL + "" + NL + "#include <DAVE3.h>";
  protected final String TEXT_3 = NL;
  protected final String TEXT_4 = NL + "/*Base Address of mapped ERU Module for App Instance ";
  protected final String TEXT_5 = " */" + NL + "#define ERU001_";
  protected final String TEXT_6 = "_ERU\t  ERU";
  protected final String TEXT_7 = NL + "/* Mapped OGU instance  for App Instance ";
  protected final String TEXT_8 = " */" + NL + "#define ERU001_";
  protected final String TEXT_9 = "_OGU_Y   ";
  protected final String TEXT_10 = NL + "/* CHANNEL IS NOT MAPPED */";
  protected final String TEXT_11 = NL + "extern const ERU002_HandleType ERU002_Handle";
  protected final String TEXT_12 = ";";
  protected final String TEXT_13 = NL + "/* OGU NOT MAPPED FOR APP INSTANCE ";
  protected final String TEXT_14 = " */";
  protected final String TEXT_15 = " " + NL + "" + NL + "" + NL + "#endif  /* ifndef _CONF_ERU002_H_ */" + NL + "" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_16 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
    stringBuffer.append(TEXT_1);
     String AppBaseuri = "app/eru002/";
    stringBuffer.append(TEXT_2);
     String ERUuri = "http://www.infineon.com/0.1.28/peripheral/eru/"; 
     String MappedUri = null; 
     String appInst  = null; 
     String UnitInst = null; 
     String ChannelInst = null; 
    stringBuffer.append(TEXT_3);
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/eru002/")); 
      for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/ogu"); 
     if((MappedUri != null) && (MappedUri != "")) { 
     UnitInst = MappedUri.substring(ERUuri.length(),MappedUri.indexOf("/ogu/")); 
     ChannelInst = MappedUri.substring(MappedUri.length()-1); 
    stringBuffer.append(TEXT_4);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_5);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_6);
    stringBuffer.append(UnitInst);
    stringBuffer.append(TEXT_7);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_8);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_9);
    stringBuffer.append( ChannelInst );
     } 
     else { 
    stringBuffer.append(TEXT_10);
     } 
    } 
     for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/ogu"); 
     if((MappedUri != null) && (MappedUri != "")) { 
    stringBuffer.append(TEXT_11);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_12);
     } 
     else { 
    stringBuffer.append(TEXT_13);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_14);
     } 
    } 
    stringBuffer.append(TEXT_15);
    stringBuffer.append(TEXT_16);
    return stringBuffer.toString();
  }
}
