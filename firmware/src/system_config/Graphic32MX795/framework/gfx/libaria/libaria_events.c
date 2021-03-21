/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_events.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
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

#include "gfx/libaria/libaria_events.h"

// MainWnd - ShowEvent
void MainWnd_ShowEvent(laScreen* scr)
{
}

// MainOKBtn - ReleasedEvent
void MainOKBtn_ReleasedEvent(laButtonWidget* btn)
{
}

// StartRaceBtn - ReleasedEvent
void StartRaceBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (RaceWnd) - Show Screen - RaceWnd
    laContext_SetActiveScreen(RaceWnd_ID);
}

// EEPromBtn - ReleasedEvent
void EEPromBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigPilotWnd) - Show Screen - ConfigPilotWnd
    laContext_SetActiveScreen(ConfigPilotWnd_ID);
}

// ConfigAppBtn - ReleasedEvent
void ConfigAppBtn_ReleasedEvent(laButtonWidget* btn)
{
    // ConfigBtnOnClick - Show Screen - ConfigMainWnd
    laContext_SetActiveScreen(ConfigMainWnd_ID);
}

// ButtonWidget1 - ReleasedEvent
void ButtonWidget1_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (WifiTesting) - Show Screen - WifiTesting
    laContext_SetActiveScreen(WifiTesting_ID);
}

// TouchExitBtn - ReleasedEvent
void TouchExitBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (MainWnd) - Show Screen - MainWnd
    laContext_SetActiveScreen(MainWnd_ID);
}

// ButtonWidget10 - ReleasedEvent
void ButtonWidget10_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (MainWnd) - Show Screen - MainWnd
    laContext_SetActiveScreen(MainWnd_ID);
}

// ButtonWidget12 - ReleasedEvent
void ButtonWidget12_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigThrLevelWnd) - Show Screen - ConfigThrLevelWnd
    laContext_SetActiveScreen(ConfigThrLevelWnd_ID);
}

// ButtonWidget13 - ReleasedEvent
void ButtonWidget13_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigRaceLevelsWnd) - Show Screen - ConfigRaceLevelsWnd
    laContext_SetActiveScreen(ConfigRaceLevelsWnd_ID);
}

// ButtonWidget14 - ReleasedEvent
void ButtonWidget14_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (TouchCalibrationWnd) - Show Screen - TouchCalibrationWnd
    laContext_SetActiveScreen(TouchCalibrationWnd_ID);
}

// ButtonWidget - ReleasedEvent
void ButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (RaceConfigWnd) - Show Screen - RaceConfigWnd
    laContext_SetActiveScreen(RaceConfigWnd_ID);
}

// ExitBtn - ReleasedEvent
void ExitBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (MainWnd) - Show Screen - ConfigMainWnd
    laContext_SetActiveScreen(ConfigMainWnd_ID);
}

// ReadBtn2 - ReleasedEvent
void ReadBtn2_ReleasedEvent(laButtonWidget* btn)
{
    // USART_SetUp_Read
      USART_SetUp_Read(); // Promgrams a Buffer Read
}

// ExitConfigLevelBtn - ReleasedEvent
void ExitConfigLevelBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigMainWnd) - Show Screen - ConfigMainWnd
    laContext_SetActiveScreen(ConfigMainWnd_ID);
}

// ExitConfigThrLevelBtn - ReleasedEvent
void ExitConfigThrLevelBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigMainWnd) - Show Screen - ConfigMainWnd
    laContext_SetActiveScreen(ConfigMainWnd_ID);
}

// ButtonWidget29 - ReleasedEvent
void ButtonWidget29_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (MainWnd) - Show Screen - MainWnd
    laContext_SetActiveScreen(MainWnd_ID);
}

// ShowFinalStatsBtn - ReleasedEvent
void ShowFinalStatsBtn_ReleasedEvent(laButtonWidget* btn)
{
    // ShowFinalStats
    RaceData.state = RACE_FINISHED;
    RaceStartWnd_ShowRaceStats();
}

// ShowEnablePilotsBtn - ReleasedEvent
void ShowEnablePilotsBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Abrir el panel
    ShowEnablePanelBtn_OnClik();
}

// CloseEnableBtn - ReleasedEvent
void CloseEnableBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Hide Enable Panel
    laWidget_SetVisible((laWidget *)EnablePilotsPanel,LA_FALSE);
    laContext_RedrawAll(); // Forza el update de toda la pantalla
}

// ExitRaceParamBtn - ReleasedEvent
void ExitRaceParamBtn_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigMainWnd) - Show Screen - ConfigMainWnd
    laContext_SetActiveScreen(ConfigMainWnd_ID);
}

// ButtonWidget15 - ReleasedEvent
void ButtonWidget15_ReleasedEvent(laButtonWidget* btn)
{
    // Show Screen (ConfigMainWnd) - Show Screen - ConfigMainWnd
    laContext_SetActiveScreen(ConfigMainWnd_ID);
}





