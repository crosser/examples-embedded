package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class io002c_template
{
  protected static String nl;
  public static synchronized io002c_template create(String lineSeparator)
  {
    nl = lineSeparator;
    io002c_template result = new io002c_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = NL + "/*CODE_BLOCK_BEGIN[IO002.c]*/" + NL + "/*******************************************************************************" + NL + " Copyright (c) 2012, Infineon Technologies AG                                 **" + NL + " All rights reserved.                                                         **" + NL + "                                                                              **" + NL + " Redistribution and use in source and binary forms, with or without           **" + NL + " modification,are permitted provided that the following conditions are met:   **" + NL + "                                                                              **" + NL + " *Redistributions of source code must retain the above copyright notice,      **" + NL + " this list of conditions and the following disclaimer.                        **" + NL + " *Redistributions in binary form must reproduce the above copyright notice,   **" + NL + " this list of conditions and the following disclaimer in the documentation    **" + NL + " and/or other materials provided with the distribution.                       **" + NL + " *Neither the name of the copyright holders nor the names of its contributors **" + NL + " may be used to endorse or promote products derived from this software without**" + NL + " specific prior written permission.                                           **" + NL + "                                                                              **" + NL + " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"  **" + NL + " AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **" + NL + " IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **" + NL + " ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **" + NL + " LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **" + NL + " CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **" + NL + " SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **" + NL + " INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **" + NL + " CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **" + NL + " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **" + NL + " POSSIBILITY OF SUCH DAMAGE.                                                  **" + NL + "                                                                              **" + NL + " To improve the quality of the software, users are encouraged to share        **" + NL + " modifications, enhancements or bug fixes with Infineon Technologies AG       **" + NL + " dave@infineon.com).                                                          **" + NL + "                                                                              **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [yes/no]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : July 15, 2013                                           **" + NL + "**                                                                            **" + NL + "*******************************************************************************/" + NL + "/*******************************************************************************" + NL + "**                      Author(s) Identity                                    **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** Initials     Name                                                          **" + NL + "** ---------------------------------------------------------------------------**" + NL + "** PAE        App Developer                                                   **" + NL + "*******************************************************************************/" + NL + "/**" + NL + " * @file   IO002.c" + NL + " *" + NL + " * @brief  IO_Digital _IO002 App" + NL + " */" + NL + "/* Revision History " + NL + " *" + NL + " * 01 Jan 2013 v1.0.12  Added constraint for Pad driver to skip the " + NL + " *                      configuration for XMC1000 devices." + NL + " * 16 Mar 2013 v1.0.14  1.Modified OMR register configuration (Direct assignment " + NL + " *                      without reading) to upgrade performance.                       " + NL + " * 19 Jun 2013 v1.0.18  1.Conditional code generation for OMR & PDR registers " + NL + " *                      configuration if Output Driver is enabled." + NL + " *                      2. Removed IO002_DisableOutputDriver() & " + NL + " *                      IO002_EnableOutputDriver() API definitions, as output " + NL + " *                      port pin configuration shall be done by higher level " + NL + " *                      APP connections." + NL + " * 15 Jul 2013 v1.0.20  1. Pad Hysteresis Control register configuration added" + NL + " *                      for XMC1000 devices to configure Standard/Large " + NL + " *                      Hysteresis on user selection basis.                    " + NL + " */" + NL + "/*******************************************************************************" + NL + " ** INCLUDE FILES                                                             **" + NL + " ******************************************************************************/" + NL + "" + NL + "/** Inclusion of header file */" + NL + "#include <DAVE3.h>" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Macro Definitions                             **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Type Definitions                              **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                 Private Function Declarations:" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Global Constant Definitions                           **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Global Variable Definitions                           **" + NL + "*******************************************************************************/";
  protected final String TEXT_2 = NL + NL + "/*******************************************************************************" + NL + "**                      Private Constant Definitions                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                 Function like macro definitions                            **" + NL + "*******************************************************************************/" + NL + "/*******************************************************************************" + NL + "**                      Private Function Definitions                          **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Public Function Definitions                           **" + NL + "*******************************************************************************/" + NL + "/** @ingroup IO002_Func" + NL + " * @{" + NL + " */" + NL + "/* Function to configure Port Pins based on user configuration & Higher App " + NL + " * configurations." + NL + " */" + NL + "void IO002_Init(void)" + NL + "{" + NL + "   /* <<<DD_IO002_API_1>>> */";
  protected final String TEXT_3 = "   ";
  protected final String TEXT_4 = NL + "  /* Configuration of ";
  protected final String TEXT_5 = " Port ";
  protected final String TEXT_6 = " based on User configuration */";
  protected final String TEXT_7 = NL + "  IO002_Handle";
  protected final String TEXT_8 = ".PortRegs->OMR = ";
  protected final String TEXT_9 = "U << ";
  protected final String TEXT_10 = ";  ";
  protected final String TEXT_11 = NL + "  IO002_Handle";
  protected final String TEXT_12 = ".PortRegs->PDR0   &= (uint32_t)(~(PORT";
  protected final String TEXT_13 = "_PDR0_PD";
  protected final String TEXT_14 = "_Msk));" + NL + "  IO002_Handle";
  protected final String TEXT_15 = ".PortRegs->PDR0   |= (uint32_t)((";
  protected final String TEXT_16 = "UL << PORT";
  protected final String TEXT_17 = "_PDR0_PD";
  protected final String TEXT_18 = "_Pos) & \\" + NL + "                                          PORT";
  protected final String TEXT_19 = "_PDR0_PD";
  protected final String TEXT_20 = "_Msk);";
  protected final String TEXT_21 = NL + "  IO002_Handle";
  protected final String TEXT_22 = ".PortRegs->PDR1  &= (uint32_t)(~(PORT";
  protected final String TEXT_23 = "_PDR1_PD";
  protected final String TEXT_24 = "_Msk));" + NL + "  IO002_Handle";
  protected final String TEXT_25 = ".PortRegs->PDR1  |= (uint32_t)((";
  protected final String TEXT_26 = "UL << PORT";
  protected final String TEXT_27 = "_PDR1_PD";
  protected final String TEXT_28 = "_Pos) & \\" + NL + "                                     PORT";
  protected final String TEXT_29 = "_PDR1_PD";
  protected final String TEXT_30 = "_Msk);";
  protected final String TEXT_31 = NL + "  IO002_Handle";
  protected final String TEXT_32 = ".PortRegs->HWSEL  |= (2U << ";
  protected final String TEXT_33 = ");";
  protected final String TEXT_34 = NL + "  IO002_Handle";
  protected final String TEXT_35 = ".PortRegs->IOCR0 |= (";
  protected final String TEXT_36 = "U << ";
  protected final String TEXT_37 = ");";
  protected final String TEXT_38 = NL + "  IO002_Handle";
  protected final String TEXT_39 = ".PortRegs->IOCR4 |= (";
  protected final String TEXT_40 = "U << ";
  protected final String TEXT_41 = ");";
  protected final String TEXT_42 = NL + "  IO002_Handle";
  protected final String TEXT_43 = ".PortRegs->IOCR8 |= (";
  protected final String TEXT_44 = "U << ";
  protected final String TEXT_45 = ");";
  protected final String TEXT_46 = NL + "  IO002_Handle";
  protected final String TEXT_47 = ".PortRegs->IOCR12 |= (";
  protected final String TEXT_48 = "U << ";
  protected final String TEXT_49 = ");";
  protected final String TEXT_50 = NL + "  PORT";
  protected final String TEXT_51 = "->PHCR0 |= PORT";
  protected final String TEXT_52 = "_PHCR0_PH";
  protected final String TEXT_53 = "_Msk;";
  protected final String TEXT_54 = NL + "  PORT";
  protected final String TEXT_55 = "->PHCR1 |= PORT";
  protected final String TEXT_56 = "_PHCR1_PH";
  protected final String TEXT_57 = "_Msk;\t  ";
  protected final String TEXT_58 = NL + "  PORT";
  protected final String TEXT_59 = "->PHCR0 &= ~(PORT";
  protected final String TEXT_60 = "_PHCR0_PH";
  protected final String TEXT_61 = "_Msk);";
  protected final String TEXT_62 = NL + "  PORT";
  protected final String TEXT_63 = "->PHCR1 &= ~(PORT";
  protected final String TEXT_64 = "_PHCR1_PH";
  protected final String TEXT_65 = "_Msk);\t  ";
  protected final String TEXT_66 = NL + "  IO002_Handle";
  protected final String TEXT_67 = ".PortRegs->IOCR0 |= (";
  protected final String TEXT_68 = "U << ";
  protected final String TEXT_69 = ");";
  protected final String TEXT_70 = NL + "  IO002_Handle";
  protected final String TEXT_71 = ".PortRegs->IOCR4 |= (";
  protected final String TEXT_72 = "U << ";
  protected final String TEXT_73 = ");";
  protected final String TEXT_74 = NL + "  IO002_Handle";
  protected final String TEXT_75 = ".PortRegs->IOCR8 |= (";
  protected final String TEXT_76 = "U << ";
  protected final String TEXT_77 = ");";
  protected final String TEXT_78 = NL + "  IO002_Handle";
  protected final String TEXT_79 = ".PortRegs->IOCR12 |= (";
  protected final String TEXT_80 = "U << ";
  protected final String TEXT_81 = ");";
  protected final String TEXT_82 = NL + "  /* PIN App instance (no.";
  protected final String TEXT_83 = ") is not mapped to any port pin. */";
  protected final String TEXT_84 = NL + "}" + NL + "" + NL + "void IO002_DisableOutputDriver(const IO002_HandleType* Handle,IO002_InputModeType Mode)" + NL + "{" + NL + "   /* Removed the definition of this API in v1.0.18 Release, as output port pin " + NL + "      configuration shall be done by higher level App */" + NL + "}" + NL + "" + NL + "void IO002_EnableOutputDriver(const IO002_HandleType* Handle,IO002_OutputModeType Mode)" + NL + "{" + NL + "   /* Removed the definition of this API in v1.0.18 Release, as output port pin " + NL + "\t  configuration shall be done by higher level App */" + NL + "}" + NL + "" + NL + "/**" + NL + "*@}" + NL + "*/\t" + NL + "" + NL + "/*CODE_BLOCK_END*/" + NL;
  protected final String TEXT_85 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
    stringBuffer.append(TEXT_1);
     int IsTIMM1Device = -1; 
     IsTIMM1Device = ((app.getSoftwareId().substring(0,1).compareTo("1")==0)?1:0);

    stringBuffer.append(TEXT_2);
     String AppBaseuri = "app/io002/"; 
     String appInst  = null; 
     ArrayList<String> appsList = (ArrayList<String>)(app.getApps("app/io002/"));
   for (String appIns : appsList ) {
   appInst = appIns.substring(appIns.lastIndexOf("/")+1);
     String pinUri = app.getMappedUri(AppBaseuri + appInst +"/pin"); 
     if ((pinUri != null) && (pinUri.trim() != "")) { 
     String portNo = pinUri.substring(pinUri.indexOf("port/p/")+7,pinUri.indexOf("/pad/")); 
     String pinNo = pinUri.substring(pinUri.indexOf("/pad/")+5,pinUri.length()); 
    stringBuffer.append(TEXT_3);
     int OMR_PS = app.getIntegerValue(AppBaseuri + appInst +"/pin/omr_ps");
  int PDR_PD = app.getIntegerValue(AppBaseuri + appInst +"/pin/pdr_pd");
  int HW_SEL = app.getIntegerValue(AppBaseuri + appInst +"IO002_irwHWControl");
  int IOCR_PCR = app.getIntegerValue(AppBaseuri + appInst +"/pin/iocr_pcr");
  int IOCR_PCR2 = app.getIntegerValue(AppBaseuri + appInst +"/IO002_inputchardummy");
  int IOCR_PO = app.getIntegerValue(AppBaseuri + appInst +"/pin/iocr_po");
  int IOCR_OE = app.getIntegerValue(AppBaseuri + appInst +"/pin/iocr_oe"); 
  int PHCR_EN = app.getIntegerValue(AppBaseuri + appInst +"/IO002_erwPadHysteresis");
  int IOCR    = (IOCR_PO << 3 );
     int Pin = Integer.parseInt(pinNo);
    stringBuffer.append(TEXT_4);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_5);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_6);
    if(IOCR_OE == 1 ){
    stringBuffer.append(TEXT_7);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_8);
    stringBuffer.append(OMR_PS);
    stringBuffer.append(TEXT_9);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_10);
    }
     if((IsTIMM1Device !=1) && (IOCR_OE == 1 )){
     if(Pin < 8) {
    stringBuffer.append(TEXT_11);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_12);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_13);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_14);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_15);
    stringBuffer.append(PDR_PD);
    stringBuffer.append(TEXT_16);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_17);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_18);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_19);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_20);
     } else {
    stringBuffer.append(TEXT_21);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_22);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_23);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_24);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_25);
    stringBuffer.append(PDR_PD);
    stringBuffer.append(TEXT_26);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_27);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_28);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_29);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_30);
    }}
     if(HW_SEL == 1 ) {
    stringBuffer.append(TEXT_31);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_32);
    stringBuffer.append(Pin);
    stringBuffer.append(TEXT_33);
     }
  if(IOCR_OE == 1 ) {
  if(Pin < 4) { 
    stringBuffer.append(TEXT_34);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_35);
    stringBuffer.append(IOCR);
    stringBuffer.append(TEXT_36);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_37);
    }else if (Pin >= 4 && Pin <= 7) {  
    Pin = Pin - 4; 
    stringBuffer.append(TEXT_38);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_39);
    stringBuffer.append(IOCR);
    stringBuffer.append(TEXT_40);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_41);
    } else if (Pin >= 8 && Pin <= 11) { 
	Pin = Pin - 8; 
    stringBuffer.append(TEXT_42);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_43);
    stringBuffer.append(IOCR);
    stringBuffer.append(TEXT_44);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_45);
    } else if (Pin >= 12 && Pin <= 15) { 
    Pin = Pin - 12; 
    stringBuffer.append(TEXT_46);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_47);
    stringBuffer.append(IOCR);
    stringBuffer.append(TEXT_48);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_49);
    }}
     if(IOCR_OE == 0 ) {
     if (IsTIMM1Device == 1){
     if (PHCR_EN == 1){
     if (Pin < 8) {
    stringBuffer.append(TEXT_50);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_51);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_52);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_53);
    } else if ((Pin >= 8) && (Pin <= 15)) {
    stringBuffer.append(TEXT_54);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_55);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_56);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_57);
    }}
    else {
     if (Pin < 8) {
    stringBuffer.append(TEXT_58);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_59);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_60);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_61);
    } else if ((Pin >= 8) && (Pin <= 15)) {
    stringBuffer.append(TEXT_62);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_63);
    stringBuffer.append(portNo);
    stringBuffer.append(TEXT_64);
    stringBuffer.append(pinNo);
    stringBuffer.append(TEXT_65);
    }
    }}
    if(Pin < 4) { 
    stringBuffer.append(TEXT_66);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_67);
    stringBuffer.append(IOCR_PCR2);
    stringBuffer.append(TEXT_68);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_69);
    }else if (Pin >= 4 && Pin <= 7) {  
    Pin = Pin - 4; 
    stringBuffer.append(TEXT_70);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_71);
    stringBuffer.append(IOCR_PCR2);
    stringBuffer.append(TEXT_72);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_73);
    } else if (Pin >= 8 && Pin <= 11) { 
	Pin = Pin - 8; 
    stringBuffer.append(TEXT_74);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_75);
    stringBuffer.append(IOCR_PCR2);
    stringBuffer.append(TEXT_76);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_77);
    } else if (Pin >= 12 && Pin <= 15) { 
    Pin = Pin - 12; 
    stringBuffer.append(TEXT_78);
    stringBuffer.append(appInst);
    stringBuffer.append(TEXT_79);
    stringBuffer.append(IOCR_PCR2);
    stringBuffer.append(TEXT_80);
    stringBuffer.append((3+(Pin*8)));
    stringBuffer.append(TEXT_81);
    }}
    } else { 
    stringBuffer.append(TEXT_82);
    stringBuffer.append( appInst );
    stringBuffer.append(TEXT_83);
    }} 
    stringBuffer.append(TEXT_84);
    stringBuffer.append(TEXT_85);
    return stringBuffer.toString();
  }
}
