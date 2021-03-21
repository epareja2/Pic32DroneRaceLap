/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Definitions Header

  File Name:
    libaria_macros.h

  Summary:
    Build-time generated definitions header based on output by the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated definitions header based on output by the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version 2.06
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _LIBARIA_INIT_H
#define _LIBARIA_INIT_H

#ifndef NATIVE
#include "system_config.h"
#include "system_definitions.h"
#endif

#include "gfx/libaria/libaria.h"
#include "gfx/libaria/libaria_events.h"

#include "gfx/gfx_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

#define LIBARIA_SCREEN_COUNT   9

// reference IDs for generated libaria screens
// screen "ConfigMainWnd"
#define ConfigMainWnd_ID    2

// screen "ConfigPilotWnd"
#define ConfigPilotWnd_ID    3

// screen "ConfigRaceLevelsWnd"
#define ConfigRaceLevelsWnd_ID    4

// screen "ConfigThrLevelWnd"
#define ConfigThrLevelWnd_ID    5

// screen "MainWnd"
#define MainWnd_ID    0

// screen "RaceConfigWnd"
#define RaceConfigWnd_ID    7

// screen "RaceWnd"
#define RaceWnd_ID    6

// screen "TouchCalibrationWnd"
#define TouchCalibrationWnd_ID    1

// screen "WifiTesting"
#define WifiTesting_ID    8



