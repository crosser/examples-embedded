package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class uart001_confc_template
{
  protected static String nl;
  public static synchronized uart001_confc_template create(String lineSeparator)
  {
    nl = lineSeparator;
    uart001_confc_template result = new uart001_confc_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + "/*CODE_BLOCK_BEGIN[UART001_Conf.c]*/" + NL + "/******************************************************************************" + NL + " Copyright (c) 2011, Infineon Technologies AG                                **" + NL + " All rights reserved.                                                        **" + NL + "                                                                             **" + NL + " Redistribution and use in source and binary forms, with or without          **" + NL + " modification,are permitted provided that the following conditions are met:  **" + NL + "                                                                             **" + NL + " *Redistributions of source code must retain the above copyright notice,     **" + NL + " this list of conditions and the following disclaimer.                       **" + NL + " *Redistributions in binary form must reproduce the above copyright notice,  **" + NL + " this list of conditions and the following disclaimer in the documentation   **" + NL + " and/or other materials provided with the distribution.                      **" + NL + " *Neither the name of the copyright holders nor the names of its             **" + NL + " contributors may be used to endorse or promote products derived from this   **" + NL + " software without specific prior written permission.                         **" + NL + "                                                                             **" + NL + " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" **" + NL + " AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   **" + NL + " IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  **" + NL + " ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  **" + NL + " LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        **" + NL + " CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        **" + NL + " SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   **" + NL + " INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     **" + NL + " CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      **" + NL + " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  **" + NL + " POSSIBILITY OF SUCH DAMAGE.                                                 **" + NL + "                                                                             **" + NL + " To improve the quality of the software, users are encouraged to share       **" + NL + " modifications, enhancements or bug fixes with Infineon Technologies AG      **" + NL + " dave@infineon.com).                                                         **" + NL + "                                                                             **" + NL + "*******************************************************************************" + NL + "**                                                                           **" + NL + "**                                                                           **" + NL + "** PLATFORM : Infineon XMC4000/ XMC1000 Series                               **" + NL + "**                                                                           **" + NL + "** COMPILER : Compiler Independent                                           **" + NL + "**                                                                           **" + NL + "** AUTHOR   : App Developer                                                  **" + NL + "**                                                                           **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                      **" + NL + "**                                                                           **" + NL + "**                                                                           **" + NL + "******************************************************************************/" + NL + "/**" + NL + " * @file   UART001_Conf.c" + NL + " * " + NL + " * @App Version UART001 <";
  protected final String TEXT_2 = ">" + NL + " *" + NL + " * @brief  Configuration file generated based on UI settings " + NL + " *         of UART001 App" + NL + " *" + NL + " */" + NL + " /*" + NL + " * Revision History" + NL + " * 04 Dec 2012 v1.0.4  Changes from 1.0.2 are" + NL + " *                     1. Modified the handle parameters for macros from" + NL + " *                     numbers." + NL + " *                     2. Modified as per coding guidelines and MISRA checks" + NL + " * 26 Mar 2013 v1.0.10 1. Updated for the alignment in revision history." + NL + " *                     2. Updated to support XMC1000 devices." + NL + " *                     3. Modified the structure UART001_HandleType to add" + NL + " *                     baud parameters for the configured baud rate." + NL + " */" + NL + "/******************************************************************************" + NL + " ** INCLUDE FILES                                                            **" + NL + " *****************************************************************************/" + NL + "#include <DAVE3.h>";
  protected final String TEXT_3 = NL;
  protected final String TEXT_4 = NL + NL + "const UART001_HandleType UART001_Handle";
  protected final String TEXT_5 = "  = " + NL + "{";
  protected final String TEXT_6 = NL + "   .UartRegs = USIC";
  protected final String TEXT_7 = "_CH";
  protected final String TEXT_8 = ", /* Usic Channel offset value */" + NL + "   .Mode = ";
  protected final String TEXT_9 = "UART_LOOPBACK";
  protected final String TEXT_10 = "UART_HALFDUPLEX";
  protected final String TEXT_11 = "UART_FULLDUPLEX";
  protected final String TEXT_12 = ", /* Mode */" + NL + "   .StopBit = ";
  protected final String TEXT_13 = "UART_TWO_STOPBIT";
  protected final String TEXT_14 = "UART_ONE_STOPBIT";
  protected final String TEXT_15 = ",/* StopBit */" + NL + "   .Parity  = ";
  protected final String TEXT_16 = "UART_PARITY_EVEN";
  protected final String TEXT_17 = "UART_PARITY_ODD";
  protected final String TEXT_18 = "UART_PARITY_NONE";
  protected final String TEXT_19 = ",/* Parity */ " + NL + "   .DataBits = (uint16_t)";
  protected final String TEXT_20 = ",/* Word Length */" + NL + "   .BaudRate  = (uint32_t)";
  protected final String TEXT_21 = ",/*Baud Rate */" + NL + "   .TxLimit = (uint8_t)";
  protected final String TEXT_22 = ",/* FIFO Tigger Level */" + NL + "   .RxLimit = (uint8_t)";
  protected final String TEXT_23 = ",/* FIFO Tigger Level */" + NL + "   .TxFifoSize = (uint8_t)";
  protected final String TEXT_24 = ",/* Tx FIFO Size */" + NL + "   .RxFifoSize = (uint8_t)";
  protected final String TEXT_25 = ",/* Rx FIFO Size */" + NL + "   .RecvNoiseEn = (bool)";
  protected final String TEXT_26 = ", /* Protocol specific interrupt enable */" + NL + "   .FormatErrEn = (bool)";
  protected final String TEXT_27 = ", /* Protocol specific interrupt enable */" + NL + "   .FrameFinEn = (bool)";
  protected final String TEXT_28 = ", /* Protocol specific interrupt enable */" + NL + "   .BGR_STEP = (uint16_t)";
  protected final String TEXT_29 = ",  /* Baud Rate Generation step value */" + NL + "   .BGR_PDIV = (uint16_t)";
  protected final String TEXT_30 = ",   /* Baud Rate Generation  pdiv value */" + NL + "   .BGR_DCTQ = (uint16_t)";
  protected final String TEXT_31 = ", /* Baud Rate Generation dctq value */";
  protected final String TEXT_32 = "   " + NL + "   .BGR_SP = (uint16_t)";
  protected final String TEXT_33 = ", /* Baud Rate Generation sampling point */" + NL + "   .BGR_PCTQ = (uint8_t)0  /* Baud Rate Generation pctq value */" + NL + "};" + NL;
  protected final String TEXT_34 = NL + "// CHANNEL IS NOT MAPPED";
  protected final String TEXT_35 = NL;
  protected final String TEXT_36 = NL + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_37 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
     String AppBaseuri = "app/uart001/";
    stringBuffer.append(TEXT_1);
    stringBuffer.append( app.getAppVersion(AppBaseuri));
    stringBuffer.append(TEXT_2);
     String Uarturi = "peripheral/usic/"; 
     String MappedUri = null; 
     String UnitInst = null; 
     String ChannelInst = null; 
     int mode= 0; 
     String appInst  = null; 
    stringBuffer.append(TEXT_3);
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/uart001/"));
 for (String appIns : appsList ) {
 appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     MappedUri = app.getMappedUri(AppBaseuri + appInst + "/channel"); 
     if((MappedUri != null) && (MappedUri != "")) { 
     UnitInst = MappedUri.substring(MappedUri .length()-11,MappedUri.indexOf("/channel/")); 
     ChannelInst = MappedUri.substring(MappedUri.length()-1); 
    stringBuffer.append(TEXT_4);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_5);
      for (int t=0; t< 3; t++) { 
	  int opmode = app.getIntegerValue(AppBaseuri + appInst + "/uart001_erwmode/" + t);   
	  if (opmode == 1) {  
	  mode = t ;
	} 
    } 
    stringBuffer.append(TEXT_6);
    stringBuffer.append( UnitInst );
    stringBuffer.append(TEXT_7);
    stringBuffer.append( ChannelInst );
    stringBuffer.append(TEXT_8);
     if(mode==2){
    stringBuffer.append(TEXT_9);
    } else if(mode==1){
    stringBuffer.append(TEXT_10);
    } else{
    stringBuffer.append(TEXT_11);
    }
    stringBuffer.append(TEXT_12);
    if((app.getIntegerValue(AppBaseuri + appInst +"/channel/pcr/stpb")) == 1){
    stringBuffer.append(TEXT_13);
    } else{
    stringBuffer.append(TEXT_14);
    }
    stringBuffer.append(TEXT_15);
    if ((app.getIntegerValue(AppBaseuri + appInst +"/channel/ccr/pm")) == 2){
    stringBuffer.append(TEXT_16);
    } else if ((app.getIntegerValue(AppBaseuri + appInst +"/channel/ccr/pm")) == 3){
    stringBuffer.append(TEXT_17);
    }else if ((app.getIntegerValue(AppBaseuri + appInst +"/channel/ccr/pm")) == 0){
    stringBuffer.append(TEXT_18);
    }else{} 
    stringBuffer.append(TEXT_19);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/channel/sctr/wle") );
    stringBuffer.append(TEXT_20);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/uart001_irwbaudrate") );
    stringBuffer.append(TEXT_21);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/channel/tbctr/limit") );
    stringBuffer.append(TEXT_22);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/channel/rbctr/limit") );
    stringBuffer.append(TEXT_23);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/channel/tbctr_size") );
    stringBuffer.append(TEXT_24);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/channel/rbctr_size") );
    stringBuffer.append(TEXT_25);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/uart001_erwRecvNoiseDetectInt/0") );
    stringBuffer.append(TEXT_26);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/uart001_erwFmtErrorInt/0") );
    stringBuffer.append(TEXT_27);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst +"/uart001_erwFrameFinishInt/0") );
    stringBuffer.append(TEXT_28);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst + "/uart001_stepvalue"));
    stringBuffer.append(TEXT_29);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst + "/uart001_pdivvalue"));
    stringBuffer.append(TEXT_30);
    stringBuffer.append( app.getIntegerValue(AppBaseuri + appInst + "/Time_Quanta_dummylevel") );
    stringBuffer.append(TEXT_31);
    	double sampling_point = 0.0;
 	long sampling_point1 = 0;
 	int dctq = (app.getIntegerValue(AppBaseuri + appInst + "/Time_Quanta_dummylevel")); 	    
   sampling_point = (((1 + dctq) / 2)  +  1);   
   sampling_point1 = Math.round(sampling_point); 			
 
    stringBuffer.append(TEXT_32);
    stringBuffer.append( sampling_point1);
    stringBuffer.append(TEXT_33);
     } 
     else { 
    stringBuffer.append(TEXT_34);
     } 
    stringBuffer.append(TEXT_35);
    } 
    stringBuffer.append(TEXT_36);
    stringBuffer.append(TEXT_37);
    return stringBuffer.toString();
  }
}