extern laScheme defaultScheme;
extern laScheme CircleSchema;
extern laScheme ProgressBarSchema;
extern laScheme BackGrowndGradient;
extern laScheme BigTextSchema;
extern laScheme BlackGradient;
extern laScheme Primitives;
extern laScheme ButtonsNormal;
extern laScheme WindowCaption;
extern laScheme KeyPadNumberScheme;
extern laGradientWidget* GradientWidget1;
extern laLabelWidget* LabelWidget2;
extern laWidget* PanelWidget4;
extern laButtonWidget* MainOKBtn;
extern laButtonWidget* MainCancelBtn;
extern laButtonWidget* StartRaceBtn;
extern laButtonWidget* EEPromBtn;
extern laButtonWidget* ConfigAppBtn;
extern laLabelWidget* LabelWidget;
extern laLabelWidget* LabelWidget4;
extern laLabelWidget* LabelWidget5;
extern laButtonWidget* ButtonWidget1;
extern laLabelWidget* LabelWidget9;
extern laGradientWidget* GradientWidget;
extern laWidget* TouchWndCaptionPanel;
extern laLabelWidget* TouchCalibrationWndCaption;
extern laWidget* PanelWidget6;
extern laButtonWidget* TouchOkBtn;
extern laButtonWidget* TouchExitBtn;
extern laCircleWidget* CirclePoint;
extern laImageWidget* GreenPointImg;
extern laLabelWidget* TouchPointLbl;
extern laLabelWidget* TouchMsg1Lbl;
extern laLabelWidget* TouchMsg2Lbl;
extern laGradientWidget* GradientWidget3;
extern laLabelWidget* ConfigMainWndLbl;
extern laWidget* PanelWidget9;
extern laButtonWidget* ButtonWidget10;
extern laButtonWidget* ButtonWidget11;
extern laButtonWidget* ButtonWidget12;
extern laButtonWidget* ButtonWidget13;
extern laButtonWidget* ButtonWidget14;
extern laLabelWidget* LabelWidget15;
extern laLabelWidget* LabelWidget1;
extern laLabelWidget* LabelWidget10;
extern laButtonWidget* ButtonWidget;
extern laLabelWidget* LabelWidget7;
extern laGradientWidget* GradientWidget4;
extern laLabelWidget* LabelWidget16;
extern laWidget* PanelWidget;
extern laButtonWidget* ExitBtn;
extern laButtonWidget* ReadBtn2;
extern laLabelWidget* LabelWidget;
extern laTextFieldWidget* ModuleEdit;
extern laButtonWidget* ModuleDropDownBtn;
extern laGroupBoxWidget* GroupBoxWidget2;
extern laTextFieldWidget* BandEdit;
extern laLabelWidget* LabelWidget3;
extern laTextFieldWidget* ChannelEdit;
extern laLabelWidget* ChannelLbl;
extern laButtonWidget* ChannelUpBtn;
extern laButtonWidget* ChannelDownBtn;
extern laButtonWidget* BandUpBtn;
extern laButtonWidget* BandDownBtn;
extern laButtonWidget* SendFreqBtn;
extern laLabelWidget* RSSI_lbl;
extern laLabelWidget* LabelWidget12;
extern laLabelWidget* FreqLbl;
extern laLabelWidget* LabelWidget13;
extern laListWidget* ModuloList;
extern laGradientWidget* GradientWidget19;
extern laLabelWidget* LabelWidget20;
extern laWidget* PanelWidget21;
extern laButtonWidget* ExitConfigLevelBtn;
extern laButtonWidget* InitCalibrationRSSILevels_Btn;
extern laLabelWidget* Pilot0Lbl;
extern laLabelWidget* Band0Lbl;
extern laLabelWidget* RSSI0Lbl;
extern laProgressBarWidget* RSSI0Bar;
extern laImageWidget* MinRSSI0Line;
extern laImageWidget* MaxRSSI0Line;
extern laLabelWidget* Pilot1Lbl;
extern laLabelWidget* Band1Lbl;
extern laLabelWidget* RSSI1Lbl;
extern laProgressBarWidget* RSSI1Bar;
extern laImageWidget* MinRSSI1Line;
extern laImageWidget* MaxRSSI1Line;
extern laLabelWidget* Pilot2Lbl;
extern laLabelWidget* Band2Lbl;
extern laLabelWidget* RSSI2Lbl;
extern laProgressBarWidget* RSSI2Bar;
extern laImageWidget* MinRSSI2Line;
extern laImageWidget* MaxRSSI2Line;
extern laLabelWidget* Pilot4Lbl;
extern laLabelWidget* Band3Lbl;
extern laLabelWidget* RSSI3Lbl;
extern laProgressBarWidget* RSSI3Bar;
extern laImageWidget* MinRSSI3Line;
extern laImageWidget* MaxRSSI3Line;
extern laLabelWidget* StatusLbl;
extern laButtonWidget* Pilot0Enable;
extern laButtonWidget* Pilot1Enable;
extern laButtonWidget* Pilot2Enable;
extern laButtonWidget* Pilot3Enable;
extern laGradientWidget* GradientWidget20;
extern laLabelWidget* LabelWidget21;
extern laWidget* PanelWidget22;
extern laButtonWidget* ExitConfigThrLevelBtn;
extern laButtonWidget* SaveConfigThrLevelBtn;
extern laButtonWidget* Pilot0Btn;
extern laButtonWidget* Pilot1Btn;
extern laButtonWidget* Pilot2Btn;
extern laButtonWidget* Pilot3Btn;
extern laGroupBoxWidget* GroupBoxWidget30;
extern laLabelWidget* LabelWidget34;
extern laLabelWidget* LabelWidget37;
extern laTextFieldWidget* MinRSSIThrEdit;
extern laTextFieldWidget* MaxRSSIThrEdit;
extern laLabelWidget* RSSILbl;
extern laLabelWidget* LabelWidget44;
extern laLabelWidget* BandaLbl;
extern laProgressBarWidget* RSSIBar;
extern laImageWidget* MinRSSILine;
extern laImageWidget* MaxRSSILine;
extern laKeyPadWidget* KeyPad1;
extern laGradientWidget* GradientWidget2;
extern laLabelWidget* TimeCountLbl;
extern laLabelWidget* LabelWidget6;
extern laWidget* PanelWidget7;
extern laLabelWidget* LabelWidget28;
extern laLabelWidget* LabelWidget29;
extern laLabelWidget* LabelWidget30;
extern laLabelWidget* LabelWidget31;
extern laLineWidget* LineaTop0;
extern laLabelWidget* RaceLapTimesLbl;
extern laLabelWidget* LapsNumbersLbl;
extern laLabelWidget* Pilot0TimesLbl;
extern laLineWidget* Linea1;
extern laLabelWidget* Pilot1TimesLbl;
extern laLineWidget* Linea2;
extern laLabelWidget* Pilot3TimesLbl;
extern laLabelWidget* Pilot2TimesLbl;
extern laLineWidget* Linea3;
extern laLineWidget* Linea4;
extern laLineWidget* Linea5;
extern laLineWidget* Linea6;
extern laLineWidget* Linea7;
extern laLabelWidget* MSegLbl;
extern laLineWidget* Linea8;
extern laLineWidget* LineaVertical;
extern laButtonWidget* StartStopRaceBtn;
extern laButtonWidget* ButtonWidget29;
extern laButtonWidget* ShowFinalStatsBtn;
extern laLabelWidget* TotalPilot0Lbl;
extern laLabelWidget* TotalPilot1Lbl;
extern laLabelWidget* TotalPilot2Lbl;
extern laLabelWidget* TotalPilot3Lbl;
extern laButtonWidget* ShowEnablePilotsBtn;
extern laWidget* FinalStatsPanel;
extern laRectangleWidget* RectangleWidget2;
extern laRectangleWidget* RectangleWidget3;
extern laLabelWidget* _1PlaceLbl;
extern laRectangleWidget* RectangleWidget4;
extern laLabelWidget* _2PlaceLbl;
extern laLabelWidget* _3PlaceLbl;
extern laButtonWidget* CloseFinalStatsBtn;
extern laLabelWidget* _2TimeLbl;
extern laLabelWidget* _1TimeLbl;
extern laLabelWidget* _3TimeLbl;
extern laLabelWidget* _4PlaceLbl;
extern laLabelWidget* _4TimeLbl;
extern laWidget* EnablePilotsPanel;
extern laButtonWidget* Pilot0EnableBtn;
extern laButtonWidget* Pilot1EnableBtn;
extern laButtonWidget* Pilot2EnableBtn;
extern laButtonWidget* Pilot3EnableBtn;
extern laButtonWidget* CloseEnableBtn;
extern laLabelWidget* LabelWidget;
extern laLabelWidget* Channel0Lbl;
extern laLabelWidget* Channel1Lbl;
extern laLabelWidget* Channel2Lbl;
extern laLabelWidget* Channel3Lbl;
extern laGradientWidget* GradientWidget23;
extern laWidget* PanelWidget24;
extern laLabelWidget* wndCaptionRaceParam;
extern laButtonWidget* ExitRaceParamBtn;
extern laButtonWidget* SaveRaceParamBtn;
extern laGroupBoxWidget* GroupBoxWidget34;
extern laRadioButtonWidget* CumulativeTimeChk;
extern laRadioButtonWidget* EachRaceTimeChk;
extern laGroupBoxWidget* GroupBoxWidget38;
extern laButtonWidget* SkipFirstLapBtn;
extern laLabelWidget* LapNumberConfLbl;
extern laButtonWidget* LapUpBtn;
extern laButtonWidget* LapDownBtn;
extern laLabelWidget* LabelWidget45;
extern laLabelWidget* LabelWidget8;
extern laButtonWidget* TLapDownBtn;
extern laLabelWidget* TVueltaLbl;
extern laButtonWidget* TLapUpBtn;
extern laLabelWidget* LabelWidget39;
extern laLabelWidget* LabelWidget11;
extern laButtonWidget* StartBeepsDownBtn;
extern laLabelWidget* StartBeepsLbl;
extern laButtonWidget* StartBeepsUpBtn;
extern laGradientWidget* GradientWidget10;
extern laWidget* PanelWidget11;
extern laLabelWidget* LabelWidget14;
extern laButtonWidget* ButtonWidget15;
extern laButtonWidget* StartListeningUSARTBtn;
extern laListWidget* ATCommandsLst;
extern laButtonWidget* SendATCommandBtn;
extern laTextFieldWidget* USART_TextLbl;
extern laButtonWidget* ClearUSART_TextBtn;


int32_t libaria_initialize(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _LIBARIA_INIT_H
/*******************************************************************************
 End of File
*/
