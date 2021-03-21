/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_init.c

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

#include "gfx/libaria/libaria_init.h"

laScheme defaultScheme;
laScheme CircleSchema;
laScheme ProgressBarSchema;
laScheme BackGrowndGradient;
laScheme BigTextSchema;
laScheme BlackGradient;
laScheme Primitives;
laScheme ButtonsNormal;
laScheme WindowCaption;
laScheme KeyPadNumberScheme;
laGradientWidget* GradientWidget1;
laLabelWidget* LabelWidget2;
laWidget* PanelWidget4;
laButtonWidget* MainOKBtn;
laButtonWidget* MainCancelBtn;
laButtonWidget* StartRaceBtn;
laButtonWidget* EEPromBtn;
laButtonWidget* ConfigAppBtn;
laLabelWidget* LabelWidget;
laLabelWidget* LabelWidget4;
laLabelWidget* LabelWidget5;
laButtonWidget* ButtonWidget1;
laLabelWidget* LabelWidget9;
laGradientWidget* GradientWidget;
laWidget* TouchWndCaptionPanel;
laLabelWidget* TouchCalibrationWndCaption;
laWidget* PanelWidget6;
laButtonWidget* TouchOkBtn;
laButtonWidget* TouchExitBtn;
laCircleWidget* CirclePoint;
laImageWidget* GreenPointImg;
laLabelWidget* TouchPointLbl;
laLabelWidget* TouchMsg1Lbl;
laLabelWidget* TouchMsg2Lbl;
laGradientWidget* GradientWidget3;
laLabelWidget* ConfigMainWndLbl;
laWidget* PanelWidget9;
laButtonWidget* ButtonWidget10;
laButtonWidget* ButtonWidget11;
laButtonWidget* ButtonWidget12;
laButtonWidget* ButtonWidget13;
laButtonWidget* ButtonWidget14;
laLabelWidget* LabelWidget15;
laLabelWidget* LabelWidget1;
laLabelWidget* LabelWidget10;
laButtonWidget* ButtonWidget;
laLabelWidget* LabelWidget7;
laGradientWidget* GradientWidget4;
laLabelWidget* LabelWidget16;
laWidget* PanelWidget;
laButtonWidget* ExitBtn;
laButtonWidget* ReadBtn2;
laLabelWidget* LabelWidget;
laTextFieldWidget* ModuleEdit;
laButtonWidget* ModuleDropDownBtn;
laGroupBoxWidget* GroupBoxWidget2;
laTextFieldWidget* BandEdit;
laLabelWidget* LabelWidget3;
laTextFieldWidget* ChannelEdit;
laLabelWidget* ChannelLbl;
laButtonWidget* ChannelUpBtn;
laButtonWidget* ChannelDownBtn;
laButtonWidget* BandUpBtn;
laButtonWidget* BandDownBtn;
laButtonWidget* SendFreqBtn;
laLabelWidget* RSSI_lbl;
laLabelWidget* LabelWidget12;
laLabelWidget* FreqLbl;
laLabelWidget* LabelWidget13;
laListWidget* ModuloList;
laGradientWidget* GradientWidget19;
laLabelWidget* LabelWidget20;
laWidget* PanelWidget21;
laButtonWidget* ExitConfigLevelBtn;
laButtonWidget* InitCalibrationRSSILevels_Btn;
laLabelWidget* Pilot0Lbl;
laLabelWidget* Band0Lbl;
laLabelWidget* RSSI0Lbl;
laProgressBarWidget* RSSI0Bar;
laImageWidget* MinRSSI0Line;
laImageWidget* MaxRSSI0Line;
laLabelWidget* Pilot1Lbl;
laLabelWidget* Band1Lbl;
laLabelWidget* RSSI1Lbl;
laProgressBarWidget* RSSI1Bar;
laImageWidget* MinRSSI1Line;
laImageWidget* MaxRSSI1Line;
laLabelWidget* Pilot2Lbl;
laLabelWidget* Band2Lbl;
laLabelWidget* RSSI2Lbl;
laProgressBarWidget* RSSI2Bar;
laImageWidget* MinRSSI2Line;
laImageWidget* MaxRSSI2Line;
laLabelWidget* Pilot4Lbl;
laLabelWidget* Band3Lbl;
laLabelWidget* RSSI3Lbl;
laProgressBarWidget* RSSI3Bar;
laImageWidget* MinRSSI3Line;
laImageWidget* MaxRSSI3Line;
laLabelWidget* StatusLbl;
laButtonWidget* Pilot0Enable;
laButtonWidget* Pilot1Enable;
laButtonWidget* Pilot2Enable;
laButtonWidget* Pilot3Enable;
laGradientWidget* GradientWidget20;
laLabelWidget* LabelWidget21;
laWidget* PanelWidget22;
laButtonWidget* ExitConfigThrLevelBtn;
laButtonWidget* SaveConfigThrLevelBtn;
laButtonWidget* Pilot0Btn;
laButtonWidget* Pilot1Btn;
laButtonWidget* Pilot2Btn;
laButtonWidget* Pilot3Btn;
laGroupBoxWidget* GroupBoxWidget30;
laLabelWidget* LabelWidget34;
laLabelWidget* LabelWidget37;
laTextFieldWidget* MinRSSIThrEdit;
laTextFieldWidget* MaxRSSIThrEdit;
laLabelWidget* RSSILbl;
laLabelWidget* LabelWidget44;
laLabelWidget* BandaLbl;
laProgressBarWidget* RSSIBar;
laImageWidget* MinRSSILine;
laImageWidget* MaxRSSILine;
laKeyPadWidget* KeyPad1;
laGradientWidget* GradientWidget2;
laLabelWidget* TimeCountLbl;
laLabelWidget* LabelWidget6;
laWidget* PanelWidget7;
laLabelWidget* LabelWidget28;
laLabelWidget* LabelWidget29;
laLabelWidget* LabelWidget30;
laLabelWidget* LabelWidget31;
laLineWidget* LineaTop0;
laLabelWidget* RaceLapTimesLbl;
laLabelWidget* LapsNumbersLbl;
laLabelWidget* Pilot0TimesLbl;
laLineWidget* Linea1;
laLabelWidget* Pilot1TimesLbl;
laLineWidget* Linea2;
laLabelWidget* Pilot3TimesLbl;
laLabelWidget* Pilot2TimesLbl;
laLineWidget* Linea3;
laLineWidget* Linea4;
laLineWidget* Linea5;
laLineWidget* Linea6;
laLineWidget* Linea7;
laLabelWidget* MSegLbl;
laLineWidget* Linea8;
laLineWidget* LineaVertical;
laButtonWidget* StartStopRaceBtn;
laButtonWidget* ButtonWidget29;
laButtonWidget* ShowFinalStatsBtn;
laLabelWidget* TotalPilot0Lbl;
laLabelWidget* TotalPilot1Lbl;
laLabelWidget* TotalPilot2Lbl;
laLabelWidget* TotalPilot3Lbl;
laButtonWidget* ShowEnablePilotsBtn;
laWidget* FinalStatsPanel;
laRectangleWidget* RectangleWidget2;
laRectangleWidget* RectangleWidget3;
laLabelWidget* _1PlaceLbl;
laRectangleWidget* RectangleWidget4;
laLabelWidget* _2PlaceLbl;
laLabelWidget* _3PlaceLbl;
laButtonWidget* CloseFinalStatsBtn;
laLabelWidget* _2TimeLbl;
laLabelWidget* _1TimeLbl;
laLabelWidget* _3TimeLbl;
laLabelWidget* _4PlaceLbl;
laLabelWidget* _4TimeLbl;
laWidget* EnablePilotsPanel;
laButtonWidget* Pilot0EnableBtn;
laButtonWidget* Pilot1EnableBtn;
laButtonWidget* Pilot2EnableBtn;
laButtonWidget* Pilot3EnableBtn;
laButtonWidget* CloseEnableBtn;
laLabelWidget* LabelWidget;
laLabelWidget* Channel0Lbl;
laLabelWidget* Channel1Lbl;
laLabelWidget* Channel2Lbl;
laLabelWidget* Channel3Lbl;
laGradientWidget* GradientWidget23;
laWidget* PanelWidget24;
laLabelWidget* wndCaptionRaceParam;
laButtonWidget* ExitRaceParamBtn;
laButtonWidget* SaveRaceParamBtn;
laGroupBoxWidget* GroupBoxWidget34;
laRadioButtonWidget* CumulativeTimeChk;
laRadioButtonWidget* EachRaceTimeChk;
laGroupBoxWidget* GroupBoxWidget38;
laButtonWidget* SkipFirstLapBtn;
laLabelWidget* LapNumberConfLbl;
laButtonWidget* LapUpBtn;
laButtonWidget* LapDownBtn;
laLabelWidget* LabelWidget45;
laLabelWidget* LabelWidget8;
laButtonWidget* TLapDownBtn;
laLabelWidget* TVueltaLbl;
laButtonWidget* TLapUpBtn;
laLabelWidget* LabelWidget39;
laLabelWidget* LabelWidget11;
laButtonWidget* StartBeepsDownBtn;
laLabelWidget* StartBeepsLbl;
laButtonWidget* StartBeepsUpBtn;
laGradientWidget* GradientWidget10;
laWidget* PanelWidget11;
laLabelWidget* LabelWidget14;
laButtonWidget* ButtonWidget15;
laButtonWidget* StartListeningUSARTBtn;
laListWidget* ATCommandsLst;
laButtonWidget* SendATCommandBtn;
laTextFieldWidget* USART_TextLbl;
laButtonWidget* ClearUSART_TextBtn;


static void ScreenCreate_MainWnd(laScreen* screen);
static void ScreenCreate_TouchCalibrationWnd(laScreen* screen);
static void ScreenCreate_ConfigMainWnd(laScreen* screen);
static void ScreenCreate_ConfigPilotWnd(laScreen* screen);
static void ScreenCreate_ConfigRaceLevelsWnd(laScreen* screen);
static void ScreenCreate_ConfigThrLevelWnd(laScreen* screen);
static void ScreenCreate_RaceWnd(laScreen* screen);
static void ScreenCreate_RaceConfigWnd(laScreen* screen);
static void ScreenCreate_WifiTesting(laScreen* screen);


int32_t libaria_initialize(void)
{
    laScreen* screen;

    laScheme_Initialize(&defaultScheme, GFX_COLOR_MODE_RGB_565);
    defaultScheme.base = 0xC67A;
    defaultScheme.highlight = 0xC67A;
    defaultScheme.highlightLight = 0xFFFF;
    defaultScheme.shadow = 0x8410;
    defaultScheme.shadowDark = 0x4208;
    defaultScheme.foreground = 0x0;
    defaultScheme.foregroundInactive = 0xD71C;
    defaultScheme.foregroundDisabled = 0x8410;
    defaultScheme.background = 0xFFFF;
    defaultScheme.backgroundInactive = 0xD71C;
    defaultScheme.backgroundDisabled = 0xC67A;
    defaultScheme.text = 0x0;
    defaultScheme.textHighlight = 0x1F;
    defaultScheme.textHighlightText = 0xFFFF;
    defaultScheme.textInactive = 0xD71C;
    defaultScheme.textDisabled = 0x8C92;

    laScheme_Initialize(&CircleSchema, GFX_COLOR_MODE_RGB_565);
    CircleSchema.base = 0x7E0;
    CircleSchema.highlight = 0xC67A;
    CircleSchema.highlightLight = 0xBDF7;
    CircleSchema.shadow = 0x8410;
    CircleSchema.shadowDark = 0x8410;
    CircleSchema.foreground = 0x4208;
    CircleSchema.foregroundInactive = 0x9CFD;
    CircleSchema.foregroundDisabled = 0x8410;
    CircleSchema.background = 0xF800;
    CircleSchema.backgroundInactive = 0xD71C;
    CircleSchema.backgroundDisabled = 0xC67A;
    CircleSchema.text = 0x0;
    CircleSchema.textHighlight = 0xF800;
    CircleSchema.textHighlightText = 0xFFFF;
    CircleSchema.textInactive = 0xD71C;
    CircleSchema.textDisabled = 0x8C92;

    laScheme_Initialize(&ProgressBarSchema, GFX_COLOR_MODE_RGB_565);
    ProgressBarSchema.base = 0xFFFF;
    ProgressBarSchema.highlight = 0xC67A;
    ProgressBarSchema.highlightLight = 0xFFFF;
    ProgressBarSchema.shadow = 0x8410;
    ProgressBarSchema.shadowDark = 0x4208;
    ProgressBarSchema.foreground = 0x7E0;
    ProgressBarSchema.foregroundInactive = 0xD71C;
    ProgressBarSchema.foregroundDisabled = 0xFDF7;
    ProgressBarSchema.background = 0xFFFF;
    ProgressBarSchema.backgroundInactive = 0xD71C;
    ProgressBarSchema.backgroundDisabled = 0x94B2;
    ProgressBarSchema.text = 0x0;
    ProgressBarSchema.textHighlight = 0x7E0;
    ProgressBarSchema.textHighlightText = 0x17;
    ProgressBarSchema.textInactive = 0xD71C;
    ProgressBarSchema.textDisabled = 0x8C92;

    laScheme_Initialize(&BackGrowndGradient, GFX_COLOR_MODE_RGB_565);
    BackGrowndGradient.base = 0xC67A;
    BackGrowndGradient.highlight = 0xC67A;
    BackGrowndGradient.highlightLight = 0xFFFF;
    BackGrowndGradient.shadow = 0x8410;
    BackGrowndGradient.shadowDark = 0x4208;
    BackGrowndGradient.foreground = 0x818;
    BackGrowndGradient.foregroundInactive = 0x9CFD;
    BackGrowndGradient.foregroundDisabled = 0x8410;
    BackGrowndGradient.background = 0xFFFF;
    BackGrowndGradient.backgroundInactive = 0xD71C;
    BackGrowndGradient.backgroundDisabled = 0xC67A;
    BackGrowndGradient.text = 0x0;
    BackGrowndGradient.textHighlight = 0x1F;
    BackGrowndGradient.textHighlightText = 0xFFFF;
    BackGrowndGradient.textInactive = 0xD71C;
    BackGrowndGradient.textDisabled = 0x8C92;

    laScheme_Initialize(&BigTextSchema, GFX_COLOR_MODE_RGB_565);
    BigTextSchema.base = 0xC67A;
    BigTextSchema.highlight = 0xC67A;
    BigTextSchema.highlightLight = 0xFFFF;
    BigTextSchema.shadow = 0x8410;
    BigTextSchema.shadowDark = 0x4208;
    BigTextSchema.foreground = 0x0;
    BigTextSchema.foregroundInactive = 0xD71C;
    BigTextSchema.foregroundDisabled = 0x8410;
    BigTextSchema.background = 0xFFFF;
    BigTextSchema.backgroundInactive = 0xD71C;
    BigTextSchema.backgroundDisabled = 0xC67A;
    BigTextSchema.text = 0xFFFF;
    BigTextSchema.textHighlight = 0x1F;
    BigTextSchema.textHighlightText = 0xFFFF;
    BigTextSchema.textInactive = 0xD71C;
    BigTextSchema.textDisabled = 0x8C92;

    laScheme_Initialize(&BlackGradient, GFX_COLOR_MODE_RGB_565);
    BlackGradient.base = 0xC67A;
    BlackGradient.highlight = 0xC67A;
    BlackGradient.highlightLight = 0xFFFF;
    BlackGradient.shadow = 0x8410;
    BlackGradient.shadowDark = 0x4208;
    BlackGradient.foreground = 0x0;
    BlackGradient.foregroundInactive = 0x0;
    BlackGradient.foregroundDisabled = 0x8410;
    BlackGradient.background = 0xFFFF;
    BlackGradient.backgroundInactive = 0xD71C;
    BlackGradient.backgroundDisabled = 0xC67A;
    BlackGradient.text = 0x0;
    BlackGradient.textHighlight = 0x1F;
    BlackGradient.textHighlightText = 0xFFFF;
    BlackGradient.textInactive = 0xD71C;
    BlackGradient.textDisabled = 0x8C92;

    laScheme_Initialize(&Primitives, GFX_COLOR_MODE_RGB_565);
    Primitives.base = 0xC67A;
    Primitives.highlight = 0xC67A;
    Primitives.highlightLight = 0xFFFF;
    Primitives.shadow = 0x8410;
    Primitives.shadowDark = 0x4208;
    Primitives.foreground = 0xFFFF;
    Primitives.foregroundInactive = 0xD71C;
    Primitives.foregroundDisabled = 0x8410;
    Primitives.background = 0xFFFF;
    Primitives.backgroundInactive = 0xD71C;
    Primitives.backgroundDisabled = 0xC67A;
    Primitives.text = 0x0;
    Primitives.textHighlight = 0x1F;
    Primitives.textHighlightText = 0xFFFF;
    Primitives.textInactive = 0xD71C;
    Primitives.textDisabled = 0x8C92;

    laScheme_Initialize(&ButtonsNormal, GFX_COLOR_MODE_RGB_565);
    ButtonsNormal.base = 0xC67A;
    ButtonsNormal.highlight = 0xC67A;
    ButtonsNormal.highlightLight = 0xFFFF;
    ButtonsNormal.shadow = 0x8410;
    ButtonsNormal.shadowDark = 0x4208;
    ButtonsNormal.foreground = 0x0;
    ButtonsNormal.foregroundInactive = 0xD71C;
    ButtonsNormal.foregroundDisabled = 0x8410;
    ButtonsNormal.background = 0x87F0;
    ButtonsNormal.backgroundInactive = 0xD71C;
    ButtonsNormal.backgroundDisabled = 0xC67A;
    ButtonsNormal.text = 0x0;
    ButtonsNormal.textHighlight = 0x1F;
    ButtonsNormal.textHighlightText = 0xFFFF;
    ButtonsNormal.textInactive = 0xD71C;
    ButtonsNormal.textDisabled = 0x8C92;

    laScheme_Initialize(&WindowCaption, GFX_COLOR_MODE_RGB_565);
    WindowCaption.base = 0x37E9;
    WindowCaption.highlight = 0xC67A;
    WindowCaption.highlightLight = 0xFFFF;
    WindowCaption.shadow = 0x8410;
    WindowCaption.shadowDark = 0x4208;
    WindowCaption.foreground = 0x0;
    WindowCaption.foregroundInactive = 0xD71C;
    WindowCaption.foregroundDisabled = 0x8410;
    WindowCaption.background = 0xFFE0;
    WindowCaption.backgroundInactive = 0xE4E7;
    WindowCaption.backgroundDisabled = 0x2690;
    WindowCaption.text = 0xFFFF;
    WindowCaption.textHighlight = 0xFFFF;
    WindowCaption.textHighlightText = 0xFFFF;
    WindowCaption.textInactive = 0xD71C;
    WindowCaption.textDisabled = 0x8C92;

    laScheme_Initialize(&KeyPadNumberScheme, GFX_COLOR_MODE_RGB_565);
    KeyPadNumberScheme.base = 0xC67A;
    KeyPadNumberScheme.highlight = 0xC67A;
    KeyPadNumberScheme.highlightLight = 0xFFFF;
    KeyPadNumberScheme.shadow = 0x8410;
    KeyPadNumberScheme.shadowDark = 0x4208;
    KeyPadNumberScheme.foreground = 0x0;
    KeyPadNumberScheme.foregroundInactive = 0xD71C;
    KeyPadNumberScheme.foregroundDisabled = 0x8410;
    KeyPadNumberScheme.background = 0x87F0;
    KeyPadNumberScheme.backgroundInactive = 0xD71C;
    KeyPadNumberScheme.backgroundDisabled = 0xC67A;
    KeyPadNumberScheme.text = 0x0;
    KeyPadNumberScheme.textHighlight = 0x1F;
    KeyPadNumberScheme.textHighlightText = 0xFFFF;
    KeyPadNumberScheme.textInactive = 0xD71C;
    KeyPadNumberScheme.textDisabled = 0x8C92;

    GFX_Set(GFXF_DRAW_PIPELINE_MODE, GFX_PIPELINE_GCUGPU);
    laContext_SetStringTable(&stringTable);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_MainWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_TouchCalibrationWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_ConfigMainWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_ConfigPilotWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_ConfigRaceLevelsWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_ConfigThrLevelWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_RaceWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_RaceConfigWnd);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_WifiTesting);
    laContext_AddScreen(screen);

    laContext_SetPreemptionLevel(LA_PREEMPTION_LEVEL_1);
    laContext_SetActiveScreen(0);

	return 0;
}

static void ScreenCreate_MainWnd(laScreen* screen)
{
    laLayer* layer0;

    laScreen_SetShowEventCallback(screen, &MainWnd_ShowEvent);

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget1 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget1, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget1, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget1, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget1, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget1, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget1);

    LabelWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget2, -16, -5);
    laWidget_SetSize((laWidget*)LabelWidget2, 269, 41);
    laWidget_SetScheme((laWidget*)LabelWidget2, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)LabelWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget2, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget2, laString_CreateFromID(string_MainWndCaption));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget2);

    PanelWidget4 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget4, 0, 41);
    laWidget_SetSize((laWidget*)PanelWidget4, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget4, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget4, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget4);

    MainOKBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)MainOKBtn, 15, 272);
    laWidget_SetSize((laWidget*)MainOKBtn, 80, 33);
    laWidget_SetScheme((laWidget*)MainOKBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)MainOKBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)MainOKBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(MainOKBtn, laString_CreateFromID(string_ButtonOK));
    laButtonWidget_SetReleasedEventCallback(MainOKBtn, &MainOKBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)MainOKBtn);

    MainCancelBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)MainCancelBtn, 146, 272);
    laWidget_SetSize((laWidget*)MainCancelBtn, 79, 33);
    laWidget_SetScheme((laWidget*)MainCancelBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)MainCancelBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)MainCancelBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(MainCancelBtn, laString_CreateFromID(string_ButtonCancel));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MainCancelBtn);

    StartRaceBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)StartRaceBtn, 15, 50);
    laWidget_SetSize((laWidget*)StartRaceBtn, 63, 45);
    laWidget_SetScheme((laWidget*)StartRaceBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)StartRaceBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StartRaceBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(StartRaceBtn, &FlagsSmall);
    laButtonWidget_SetReleasedImage(StartRaceBtn, &FlagsSmall);
    laButtonWidget_SetReleasedEventCallback(StartRaceBtn, &StartRaceBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)StartRaceBtn);

    EEPromBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)EEPromBtn, 15, 106);
    laWidget_SetSize((laWidget*)EEPromBtn, 63, 50);
    laWidget_SetScheme((laWidget*)EEPromBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)EEPromBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)EEPromBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(EEPromBtn, &PilotSmallJPG);
    laButtonWidget_SetReleasedImage(EEPromBtn, &PilotSmallJPG);
    laButtonWidget_SetReleasedEventCallback(EEPromBtn, &EEPromBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)EEPromBtn);

    ConfigAppBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ConfigAppBtn, 15, 164);
    laWidget_SetSize((laWidget*)ConfigAppBtn, 63, 45);
    laWidget_SetScheme((laWidget*)ConfigAppBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ConfigAppBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ConfigAppBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ConfigAppBtn, &ConfigJPG);
    laButtonWidget_SetReleasedImage(ConfigAppBtn, &ConfigJPG);
    laButtonWidget_SetReleasedEventCallback(ConfigAppBtn, &ConfigAppBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ConfigAppBtn);

    LabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget, 85, 60);
    laWidget_SetSize((laWidget*)LabelWidget, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget, laString_CreateFromID(string_StartRaceStr));
    laLabelWidget_SetHAlignment(LabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget);

    LabelWidget4 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget4, 85, 111);
    laWidget_SetSize((laWidget*)LabelWidget4, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget4, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget4, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget4, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget4, laString_CreateFromID(string_CalibrarVTXStr));
    laLabelWidget_SetHAlignment(LabelWidget4, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget4);

    LabelWidget5 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget5, 85, 171);
    laWidget_SetSize((laWidget*)LabelWidget5, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget5, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget5, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget5, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget5, laString_CreateFromID(string_ConfigBtnStr));
    laLabelWidget_SetHAlignment(LabelWidget5, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget5);

    ButtonWidget1 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget1, 15, 216);
    laWidget_SetSize((laWidget*)ButtonWidget1, 63, 45);
    laWidget_SetScheme((laWidget*)ButtonWidget1, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ButtonWidget1, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ButtonWidget1, &wifi_small);
    laButtonWidget_SetReleasedImage(ButtonWidget1, &wifi_small);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget1, &ButtonWidget1_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget1);

    LabelWidget9 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget9, 86, 225);
    laWidget_SetSize((laWidget*)LabelWidget9, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget9, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget9, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget9, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget9, laString_CreateFromID(string_WiFi_Settings_lbl));
    laLabelWidget_SetHAlignment(LabelWidget9, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget9);

}

static void ScreenCreate_TouchCalibrationWnd(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)GradientWidget, 0, 0, 0, 0);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget);

    TouchWndCaptionPanel = laWidget_New();
    laWidget_SetSize((laWidget*)TouchWndCaptionPanel, 240, 320);
    laWidget_SetScheme((laWidget*)TouchWndCaptionPanel, &CircleSchema);
    laWidget_SetBackgroundType((laWidget*)TouchWndCaptionPanel, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TouchWndCaptionPanel, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)TouchWndCaptionPanel, 0, 0, 0, 0);
    laWidget_AddChild((laWidget*)GradientWidget, TouchWndCaptionPanel);

    TouchCalibrationWndCaption = laLabelWidget_New();
    laWidget_SetSize((laWidget*)TouchCalibrationWndCaption, 240, 34);
    laWidget_SetScheme((laWidget*)TouchCalibrationWndCaption, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)TouchCalibrationWndCaption, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TouchCalibrationWndCaption, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TouchCalibrationWndCaption, laString_CreateFromID(string_TouchConfigWndStr));
    laWidget_AddChild((laWidget*)TouchWndCaptionPanel, (laWidget*)TouchCalibrationWndCaption);

    PanelWidget6 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget6, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget6, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget6, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget6, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)TouchWndCaptionPanel, PanelWidget6);

    TouchOkBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)TouchOkBtn, 15, 272);
    laWidget_SetSize((laWidget*)TouchOkBtn, 80, 33);
    laWidget_SetScheme((laWidget*)TouchOkBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)TouchOkBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)TouchOkBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(TouchOkBtn, laString_CreateFromID(string_TouchStartLbl));
    laWidget_AddChild((laWidget*)TouchWndCaptionPanel, (laWidget*)TouchOkBtn);

    TouchExitBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)TouchExitBtn, 146, 272);
    laWidget_SetSize((laWidget*)TouchExitBtn, 79, 33);
    laWidget_SetScheme((laWidget*)TouchExitBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)TouchExitBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)TouchExitBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(TouchExitBtn, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(TouchExitBtn, &TouchExitBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)TouchWndCaptionPanel, (laWidget*)TouchExitBtn);

    CirclePoint = laCircleWidget_New();
    laWidget_SetPosition((laWidget*)CirclePoint, 37, 67);
    laWidget_SetSize((laWidget*)CirclePoint, 23, 24);
    laWidget_SetVisible((laWidget*)CirclePoint, LA_FALSE);
    laWidget_SetScheme((laWidget*)CirclePoint, &Primitives);
    laWidget_SetBackgroundType((laWidget*)CirclePoint, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CirclePoint, LA_WIDGET_BORDER_NONE);
    laCircleWidget_SetOrigin(CirclePoint, 11, 11);
    laCircleWidget_SetRadius(CirclePoint, 11);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)CirclePoint);

    GreenPointImg = laImageWidget_New();
    laWidget_SetPosition((laWidget*)GreenPointImg, 3, 3);
    laWidget_SetSize((laWidget*)GreenPointImg, 16, 16);
    laWidget_SetBackgroundType((laWidget*)GreenPointImg, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)GreenPointImg, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(GreenPointImg, &PuntoVerde);
    laWidget_AddChild((laWidget*)CirclePoint, (laWidget*)GreenPointImg);

    TouchPointLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TouchPointLbl, 37, 80);
    laWidget_SetSize((laWidget*)TouchPointLbl, 164, 25);
    laWidget_SetScheme((laWidget*)TouchPointLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TouchPointLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TouchPointLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TouchPointLbl, laString_CreateFromID(string_TouchPointStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TouchPointLbl);

    TouchMsg1Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TouchMsg1Lbl, 0, 130);
    laWidget_SetSize((laWidget*)TouchMsg1Lbl, 240, 29);
    laWidget_SetScheme((laWidget*)TouchMsg1Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TouchMsg1Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TouchMsg1Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TouchMsg1Lbl, laString_CreateFromID(string_TouchInstruction1Str));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TouchMsg1Lbl);

    TouchMsg2Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TouchMsg2Lbl, 0, 150);
    laWidget_SetSize((laWidget*)TouchMsg2Lbl, 240, 29);
    laWidget_SetScheme((laWidget*)TouchMsg2Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TouchMsg2Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TouchMsg2Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TouchMsg2Lbl, laString_CreateFromID(string_TouchInstruction2Str));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TouchMsg2Lbl);

}

static void ScreenCreate_ConfigMainWnd(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget3 = laGradientWidget_New();
    laWidget_SetPosition((laWidget*)GradientWidget3, 0, 1);
    laWidget_SetSize((laWidget*)GradientWidget3, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget3, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget3, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget3, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget3, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget3);

    ConfigMainWndLbl = laLabelWidget_New();
    laWidget_SetSize((laWidget*)ConfigMainWndLbl, 240, 34);
    laWidget_SetScheme((laWidget*)ConfigMainWndLbl, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)ConfigMainWndLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ConfigMainWndLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(ConfigMainWndLbl, laString_CreateFromID(string_ConfigWndCaption));
    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ConfigMainWndLbl);

    PanelWidget9 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget9, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget9, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget9, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget9, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)GradientWidget3, PanelWidget9);

    ButtonWidget10 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget10, 146, 272);
    laWidget_SetSize((laWidget*)ButtonWidget10, 79, 33);
    laWidget_SetScheme((laWidget*)ButtonWidget10, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget10, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ButtonWidget10, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget10, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget10, &ButtonWidget10_ReleasedEvent);

    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ButtonWidget10);

    ButtonWidget11 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget11, 15, 272);
    laWidget_SetSize((laWidget*)ButtonWidget11, 80, 33);
    laWidget_SetScheme((laWidget*)ButtonWidget11, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget11, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ButtonWidget11, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget11, laString_CreateFromID(string_DemoWndReadLbl));
    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ButtonWidget11);

    ButtonWidget12 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget12, 15, 45);
    laWidget_SetSize((laWidget*)ButtonWidget12, 55, 45);
    laWidget_SetScheme((laWidget*)ButtonWidget12, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget12, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ButtonWidget12, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ButtonWidget12, &ToolboxSmall);
    laButtonWidget_SetReleasedImage(ButtonWidget12, &ToolboxSmall);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget12, &ButtonWidget12_ReleasedEvent);

    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ButtonWidget12);

    ButtonWidget13 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget13, 15, 90);
    laWidget_SetSize((laWidget*)ButtonWidget13, 55, 45);
    laWidget_SetScheme((laWidget*)ButtonWidget13, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget13, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ButtonWidget13, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ButtonWidget13, &PilotSmallJPG);
    laButtonWidget_SetReleasedImage(ButtonWidget13, &PilotSmallJPG);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget13, &ButtonWidget13_ReleasedEvent);

    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ButtonWidget13);

    ButtonWidget14 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget14, 14, 192);
    laWidget_SetSize((laWidget*)ButtonWidget14, 55, 45);
    laWidget_SetScheme((laWidget*)ButtonWidget14, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget14, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ButtonWidget14, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ButtonWidget14, &ConfigJPG);
    laButtonWidget_SetReleasedImage(ButtonWidget14, &ConfigJPG);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget14, &ButtonWidget14_ReleasedEvent);

    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ButtonWidget14);

    LabelWidget15 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget15, 70, 52);
    laWidget_SetSize((laWidget*)LabelWidget15, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget15, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget15, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget15, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget15, laString_CreateFromID(string_RaceLevels_lbl));
    laLabelWidget_SetHAlignment(LabelWidget15, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)LabelWidget15);

    LabelWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget1, 70, 98);
    laWidget_SetSize((laWidget*)LabelWidget1, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget1, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget1, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget1, laString_CreateFromID(string_ConfigFreqModule_lbl));
    laLabelWidget_SetHAlignment(LabelWidget1, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)LabelWidget1);

    LabelWidget10 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget10, 70, 148);
    laWidget_SetSize((laWidget*)LabelWidget10, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget10, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget10, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget10, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget10, laString_CreateFromID(string_RaceParamStr2));
    laLabelWidget_SetHAlignment(LabelWidget10, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)LabelWidget10);

    ButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget, 15, 138);
    laWidget_SetSize((laWidget*)ButtonWidget, 55, 45);
    laWidget_SetScheme((laWidget*)ButtonWidget, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ButtonWidget, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ButtonWidget, &ConfigJPG);
    laButtonWidget_SetReleasedImage(ButtonWidget, &ConfigJPG);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget, &ButtonWidget_ReleasedEvent);

    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)ButtonWidget);

    LabelWidget7 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget7, 70, 200);
    laWidget_SetSize((laWidget*)LabelWidget7, 154, 25);
    laWidget_SetScheme((laWidget*)LabelWidget7, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget7, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget7, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget7, laString_CreateFromID(string_TouchConfigWndStr));
    laLabelWidget_SetHAlignment(LabelWidget7, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GradientWidget3, (laWidget*)LabelWidget7);

}

static void ScreenCreate_ConfigPilotWnd(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget4 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget4, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget4, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget4, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget4, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget4, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget4);

    LabelWidget16 = laLabelWidget_New();
    laWidget_SetSize((laWidget*)LabelWidget16, 240, 34);
    laWidget_SetScheme((laWidget*)LabelWidget16, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)LabelWidget16, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget16, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget16, laString_CreateFromID(string_ConfigFreqModule_lbl));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget16);

    PanelWidget = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget);

    ExitBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ExitBtn, 146, 272);
    laWidget_SetSize((laWidget*)ExitBtn, 79, 33);
    laWidget_SetScheme((laWidget*)ExitBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ExitBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ExitBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ExitBtn, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ExitBtn, &ExitBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ExitBtn);

    ReadBtn2 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ReadBtn2, 15, 272);
    laWidget_SetSize((laWidget*)ReadBtn2, 80, 33);
    laWidget_SetScheme((laWidget*)ReadBtn2, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ReadBtn2, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ReadBtn2, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ReadBtn2, laString_CreateFromID(string_DemoWndReadLbl));
    laButtonWidget_SetReleasedEventCallback(ReadBtn2, &ReadBtn2_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ReadBtn2);

    LabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget, 10, 50);
    laWidget_SetSize((laWidget*)LabelWidget, 54, 25);
    laWidget_SetScheme((laWidget*)LabelWidget, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget, laString_CreateFromID(string_PilotoLbl));
    laLabelWidget_SetHAlignment(LabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget);

    ModuleEdit = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)ModuleEdit, 79, 45);
    laWidget_SetSize((laWidget*)ModuleEdit, 85, 35);
    laWidget_SetScheme((laWidget*)ModuleEdit, &defaultScheme);
    laWidget_SetBackgroundType((laWidget*)ModuleEdit, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ModuleEdit, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetCursorEnabled(ModuleEdit, LA_TRUE);
    laTextFieldWidget_SetClearOnFirstEdit(ModuleEdit, LA_FALSE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ModuleEdit);

    ModuleDropDownBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ModuleDropDownBtn, 165, 45);
    laWidget_SetSize((laWidget*)ModuleDropDownBtn, 36, 36);
    laWidget_SetBackgroundType((laWidget*)ModuleDropDownBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ModuleDropDownBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ModuleDropDownBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(ModuleDropDownBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ModuleDropDownBtn);

    GroupBoxWidget2 = laGroupBoxWidget_New();
    laWidget_SetPosition((laWidget*)GroupBoxWidget2, 3, 96);
    laWidget_SetSize((laWidget*)GroupBoxWidget2, 235, 169);
    laWidget_SetBackgroundType((laWidget*)GroupBoxWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)GroupBoxWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupBoxWidget2);

    BandEdit = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)BandEdit, 101, 9);
    laWidget_SetSize((laWidget*)BandEdit, 95, 29);
    laWidget_SetScheme((laWidget*)BandEdit, &defaultScheme);
    laWidget_SetBackgroundType((laWidget*)BandEdit, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)BandEdit, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetCursorEnabled(BandEdit, LA_TRUE);
    laTextFieldWidget_SetClearOnFirstEdit(BandEdit, LA_FALSE);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)BandEdit);

    LabelWidget3 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget3, 10, 15);
    laWidget_SetSize((laWidget*)LabelWidget3, 62, 25);
    laWidget_SetScheme((laWidget*)LabelWidget3, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget3, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget3, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget3, laString_CreateFromID(string_Banda_str));
    laLabelWidget_SetHAlignment(LabelWidget3, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)LabelWidget3);

    ChannelEdit = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)ChannelEdit, 101, 55);
    laWidget_SetSize((laWidget*)ChannelEdit, 95, 29);
    laWidget_SetScheme((laWidget*)ChannelEdit, &defaultScheme);
    laWidget_SetBackgroundType((laWidget*)ChannelEdit, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ChannelEdit, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetCursorEnabled(ChannelEdit, LA_TRUE);
    laTextFieldWidget_SetClearOnFirstEdit(ChannelEdit, LA_FALSE);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)ChannelEdit);

    ChannelLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ChannelLbl, 12, 60);
    laWidget_SetSize((laWidget*)ChannelLbl, 58, 25);
    laWidget_SetScheme((laWidget*)ChannelLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)ChannelLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ChannelLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(ChannelLbl, laString_CreateFromID(string_Channel_str));
    laLabelWidget_SetHAlignment(ChannelLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)ChannelLbl);

    ChannelUpBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ChannelUpBtn, 196, 56);
    laWidget_SetSize((laWidget*)ChannelUpBtn, 30, 30);
    laWidget_SetBackgroundType((laWidget*)ChannelUpBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ChannelUpBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ChannelUpBtn, &ArrowUp);
    laButtonWidget_SetReleasedImage(ChannelUpBtn, &ArrowUp);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)ChannelUpBtn);

    ChannelDownBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ChannelDownBtn, 72, 56);
    laWidget_SetSize((laWidget*)ChannelDownBtn, 30, 30);
    laWidget_SetBackgroundType((laWidget*)ChannelDownBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ChannelDownBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ChannelDownBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(ChannelDownBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)ChannelDownBtn);

    BandUpBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)BandUpBtn, 196, 11);
    laWidget_SetSize((laWidget*)BandUpBtn, 30, 30);
    laWidget_SetBackgroundType((laWidget*)BandUpBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)BandUpBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(BandUpBtn, &ArrowUp);
    laButtonWidget_SetReleasedImage(BandUpBtn, &ArrowUp);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)BandUpBtn);

    BandDownBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)BandDownBtn, 72, 11);
    laWidget_SetSize((laWidget*)BandDownBtn, 30, 30);
    laWidget_SetBackgroundType((laWidget*)BandDownBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)BandDownBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(BandDownBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(BandDownBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)GroupBoxWidget2, (laWidget*)BandDownBtn);

    SendFreqBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)SendFreqBtn, 10, 219);
    laWidget_SetSize((laWidget*)SendFreqBtn, 125, 37);
    laWidget_SetScheme((laWidget*)SendFreqBtn, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)SendFreqBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)SendFreqBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(SendFreqBtn, laString_CreateFromID(string_SaveStr));
    laButtonWidget_SetPressedImage(SendFreqBtn, &chip_32);
    laButtonWidget_SetReleasedImage(SendFreqBtn, &chip_32);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)SendFreqBtn);

    RSSI_lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RSSI_lbl, 79, 185);
    laWidget_SetSize((laWidget*)RSSI_lbl, 90, 25);
    laWidget_SetScheme((laWidget*)RSSI_lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI_lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RSSI_lbl, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI_lbl);

    LabelWidget12 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget12, 164, 207);
    laWidget_SetSize((laWidget*)LabelWidget12, 51, 25);
    laWidget_SetScheme((laWidget*)LabelWidget12, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget12, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget12, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget12, laString_CreateFromID(string_FrecuenciaStr));
    laLabelWidget_SetHAlignment(LabelWidget12, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget12);

    FreqLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)FreqLbl, 145, 231);
    laWidget_SetSize((laWidget*)FreqLbl, 85, 25);
    laWidget_SetScheme((laWidget*)FreqLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)FreqLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)FreqLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(FreqLbl, laString_CreateFromID(string_POT_VALUE_lbl));
    laLabelWidget_SetHAlignment(FreqLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)FreqLbl);

    LabelWidget13 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget13, 18, 185);
    laWidget_SetSize((laWidget*)LabelWidget13, 45, 25);
    laWidget_SetScheme((laWidget*)LabelWidget13, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget13, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget13, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget13, laString_CreateFromID(string_RSSI_Str));
    laLabelWidget_SetHAlignment(LabelWidget13, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget13);

    ModuloList = laListWidget_New();
    laWidget_SetPosition((laWidget*)ModuloList, 75, 80);
    laWidget_SetSize((laWidget*)ModuloList, 110, 140);
    laWidget_SetVisible((laWidget*)ModuloList, LA_FALSE);
    laWidget_SetScheme((laWidget*)ModuloList, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)ModuloList, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ModuloList, LA_WIDGET_BORDER_BEVEL);
    laListWidget_SetSelectionMode(ModuloList, LA_LIST_WIDGET_SELECTION_MODE_SINGLE);
    laListWidget_SetAlignment(ModuloList, LA_HALIGN_RIGHT);
    laListWidget_SetIconMargin(ModuloList, 5);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ModuloList);

}

static void ScreenCreate_ConfigRaceLevelsWnd(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget19 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget19, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget19, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget19, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget19, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget19, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget19);

    LabelWidget20 = laLabelWidget_New();
    laWidget_SetSize((laWidget*)LabelWidget20, 240, 34);
    laWidget_SetScheme((laWidget*)LabelWidget20, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)LabelWidget20, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget20, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget20, laString_CreateFromID(string_RaceLevels_lbl));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget20);

    PanelWidget21 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget21, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget21, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget21, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget21, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget21);

    ExitConfigLevelBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ExitConfigLevelBtn, 146, 272);
    laWidget_SetSize((laWidget*)ExitConfigLevelBtn, 79, 33);
    laWidget_SetScheme((laWidget*)ExitConfigLevelBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ExitConfigLevelBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ExitConfigLevelBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ExitConfigLevelBtn, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ExitConfigLevelBtn, &ExitConfigLevelBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ExitConfigLevelBtn);

    InitCalibrationRSSILevels_Btn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)InitCalibrationRSSILevels_Btn, 15, 272);
    laWidget_SetSize((laWidget*)InitCalibrationRSSILevels_Btn, 80, 33);
    laWidget_SetScheme((laWidget*)InitCalibrationRSSILevels_Btn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)InitCalibrationRSSILevels_Btn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)InitCalibrationRSSILevels_Btn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(InitCalibrationRSSILevels_Btn, laString_CreateFromID(string_TouchStartLbl));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)InitCalibrationRSSILevels_Btn);

    Pilot0Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot0Lbl, 4, 71);
    laWidget_SetSize((laWidget*)Pilot0Lbl, 74, 25);
    laWidget_SetScheme((laWidget*)Pilot0Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot0Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot0Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot0Lbl, laString_CreateFromID(string_Piloto1Str));
    laLabelWidget_SetHAlignment(Pilot0Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot0Lbl);

    Band0Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Band0Lbl, 85, 70);
    laWidget_SetSize((laWidget*)Band0Lbl, 42, 25);
    laWidget_SetScheme((laWidget*)Band0Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Band0Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Band0Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Band0Lbl, laString_CreateFromID(string_BandInitStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Band0Lbl);

    RSSI0Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RSSI0Lbl, 124, 70);
    laWidget_SetSize((laWidget*)RSSI0Lbl, 45, 25);
    laWidget_SetScheme((laWidget*)RSSI0Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI0Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RSSI0Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(RSSI0Lbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI0Lbl);

    RSSI0Bar = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)RSSI0Bar, 25, 100);
    laWidget_SetSize((laWidget*)RSSI0Bar, 196, 5);
    laWidget_SetScheme((laWidget*)RSSI0Bar, &ProgressBarSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI0Bar, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RSSI0Bar, LA_WIDGET_BORDER_NONE);
    laProgressBarWidget_SetValue(RSSI0Bar, 75);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI0Bar);

    MinRSSI0Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MinRSSI0Line, 29, 108);
    laWidget_SetSize((laWidget*)MinRSSI0Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MinRSSI0Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MinRSSI0Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MinRSSI0Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MinRSSI0Line);

    MaxRSSI0Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MaxRSSI0Line, 165, 108);
    laWidget_SetSize((laWidget*)MaxRSSI0Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MaxRSSI0Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MaxRSSI0Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MaxRSSI0Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MaxRSSI0Line);

    Pilot1Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot1Lbl, 4, 118);
    laWidget_SetSize((laWidget*)Pilot1Lbl, 73, 25);
    laWidget_SetScheme((laWidget*)Pilot1Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot1Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot1Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot1Lbl, laString_CreateFromID(string_Piloto2Str));
    laLabelWidget_SetHAlignment(Pilot1Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot1Lbl);

    Band1Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Band1Lbl, 85, 117);
    laWidget_SetSize((laWidget*)Band1Lbl, 42, 25);
    laWidget_SetScheme((laWidget*)Band1Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Band1Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Band1Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Band1Lbl, laString_CreateFromID(string_BandInitStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Band1Lbl);

    RSSI1Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RSSI1Lbl, 124, 117);
    laWidget_SetSize((laWidget*)RSSI1Lbl, 45, 25);
    laWidget_SetScheme((laWidget*)RSSI1Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI1Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RSSI1Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(RSSI1Lbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI1Lbl);

    RSSI1Bar = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)RSSI1Bar, 25, 147);
    laWidget_SetSize((laWidget*)RSSI1Bar, 196, 5);
    laWidget_SetScheme((laWidget*)RSSI1Bar, &ProgressBarSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI1Bar, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RSSI1Bar, LA_WIDGET_BORDER_NONE);
    laProgressBarWidget_SetValue(RSSI1Bar, 75);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI1Bar);

    MinRSSI1Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MinRSSI1Line, 29, 154);
    laWidget_SetSize((laWidget*)MinRSSI1Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MinRSSI1Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MinRSSI1Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MinRSSI1Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MinRSSI1Line);

    MaxRSSI1Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MaxRSSI1Line, 165, 154);
    laWidget_SetSize((laWidget*)MaxRSSI1Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MaxRSSI1Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MaxRSSI1Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MaxRSSI1Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MaxRSSI1Line);

    Pilot2Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot2Lbl, 4, 168);
    laWidget_SetSize((laWidget*)Pilot2Lbl, 72, 25);
    laWidget_SetScheme((laWidget*)Pilot2Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot2Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot2Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot2Lbl, laString_CreateFromID(string_Piloto3Str));
    laLabelWidget_SetHAlignment(Pilot2Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot2Lbl);

    Band2Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Band2Lbl, 85, 167);
    laWidget_SetSize((laWidget*)Band2Lbl, 42, 25);
    laWidget_SetScheme((laWidget*)Band2Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Band2Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Band2Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Band2Lbl, laString_CreateFromID(string_BandInitStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Band2Lbl);

    RSSI2Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RSSI2Lbl, 124, 167);
    laWidget_SetSize((laWidget*)RSSI2Lbl, 45, 25);
    laWidget_SetScheme((laWidget*)RSSI2Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI2Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RSSI2Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(RSSI2Lbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI2Lbl);

    RSSI2Bar = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)RSSI2Bar, 25, 197);
    laWidget_SetSize((laWidget*)RSSI2Bar, 196, 5);
    laWidget_SetScheme((laWidget*)RSSI2Bar, &ProgressBarSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI2Bar, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RSSI2Bar, LA_WIDGET_BORDER_NONE);
    laProgressBarWidget_SetValue(RSSI2Bar, 75);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI2Bar);

    MinRSSI2Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MinRSSI2Line, 28, 204);
    laWidget_SetSize((laWidget*)MinRSSI2Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MinRSSI2Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MinRSSI2Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MinRSSI2Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MinRSSI2Line);

    MaxRSSI2Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MaxRSSI2Line, 164, 204);
    laWidget_SetSize((laWidget*)MaxRSSI2Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MaxRSSI2Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MaxRSSI2Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MaxRSSI2Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MaxRSSI2Line);

    Pilot4Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot4Lbl, 4, 218);
    laWidget_SetSize((laWidget*)Pilot4Lbl, 77, 25);
    laWidget_SetScheme((laWidget*)Pilot4Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot4Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot4Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot4Lbl, laString_CreateFromID(string_Piloto4Str));
    laLabelWidget_SetHAlignment(Pilot4Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot4Lbl);

    Band3Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Band3Lbl, 85, 217);
    laWidget_SetSize((laWidget*)Band3Lbl, 42, 25);
    laWidget_SetScheme((laWidget*)Band3Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Band3Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Band3Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Band3Lbl, laString_CreateFromID(string_BandInitStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Band3Lbl);

    RSSI3Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RSSI3Lbl, 124, 217);
    laWidget_SetSize((laWidget*)RSSI3Lbl, 45, 25);
    laWidget_SetScheme((laWidget*)RSSI3Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI3Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RSSI3Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(RSSI3Lbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI3Lbl);

    RSSI3Bar = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)RSSI3Bar, 25, 247);
    laWidget_SetSize((laWidget*)RSSI3Bar, 196, 5);
    laWidget_SetScheme((laWidget*)RSSI3Bar, &ProgressBarSchema);
    laWidget_SetBackgroundType((laWidget*)RSSI3Bar, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RSSI3Bar, LA_WIDGET_BORDER_NONE);
    laProgressBarWidget_SetValue(RSSI3Bar, 75);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSI3Bar);

    MinRSSI3Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MinRSSI3Line, 25, 255);
    laWidget_SetSize((laWidget*)MinRSSI3Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MinRSSI3Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MinRSSI3Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MinRSSI3Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MinRSSI3Line);

    MaxRSSI3Line = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MaxRSSI3Line, 161, 255);
    laWidget_SetSize((laWidget*)MaxRSSI3Line, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MaxRSSI3Line, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MaxRSSI3Line, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MaxRSSI3Line, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MaxRSSI3Line);

    StatusLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)StatusLbl, 28, 36);
    laWidget_SetSize((laWidget*)StatusLbl, 197, 25);
    laWidget_SetScheme((laWidget*)StatusLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)StatusLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StatusLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(StatusLbl, laString_CreateFromID(string_EstadoStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)StatusLbl);

    Pilot0Enable = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot0Enable, 174, 72);
    laWidget_SetSize((laWidget*)Pilot0Enable, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot0Enable, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot0Enable, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot0Enable, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot0Enable, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot0Enable, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot0Enable, 0);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot0Enable);

    Pilot1Enable = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot1Enable, 174, 119);
    laWidget_SetSize((laWidget*)Pilot1Enable, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot1Enable, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot1Enable, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot1Enable, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot1Enable, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot1Enable, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot1Enable, 0);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot1Enable);

    Pilot2Enable = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot2Enable, 174, 169);
    laWidget_SetSize((laWidget*)Pilot2Enable, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot2Enable, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot2Enable, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot2Enable, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot2Enable, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot2Enable, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot2Enable, 0);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot2Enable);

    Pilot3Enable = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot3Enable, 174, 219);
    laWidget_SetSize((laWidget*)Pilot3Enable, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot3Enable, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot3Enable, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot3Enable, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot3Enable, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot3Enable, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot3Enable, 0);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot3Enable);

}

static void ScreenCreate_ConfigThrLevelWnd(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget20 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget20, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget20, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget20, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget20, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget20, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget20);

    LabelWidget21 = laLabelWidget_New();
    laWidget_SetSize((laWidget*)LabelWidget21, 240, 34);
    laWidget_SetScheme((laWidget*)LabelWidget21, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)LabelWidget21, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget21, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget21, laString_CreateFromID(string_ConfigSpecificRaceWndCaption));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget21);

    PanelWidget22 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget22, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget22, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget22, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget22, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget22);

    ExitConfigThrLevelBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ExitConfigThrLevelBtn, 146, 272);
    laWidget_SetSize((laWidget*)ExitConfigThrLevelBtn, 79, 33);
    laWidget_SetScheme((laWidget*)ExitConfigThrLevelBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ExitConfigThrLevelBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ExitConfigThrLevelBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ExitConfigThrLevelBtn, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ExitConfigThrLevelBtn, &ExitConfigThrLevelBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ExitConfigThrLevelBtn);

    SaveConfigThrLevelBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)SaveConfigThrLevelBtn, 15, 272);
    laWidget_SetSize((laWidget*)SaveConfigThrLevelBtn, 80, 33);
    laWidget_SetVisible((laWidget*)SaveConfigThrLevelBtn, LA_FALSE);
    laWidget_SetScheme((laWidget*)SaveConfigThrLevelBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)SaveConfigThrLevelBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)SaveConfigThrLevelBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(SaveConfigThrLevelBtn, laString_CreateFromID(string_SaveStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)SaveConfigThrLevelBtn);

    Pilot0Btn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot0Btn, 12, 43);
    laWidget_SetSize((laWidget*)Pilot0Btn, 50, 30);
    laWidget_SetEnabled((laWidget*)Pilot0Btn, LA_FALSE);
    laWidget_SetScheme((laWidget*)Pilot0Btn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)Pilot0Btn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)Pilot0Btn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetToggleable(Pilot0Btn, LA_TRUE);
    laButtonWidget_SetPressed(Pilot0Btn, LA_TRUE);
    laButtonWidget_SetText(Pilot0Btn, laString_CreateFromID(string_Lbl1));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot0Btn);

    Pilot1Btn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot1Btn, 68, 43);
    laWidget_SetSize((laWidget*)Pilot1Btn, 50, 30);
    laWidget_SetScheme((laWidget*)Pilot1Btn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)Pilot1Btn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)Pilot1Btn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetToggleable(Pilot1Btn, LA_TRUE);
    laButtonWidget_SetText(Pilot1Btn, laString_CreateFromID(string_Lbl2));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot1Btn);

    Pilot2Btn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot2Btn, 123, 43);
    laWidget_SetSize((laWidget*)Pilot2Btn, 50, 30);
    laWidget_SetScheme((laWidget*)Pilot2Btn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)Pilot2Btn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)Pilot2Btn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetToggleable(Pilot2Btn, LA_TRUE);
    laButtonWidget_SetText(Pilot2Btn, laString_CreateFromID(string_Lbl3));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot2Btn);

    Pilot3Btn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot3Btn, 179, 43);
    laWidget_SetSize((laWidget*)Pilot3Btn, 50, 30);
    laWidget_SetScheme((laWidget*)Pilot3Btn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)Pilot3Btn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)Pilot3Btn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetToggleable(Pilot3Btn, LA_TRUE);
    laButtonWidget_SetText(Pilot3Btn, laString_CreateFromID(string_Lbl4));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot3Btn);

    GroupBoxWidget30 = laGroupBoxWidget_New();
    laWidget_SetPosition((laWidget*)GroupBoxWidget30, 10, 74);
    laWidget_SetSize((laWidget*)GroupBoxWidget30, 220, 181);
    laWidget_SetScheme((laWidget*)GroupBoxWidget30, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)GroupBoxWidget30, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)GroupBoxWidget30, LA_WIDGET_BORDER_NONE);
    laGroupBoxWidget_SetText(GroupBoxWidget30, laString_CreateFromID(string_RSSIParametersGroupLbl));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupBoxWidget30);

    LabelWidget34 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget34, 12, 36);
    laWidget_SetSize((laWidget*)LabelWidget34, 129, 25);
    laWidget_SetScheme((laWidget*)LabelWidget34, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget34, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget34, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget34, laString_CreateFromID(string_MinRSSIThLbl));
    laLabelWidget_SetHAlignment(LabelWidget34, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget30, (laWidget*)LabelWidget34);

    LabelWidget37 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget37, 11, 71);
    laWidget_SetSize((laWidget*)LabelWidget37, 129, 25);
    laWidget_SetScheme((laWidget*)LabelWidget37, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget37, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget37, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget37, laString_CreateFromID(string_MaxRSSIThLbl));
    laLabelWidget_SetHAlignment(LabelWidget37, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget30, (laWidget*)LabelWidget37);

    MinRSSIThrEdit = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)MinRSSIThrEdit, 153, 36);
    laWidget_SetSize((laWidget*)MinRSSIThrEdit, 56, 25);
    laWidget_SetBackgroundType((laWidget*)MinRSSIThrEdit, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)MinRSSIThrEdit, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetCursorEnabled(MinRSSIThrEdit, LA_TRUE);
    laTextFieldWidget_SetClearOnFirstEdit(MinRSSIThrEdit, LA_FALSE);
    laWidget_AddChild((laWidget*)GroupBoxWidget30, (laWidget*)MinRSSIThrEdit);

    MaxRSSIThrEdit = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)MaxRSSIThrEdit, 153, 71);
    laWidget_SetSize((laWidget*)MaxRSSIThrEdit, 56, 25);
    laWidget_SetBackgroundType((laWidget*)MaxRSSIThrEdit, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)MaxRSSIThrEdit, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetCursorEnabled(MaxRSSIThrEdit, LA_TRUE);
    laTextFieldWidget_SetCursorDelay(MaxRSSIThrEdit, 1000);
    laTextFieldWidget_SetClearOnFirstEdit(MaxRSSIThrEdit, LA_FALSE);
    laWidget_AddChild((laWidget*)GroupBoxWidget30, (laWidget*)MaxRSSIThrEdit);

    RSSILbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RSSILbl, 172, 212);
    laWidget_SetSize((laWidget*)RSSILbl, 54, 25);
    laWidget_SetScheme((laWidget*)RSSILbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)RSSILbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RSSILbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(RSSILbl, laString_CreateFromID(string_Lbl0));
    laLabelWidget_SetHAlignment(RSSILbl, LA_HALIGN_RIGHT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSILbl);

    LabelWidget44 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget44, 136, 212);
    laWidget_SetSize((laWidget*)LabelWidget44, 45, 25);
    laWidget_SetScheme((laWidget*)LabelWidget44, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget44, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget44, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget44, laString_CreateFromID(string_RSSI_Str));
    laLabelWidget_SetHAlignment(LabelWidget44, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget44);

    BandaLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)BandaLbl, 14, 212);
    laWidget_SetSize((laWidget*)BandaLbl, 121, 25);
    laWidget_SetScheme((laWidget*)BandaLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)BandaLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)BandaLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(BandaLbl, laString_CreateFromID(string_Banda_str));
    laLabelWidget_SetHAlignment(BandaLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)BandaLbl);

    RSSIBar = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)RSSIBar, 23, 192);
    laWidget_SetSize((laWidget*)RSSIBar, 196, 5);
    laWidget_SetScheme((laWidget*)RSSIBar, &ProgressBarSchema);
    laWidget_SetBackgroundType((laWidget*)RSSIBar, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RSSIBar, LA_WIDGET_BORDER_NONE);
    laProgressBarWidget_SetValue(RSSIBar, 75);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RSSIBar);

    MinRSSILine = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MinRSSILine, 27, 200);
    laWidget_SetSize((laWidget*)MinRSSILine, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MinRSSILine, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MinRSSILine, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MinRSSILine, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MinRSSILine);

    MaxRSSILine = laImageWidget_New();
    laWidget_SetPosition((laWidget*)MaxRSSILine, 163, 200);
    laWidget_SetSize((laWidget*)MaxRSSILine, 12, 9);
    laWidget_SetBackgroundType((laWidget*)MaxRSSILine, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MaxRSSILine, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(MaxRSSILine, &ArrowUpRed);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MaxRSSILine);

    KeyPad1 = laKeyPadWidget_New(4, 3);
    laWidget_SetPosition((laWidget*)KeyPad1, 260, 180);
    laWidget_SetSize((laWidget*)KeyPad1, 132, 119);
    laWidget_SetScheme((laWidget*)KeyPad1, &KeyPadNumberScheme);
    laWidget_SetBackgroundType((laWidget*)KeyPad1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)KeyPad1, LA_WIDGET_BORDER_BEVEL);
    laKeyPadWidget_SetKeyText(KeyPad1, 0, 0, laString_CreateFromID(string_Lbl1));
    laKeyPadWidget_SetKeyValue(KeyPad1, 0, 0, laString_CreateFromID(string_Lbl1));
    laKeyPadWidget_SetKeyAction(KeyPad1, 0, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 0, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 0, 1, laString_CreateFromID(string_Lbl2));
    laKeyPadWidget_SetKeyValue(KeyPad1, 0, 1, laString_CreateFromID(string_Lbl2));
    laKeyPadWidget_SetKeyAction(KeyPad1, 0, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 0, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 0, 2, laString_CreateFromID(string_Lbl3));
    laKeyPadWidget_SetKeyValue(KeyPad1, 0, 2, laString_CreateFromID(string_Lbl3));
    laKeyPadWidget_SetKeyAction(KeyPad1, 0, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 0, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 1, 0, laString_CreateFromID(string_Lbl4));
    laKeyPadWidget_SetKeyValue(KeyPad1, 1, 0, laString_CreateFromID(string_Lbl4));
    laKeyPadWidget_SetKeyAction(KeyPad1, 1, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 1, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 1, 1, laString_CreateFromID(string_Lbl5));
    laKeyPadWidget_SetKeyValue(KeyPad1, 1, 1, laString_CreateFromID(string_Lbl5));
    laKeyPadWidget_SetKeyAction(KeyPad1, 1, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 1, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 1, 2, laString_CreateFromID(string_Lbl6));
    laKeyPadWidget_SetKeyValue(KeyPad1, 1, 2, laString_CreateFromID(string_Lbl6));
    laKeyPadWidget_SetKeyAction(KeyPad1, 1, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 1, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 2, 0, laString_CreateFromID(string_Lbl7));
    laKeyPadWidget_SetKeyValue(KeyPad1, 2, 0, laString_CreateFromID(string_Lbl7));
    laKeyPadWidget_SetKeyAction(KeyPad1, 2, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 2, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 2, 1, laString_CreateFromID(string_Lbl8));
    laKeyPadWidget_SetKeyValue(KeyPad1, 2, 1, laString_CreateFromID(string_Lbl8));
    laKeyPadWidget_SetKeyAction(KeyPad1, 2, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 2, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 2, 2, laString_CreateFromID(string_Lbl9));
    laKeyPadWidget_SetKeyValue(KeyPad1, 2, 2, laString_CreateFromID(string_Lbl9));
    laKeyPadWidget_SetKeyAction(KeyPad1, 2, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 2, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPad1, 3, 0, LA_KEYPAD_CELL_ACTION_BACKSPACE);
    laKeyPadWidget_SetKeyPressedImage(KeyPad1, 3, 0, &BackSpaceBlue);
    laKeyPadWidget_SetKeyReleasedImage(KeyPad1, 3, 0, &BackSpaceBlue);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 3, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPad1, 3, 1, laString_CreateFromID(string_Lbl0));
    laKeyPadWidget_SetKeyValue(KeyPad1, 3, 1, laString_CreateFromID(string_Lbl0));
    laKeyPadWidget_SetKeyAction(KeyPad1, 3, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 3, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPad1, 3, 2, LA_KEYPAD_CELL_ACTION_ACCEPT);
    laKeyPadWidget_SetKeyPressedImage(KeyPad1, 3, 2, &EnterSmall);
    laKeyPadWidget_SetKeyReleasedImage(KeyPad1, 3, 2, &EnterSmall);
    laKeyPadWidget_SetKeyImagePosition(KeyPad1, 3, 2, LA_RELATIVE_POSITION_BEHIND);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)KeyPad1);

}

static void ScreenCreate_RaceWnd(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget2 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget2, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget2, &BlackGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget2, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget2, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget2, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget2);

    TimeCountLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TimeCountLbl, 82, 27);
    laWidget_SetSize((laWidget*)TimeCountLbl, 61, 25);
    laWidget_SetScheme((laWidget*)TimeCountLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TimeCountLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TimeCountLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TimeCountLbl, laString_CreateFromID(string_StartTimeStr));
    laLabelWidget_SetHAlignment(TimeCountLbl, LA_HALIGN_RIGHT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TimeCountLbl);

    LabelWidget6 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget6, 0, -8);
    laWidget_SetSize((laWidget*)LabelWidget6, 240, 34);
    laWidget_SetScheme((laWidget*)LabelWidget6, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)LabelWidget6, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget6, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget6, laString_CreateFromID(string_RaceStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget6);

    PanelWidget7 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget7, 0, 22);
    laWidget_SetSize((laWidget*)PanelWidget7, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget7, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget7, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget7);

    LabelWidget28 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget28, 22, 46);
    laWidget_SetSize((laWidget*)LabelWidget28, 54, 25);
    laWidget_SetScheme((laWidget*)LabelWidget28, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget28, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget28, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget28, laString_CreateFromID(string_Pilot1Small_str));
    laLabelWidget_SetHAlignment(LabelWidget28, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget28);

    LabelWidget29 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget29, 76, 46);
    laWidget_SetSize((laWidget*)LabelWidget29, 54, 25);
    laWidget_SetScheme((laWidget*)LabelWidget29, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget29, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget29, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget29, laString_CreateFromID(string_Pilot2Small_str));
    laLabelWidget_SetHAlignment(LabelWidget29, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget29);

    LabelWidget30 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget30, 130, 46);
    laWidget_SetSize((laWidget*)LabelWidget30, 54, 25);
    laWidget_SetScheme((laWidget*)LabelWidget30, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget30, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget30, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget30, laString_CreateFromID(string_Pilot3Small_str));
    laLabelWidget_SetHAlignment(LabelWidget30, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget30);

    LabelWidget31 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget31, 184, 46);
    laWidget_SetSize((laWidget*)LabelWidget31, 54, 25);
    laWidget_SetScheme((laWidget*)LabelWidget31, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget31, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget31, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget31, laString_CreateFromID(string_Pilot4Small_str));
    laLabelWidget_SetHAlignment(LabelWidget31, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget31);

    LineaTop0 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)LineaTop0, 25, 66);
    laWidget_SetSize((laWidget*)LineaTop0, 204, 4);
    laWidget_SetScheme((laWidget*)LineaTop0, &Primitives);
    laWidget_SetBackgroundType((laWidget*)LineaTop0, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LineaTop0, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(LineaTop0, 0, 1);
    laLineWidget_SetEndPoint(LineaTop0, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LineaTop0);

    RaceLapTimesLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)RaceLapTimesLbl, 10, 90);
    laWidget_SetSize((laWidget*)RaceLapTimesLbl, 220, 25);
    laWidget_SetBackgroundType((laWidget*)RaceLapTimesLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)RaceLapTimesLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetHAlignment(RaceLapTimesLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RaceLapTimesLbl);

    LapsNumbersLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LapsNumbersLbl, 0, 67);
    laWidget_SetSize((laWidget*)LapsNumbersLbl, 16, 198);
    laWidget_SetScheme((laWidget*)LapsNumbersLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LapsNumbersLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LapsNumbersLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LapsNumbersLbl, laString_CreateFromID(string_RaceNumbersLbl));
    laLabelWidget_SetVAlignment(LapsNumbersLbl, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LapsNumbersLbl);

    Pilot0TimesLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot0TimesLbl, 22, 67);
    laWidget_SetSize((laWidget*)Pilot0TimesLbl, 50, 196);
    laWidget_SetScheme((laWidget*)Pilot0TimesLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot0TimesLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot0TimesLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot0TimesLbl, laString_CreateFromID(string_RaceNumbersInit));
    laLabelWidget_SetVAlignment(Pilot0TimesLbl, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot0TimesLbl);

    Linea1 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea1, 25, 88);
    laWidget_SetSize((laWidget*)Linea1, 204, 4);
    laWidget_SetScheme((laWidget*)Linea1, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea1, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea1, 0, 1);
    laLineWidget_SetEndPoint(Linea1, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea1);

    Pilot1TimesLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot1TimesLbl, 76, 67);
    laWidget_SetSize((laWidget*)Pilot1TimesLbl, 50, 198);
    laWidget_SetScheme((laWidget*)Pilot1TimesLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot1TimesLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot1TimesLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot1TimesLbl, laString_CreateFromID(string_RaceNumbersInit));
    laLabelWidget_SetVAlignment(Pilot1TimesLbl, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot1TimesLbl);

    Linea2 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea2, 25, 110);
    laWidget_SetSize((laWidget*)Linea2, 204, 4);
    laWidget_SetScheme((laWidget*)Linea2, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea2, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea2, 0, 1);
    laLineWidget_SetEndPoint(Linea2, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea2);

    Pilot3TimesLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot3TimesLbl, 184, 67);
    laWidget_SetSize((laWidget*)Pilot3TimesLbl, 50, 196);
    laWidget_SetScheme((laWidget*)Pilot3TimesLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot3TimesLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot3TimesLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot3TimesLbl, laString_CreateFromID(string_RaceNumbersInit));
    laLabelWidget_SetVAlignment(Pilot3TimesLbl, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot3TimesLbl);

    Pilot2TimesLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Pilot2TimesLbl, 130, 67);
    laWidget_SetSize((laWidget*)Pilot2TimesLbl, 50, 196);
    laWidget_SetScheme((laWidget*)Pilot2TimesLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)Pilot2TimesLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot2TimesLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Pilot2TimesLbl, laString_CreateFromID(string_RaceNumbersInit));
    laLabelWidget_SetVAlignment(Pilot2TimesLbl, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Pilot2TimesLbl);

    Linea3 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea3, 25, 132);
    laWidget_SetSize((laWidget*)Linea3, 204, 4);
    laWidget_SetScheme((laWidget*)Linea3, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea3, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea3, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea3, 0, 1);
    laLineWidget_SetEndPoint(Linea3, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea3);

    Linea4 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea4, 25, 154);
    laWidget_SetSize((laWidget*)Linea4, 204, 4);
    laWidget_SetScheme((laWidget*)Linea4, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea4, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea4, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea4, 0, 1);
    laLineWidget_SetEndPoint(Linea4, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea4);

    Linea5 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea5, 25, 176);
    laWidget_SetSize((laWidget*)Linea5, 204, 4);
    laWidget_SetScheme((laWidget*)Linea5, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea5, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea5, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea5, 0, 1);
    laLineWidget_SetEndPoint(Linea5, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea5);

    Linea6 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea6, 25, 198);
    laWidget_SetSize((laWidget*)Linea6, 204, 4);
    laWidget_SetScheme((laWidget*)Linea6, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea6, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea6, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea6, 0, 1);
    laLineWidget_SetEndPoint(Linea6, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea6);

    Linea7 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea7, 25, 220);
    laWidget_SetSize((laWidget*)Linea7, 204, 4);
    laWidget_SetScheme((laWidget*)Linea7, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea7, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea7, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea7, 0, 1);
    laLineWidget_SetEndPoint(Linea7, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea7);

    MSegLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)MSegLbl, 137, 27);
    laWidget_SetSize((laWidget*)MSegLbl, 37, 25);
    laWidget_SetScheme((laWidget*)MSegLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)MSegLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MSegLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(MSegLbl, laString_CreateFromID(string_Lbl0));
    laLabelWidget_SetHAlignment(MSegLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MSegLbl);

    Linea8 = laLineWidget_New();
    laWidget_SetPosition((laWidget*)Linea8, 25, 242);
    laWidget_SetSize((laWidget*)Linea8, 204, 4);
    laWidget_SetScheme((laWidget*)Linea8, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Linea8, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Linea8, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(Linea8, 0, 1);
    laLineWidget_SetEndPoint(Linea8, 240, 1);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Linea8);

    LineaVertical = laLineWidget_New();
    laWidget_SetPosition((laWidget*)LineaVertical, 16, 67);
    laWidget_SetSize((laWidget*)LineaVertical, 5, 190);
    laWidget_SetScheme((laWidget*)LineaVertical, &Primitives);
    laWidget_SetBackgroundType((laWidget*)LineaVertical, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LineaVertical, LA_WIDGET_BORDER_NONE);
    laLineWidget_SetStartPoint(LineaVertical, 1, 1);
    laLineWidget_SetEndPoint(LineaVertical, 1, 300);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LineaVertical);

    StartStopRaceBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)StartStopRaceBtn, 31, 282);
    laWidget_SetSize((laWidget*)StartStopRaceBtn, 76, 33);
    laWidget_SetScheme((laWidget*)StartStopRaceBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)StartStopRaceBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)StartStopRaceBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(StartStopRaceBtn, laString_CreateFromID(string_StartRaceBtnStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)StartStopRaceBtn);

    ButtonWidget29 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget29, 138, 282);
    laWidget_SetSize((laWidget*)ButtonWidget29, 76, 33);
    laWidget_SetScheme((laWidget*)ButtonWidget29, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget29, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ButtonWidget29, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget29, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget29, &ButtonWidget29_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget29);

    ShowFinalStatsBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ShowFinalStatsBtn, 197, 30);
    laWidget_SetSize((laWidget*)ShowFinalStatsBtn, 24, 21);
    laWidget_SetBackgroundType((laWidget*)ShowFinalStatsBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ShowFinalStatsBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ShowFinalStatsBtn, &ArrowUpRed);
    laButtonWidget_SetReleasedImage(ShowFinalStatsBtn, &ArrowUpRed);
    laButtonWidget_SetReleasedEventCallback(ShowFinalStatsBtn, &ShowFinalStatsBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ShowFinalStatsBtn);

    TotalPilot0Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TotalPilot0Lbl, 14, 256);
    laWidget_SetSize((laWidget*)TotalPilot0Lbl, 56, 25);
    laWidget_SetScheme((laWidget*)TotalPilot0Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TotalPilot0Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TotalPilot0Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TotalPilot0Lbl, laString_CreateFromID(string_TestTimeStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TotalPilot0Lbl);

    TotalPilot1Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TotalPilot1Lbl, 72, 256);
    laWidget_SetSize((laWidget*)TotalPilot1Lbl, 56, 25);
    laWidget_SetScheme((laWidget*)TotalPilot1Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TotalPilot1Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TotalPilot1Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TotalPilot1Lbl, laString_CreateFromID(string_TestTimeStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TotalPilot1Lbl);

    TotalPilot2Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TotalPilot2Lbl, 128, 256);
    laWidget_SetSize((laWidget*)TotalPilot2Lbl, 56, 25);
    laWidget_SetScheme((laWidget*)TotalPilot2Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TotalPilot2Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TotalPilot2Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TotalPilot2Lbl, laString_CreateFromID(string_TestTimeStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TotalPilot2Lbl);

    TotalPilot3Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TotalPilot3Lbl, 184, 256);
    laWidget_SetSize((laWidget*)TotalPilot3Lbl, 56, 25);
    laWidget_SetScheme((laWidget*)TotalPilot3Lbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TotalPilot3Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TotalPilot3Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TotalPilot3Lbl, laString_CreateFromID(string_TestTimeStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TotalPilot3Lbl);

    ShowEnablePilotsBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ShowEnablePilotsBtn, 10, 30);
    laWidget_SetSize((laWidget*)ShowEnablePilotsBtn, 24, 21);
    laWidget_SetBackgroundType((laWidget*)ShowEnablePilotsBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ShowEnablePilotsBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ShowEnablePilotsBtn, &ArrowUpRed);
    laButtonWidget_SetReleasedImage(ShowEnablePilotsBtn, &ArrowUpRed);
    laButtonWidget_SetReleasedEventCallback(ShowEnablePilotsBtn, &ShowEnablePilotsBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ShowEnablePilotsBtn);

    FinalStatsPanel = laWidget_New();
    laWidget_SetPosition((laWidget*)FinalStatsPanel, 5, 52);
    laWidget_SetSize((laWidget*)FinalStatsPanel, 233, 208);
    laWidget_SetVisible((laWidget*)FinalStatsPanel, LA_FALSE);
    laWidget_SetScheme((laWidget*)FinalStatsPanel, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)FinalStatsPanel, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)FinalStatsPanel, LA_WIDGET_BORDER_BEVEL);
    laWidget_AddChild((laWidget*)layer0, FinalStatsPanel);

    RectangleWidget2 = laRectangleWidget_New();
    laWidget_SetPosition((laWidget*)RectangleWidget2, 85, 34);
    laWidget_SetSize((laWidget*)RectangleWidget2, 63, 70);
    laWidget_SetScheme((laWidget*)RectangleWidget2, &CircleSchema);
    laWidget_SetBackgroundType((laWidget*)RectangleWidget2, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RectangleWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)RectangleWidget2);

    RectangleWidget3 = laRectangleWidget_New();
    laWidget_SetPosition((laWidget*)RectangleWidget3, 149, 74);
    laWidget_SetSize((laWidget*)RectangleWidget3, 71, 30);
    laWidget_SetScheme((laWidget*)RectangleWidget3, &CircleSchema);
    laWidget_SetBackgroundType((laWidget*)RectangleWidget3, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RectangleWidget3, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)RectangleWidget3);

    _1PlaceLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_1PlaceLbl, 80, 3);
    laWidget_SetSize((laWidget*)_1PlaceLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_1PlaceLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_1PlaceLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_1PlaceLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_1PlaceLbl, laString_CreateFromID(string_Piloto1Str));
    laLabelWidget_SetHAlignment(_1PlaceLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_1PlaceLbl);

    RectangleWidget4 = laRectangleWidget_New();
    laWidget_SetPosition((laWidget*)RectangleWidget4, 10, 64);
    laWidget_SetSize((laWidget*)RectangleWidget4, 74, 40);
    laWidget_SetScheme((laWidget*)RectangleWidget4, &CircleSchema);
    laWidget_SetBackgroundType((laWidget*)RectangleWidget4, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RectangleWidget4, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)RectangleWidget4);

    _2PlaceLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_2PlaceLbl, 7, 35);
    laWidget_SetSize((laWidget*)_2PlaceLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_2PlaceLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_2PlaceLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_2PlaceLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_2PlaceLbl, laString_CreateFromID(string_Piloto2Str));
    laLabelWidget_SetHAlignment(_2PlaceLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_2PlaceLbl);

    _3PlaceLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_3PlaceLbl, 150, 49);
    laWidget_SetSize((laWidget*)_3PlaceLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_3PlaceLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_3PlaceLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_3PlaceLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_3PlaceLbl, laString_CreateFromID(string_Piloto3Str));
    laLabelWidget_SetHAlignment(_3PlaceLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_3PlaceLbl);

    CloseFinalStatsBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CloseFinalStatsBtn, 205, 0);
    laWidget_SetSize((laWidget*)CloseFinalStatsBtn, 28, 25);
    laWidget_SetBackgroundType((laWidget*)CloseFinalStatsBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)CloseFinalStatsBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(CloseFinalStatsBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(CloseFinalStatsBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)CloseFinalStatsBtn);

    _2TimeLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_2TimeLbl, 2, 104);
    laWidget_SetSize((laWidget*)_2TimeLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_2TimeLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_2TimeLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_2TimeLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_2TimeLbl, laString_CreateFromID(string_StartTimeStr));
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_2TimeLbl);

    _1TimeLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_1TimeLbl, 79, 104);
    laWidget_SetSize((laWidget*)_1TimeLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_1TimeLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_1TimeLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_1TimeLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_1TimeLbl, laString_CreateFromID(string_StartTimeStr));
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_1TimeLbl);

    _3TimeLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_3TimeLbl, 155, 104);
    laWidget_SetSize((laWidget*)_3TimeLbl, 76, 25);
    laWidget_SetScheme((laWidget*)_3TimeLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_3TimeLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_3TimeLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_3TimeLbl, laString_CreateFromID(string_StartTimeStr));
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_3TimeLbl);

    _4PlaceLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_4PlaceLbl, 25, 164);
    laWidget_SetSize((laWidget*)_4PlaceLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_4PlaceLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_4PlaceLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_4PlaceLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_4PlaceLbl, laString_CreateFromID(string_Piloto4Str));
    laLabelWidget_SetHAlignment(_4PlaceLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_4PlaceLbl);

    _4TimeLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)_4TimeLbl, 104, 164);
    laWidget_SetSize((laWidget*)_4TimeLbl, 77, 25);
    laWidget_SetScheme((laWidget*)_4TimeLbl, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)_4TimeLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)_4TimeLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(_4TimeLbl, laString_CreateFromID(string_StartTimeStr));
    laLabelWidget_SetHAlignment(_4TimeLbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)FinalStatsPanel, (laWidget*)_4TimeLbl);

    EnablePilotsPanel = laWidget_New();
    laWidget_SetPosition((laWidget*)EnablePilotsPanel, 5, 66);
    laWidget_SetSize((laWidget*)EnablePilotsPanel, 230, 94);
    laWidget_SetVisible((laWidget*)EnablePilotsPanel, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)EnablePilotsPanel, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)EnablePilotsPanel, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, EnablePilotsPanel);

    Pilot0EnableBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot0EnableBtn, 11, 34);
    laWidget_SetSize((laWidget*)Pilot0EnableBtn, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot0EnableBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot0EnableBtn, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot0EnableBtn, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot0EnableBtn, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot0EnableBtn, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot0EnableBtn, 0);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Pilot0EnableBtn);

    Pilot1EnableBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot1EnableBtn, 70, 34);
    laWidget_SetSize((laWidget*)Pilot1EnableBtn, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot1EnableBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot1EnableBtn, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot1EnableBtn, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot1EnableBtn, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot1EnableBtn, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot1EnableBtn, 0);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Pilot1EnableBtn);

    Pilot2EnableBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot2EnableBtn, 125, 34);
    laWidget_SetSize((laWidget*)Pilot2EnableBtn, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot2EnableBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot2EnableBtn, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot2EnableBtn, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot2EnableBtn, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot2EnableBtn, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot2EnableBtn, 0);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Pilot2EnableBtn);

    Pilot3EnableBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)Pilot3EnableBtn, 180, 34);
    laWidget_SetSize((laWidget*)Pilot3EnableBtn, 43, 25);
    laWidget_SetBackgroundType((laWidget*)Pilot3EnableBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Pilot3EnableBtn, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(Pilot3EnableBtn, LA_TRUE);
    laButtonWidget_SetPressedImage(Pilot3EnableBtn, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(Pilot3EnableBtn, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(Pilot3EnableBtn, 0);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Pilot3EnableBtn);

    CloseEnableBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CloseEnableBtn, 196, 4);
    laWidget_SetSize((laWidget*)CloseEnableBtn, 28, 25);
    laWidget_SetBackgroundType((laWidget*)CloseEnableBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)CloseEnableBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(CloseEnableBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(CloseEnableBtn, &ArrowDown);
    laButtonWidget_SetReleasedEventCallback(CloseEnableBtn, &CloseEnableBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)CloseEnableBtn);

    LabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget, 13, 4);
    laWidget_SetSize((laWidget*)LabelWidget, 157, 25);
    laWidget_SetScheme((laWidget*)LabelWidget, &Primitives);
    laWidget_SetBackgroundType((laWidget*)LabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget, laString_CreateFromID(string_EnablePilotsStr));
    laLabelWidget_SetHAlignment(LabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)LabelWidget);

    Channel0Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Channel0Lbl, 14, 64);
    laWidget_SetSize((laWidget*)Channel0Lbl, 31, 25);
    laWidget_SetScheme((laWidget*)Channel0Lbl, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Channel0Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Channel0Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Channel0Lbl, laString_CreateFromID(string_BandInitStr));
    laLabelWidget_SetHAlignment(Channel0Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Channel0Lbl);

    Channel1Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Channel1Lbl, 75, 64);
    laWidget_SetSize((laWidget*)Channel1Lbl, 35, 25);
    laWidget_SetScheme((laWidget*)Channel1Lbl, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Channel1Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Channel1Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Channel1Lbl, laString_CreateFromID(string_BandInitStr));
    laLabelWidget_SetHAlignment(Channel1Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Channel1Lbl);

    Channel2Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Channel2Lbl, 130, 64);
    laWidget_SetSize((laWidget*)Channel2Lbl, 40, 25);
    laWidget_SetScheme((laWidget*)Channel2Lbl, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Channel2Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Channel2Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Channel2Lbl, laString_CreateFromID(string_BandInitStr));
    laLabelWidget_SetHAlignment(Channel2Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Channel2Lbl);

    Channel3Lbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)Channel3Lbl, 185, 64);
    laWidget_SetSize((laWidget*)Channel3Lbl, 35, 25);
    laWidget_SetScheme((laWidget*)Channel3Lbl, &Primitives);
    laWidget_SetBackgroundType((laWidget*)Channel3Lbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)Channel3Lbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(Channel3Lbl, laString_CreateFromID(string_BandInitStr));
    laLabelWidget_SetHAlignment(Channel3Lbl, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)EnablePilotsPanel, (laWidget*)Channel3Lbl);

}

static void ScreenCreate_RaceConfigWnd(laScreen* screen)
{
    laLayer* layer0;
    laRadioButtonGroup* radioButtonGroup_1;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget23 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget23, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget23, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget23, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget23, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget23, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget23);

    PanelWidget24 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget24, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget24, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget24, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget24, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget24);

    wndCaptionRaceParam = laLabelWidget_New();
    laWidget_SetSize((laWidget*)wndCaptionRaceParam, 240, 34);
    laWidget_SetScheme((laWidget*)wndCaptionRaceParam, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)wndCaptionRaceParam, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)wndCaptionRaceParam, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(wndCaptionRaceParam, laString_CreateFromID(string_RaceParamWndStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)wndCaptionRaceParam);

    ExitRaceParamBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ExitRaceParamBtn, 146, 272);
    laWidget_SetSize((laWidget*)ExitRaceParamBtn, 79, 33);
    laWidget_SetScheme((laWidget*)ExitRaceParamBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ExitRaceParamBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ExitRaceParamBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ExitRaceParamBtn, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ExitRaceParamBtn, &ExitRaceParamBtn_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ExitRaceParamBtn);

    SaveRaceParamBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)SaveRaceParamBtn, 15, 272);
    laWidget_SetSize((laWidget*)SaveRaceParamBtn, 80, 33);
    laWidget_SetScheme((laWidget*)SaveRaceParamBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)SaveRaceParamBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)SaveRaceParamBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(SaveRaceParamBtn, laString_CreateFromID(string_SaveStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)SaveRaceParamBtn);

    GroupBoxWidget34 = laGroupBoxWidget_New();
    laWidget_SetPosition((laWidget*)GroupBoxWidget34, 5, 35);
    laWidget_SetSize((laWidget*)GroupBoxWidget34, 230, 100);
    laWidget_SetScheme((laWidget*)GroupBoxWidget34, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)GroupBoxWidget34, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)GroupBoxWidget34, LA_WIDGET_BORDER_NONE);
    laGroupBoxWidget_SetText(GroupBoxWidget34, laString_CreateFromID(string_RaceTypeStr));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupBoxWidget34);

    CumulativeTimeChk = laRadioButtonWidget_New();
    laWidget_SetPosition((laWidget*)CumulativeTimeChk, 9, 30);
    laWidget_SetSize((laWidget*)CumulativeTimeChk, 206, 25);
    laWidget_SetScheme((laWidget*)CumulativeTimeChk, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)CumulativeTimeChk, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CumulativeTimeChk, LA_WIDGET_BORDER_NONE);
    laRadioButtonWidget_SetText(CumulativeTimeChk, laString_CreateFromID(string_RaceType_AbsoluteStr));
    laRadioButtonWidget_SetHAlignment(CumulativeTimeChk, LA_HALIGN_LEFT);
    laRadioButtonWidget_SetSelectedImage(CumulativeTimeChk, &SliderButtonsmall3green);
    laRadioButtonWidget_SetUnselectedImage(CumulativeTimeChk, &SliderButtonsmall3red);
    laRadioButtonGroup_Create(&radioButtonGroup_1);
    laRadioButtonGroup_AddButton(radioButtonGroup_1, CumulativeTimeChk);
    laRadioButtonWidget_SetSelected(CumulativeTimeChk);
    laWidget_AddChild((laWidget*)GroupBoxWidget34, (laWidget*)CumulativeTimeChk);

    EachRaceTimeChk = laRadioButtonWidget_New();
    laWidget_SetPosition((laWidget*)EachRaceTimeChk, 9, 64);
    laWidget_SetSize((laWidget*)EachRaceTimeChk, 211, 25);
    laWidget_SetScheme((laWidget*)EachRaceTimeChk, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)EachRaceTimeChk, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)EachRaceTimeChk, LA_WIDGET_BORDER_NONE);
    laRadioButtonWidget_SetText(EachRaceTimeChk, laString_CreateFromID(string_RaceType_EachLapStr));
    laRadioButtonWidget_SetHAlignment(EachRaceTimeChk, LA_HALIGN_LEFT);
    laRadioButtonWidget_SetSelectedImage(EachRaceTimeChk, &SliderButtonsmall3green);
    laRadioButtonWidget_SetUnselectedImage(EachRaceTimeChk, &SliderButtonsmall3red);
    laRadioButtonGroup_AddButton(radioButtonGroup_1, EachRaceTimeChk);
    laWidget_AddChild((laWidget*)GroupBoxWidget34, (laWidget*)EachRaceTimeChk);

    GroupBoxWidget38 = laGroupBoxWidget_New();
    laWidget_SetPosition((laWidget*)GroupBoxWidget38, 6, 138);
    laWidget_SetSize((laWidget*)GroupBoxWidget38, 229, 132);
    laWidget_SetBackgroundType((laWidget*)GroupBoxWidget38, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)GroupBoxWidget38, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupBoxWidget38);

    SkipFirstLapBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)SkipFirstLapBtn, 12, 101);
    laWidget_SetSize((laWidget*)SkipFirstLapBtn, 43, 25);
    laWidget_SetBackgroundType((laWidget*)SkipFirstLapBtn, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)SkipFirstLapBtn, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetToggleable(SkipFirstLapBtn, LA_TRUE);
    laButtonWidget_SetPressedImage(SkipFirstLapBtn, &SliderButtonsmall3green);
    laButtonWidget_SetReleasedImage(SkipFirstLapBtn, &SliderButtonsmall3red);
    laButtonWidget_SetPressedOffset(SkipFirstLapBtn, 0);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)SkipFirstLapBtn);

    LapNumberConfLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LapNumberConfLbl, 160, 7);
    laWidget_SetSize((laWidget*)LapNumberConfLbl, 25, 25);
    laWidget_SetScheme((laWidget*)LapNumberConfLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LapNumberConfLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LapNumberConfLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LapNumberConfLbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LapNumberConfLbl);

    LapUpBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)LapUpBtn, 189, 7);
    laWidget_SetSize((laWidget*)LapUpBtn, 25, 25);
    laWidget_SetBackgroundType((laWidget*)LapUpBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)LapUpBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(LapUpBtn, &ArrowUp);
    laButtonWidget_SetReleasedImage(LapUpBtn, &ArrowUp);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LapUpBtn);

    LapDownBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)LapDownBtn, 134, 7);
    laWidget_SetSize((laWidget*)LapDownBtn, 25, 25);
    laWidget_SetBackgroundType((laWidget*)LapDownBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)LapDownBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(LapDownBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(LapDownBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LapDownBtn);

    LabelWidget45 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget45, 65, 100);
    laWidget_SetSize((laWidget*)LabelWidget45, 150, 25);
    laWidget_SetScheme((laWidget*)LabelWidget45, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget45, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget45, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget45, laString_CreateFromID(string_SkipFirstLap_str));
    laLabelWidget_SetHAlignment(LabelWidget45, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LabelWidget45);

    LabelWidget8 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget8, 10, 37);
    laWidget_SetSize((laWidget*)LabelWidget8, 120, 25);
    laWidget_SetScheme((laWidget*)LabelWidget8, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget8, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget8, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget8, laString_CreateFromID(string_TiempoMinimoStr));
    laLabelWidget_SetHAlignment(LabelWidget8, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LabelWidget8);

    TLapDownBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)TLapDownBtn, 134, 40);
    laWidget_SetSize((laWidget*)TLapDownBtn, 25, 25);
    laWidget_SetBackgroundType((laWidget*)TLapDownBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)TLapDownBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(TLapDownBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(TLapDownBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)TLapDownBtn);

    TVueltaLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TVueltaLbl, 160, 40);
    laWidget_SetSize((laWidget*)TVueltaLbl, 25, 25);
    laWidget_SetScheme((laWidget*)TVueltaLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)TVueltaLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TVueltaLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TVueltaLbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)TVueltaLbl);

    TLapUpBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)TLapUpBtn, 189, 40);
    laWidget_SetSize((laWidget*)TLapUpBtn, 25, 25);
    laWidget_SetBackgroundType((laWidget*)TLapUpBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)TLapUpBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(TLapUpBtn, &ArrowUp);
    laButtonWidget_SetReleasedImage(TLapUpBtn, &ArrowUp);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)TLapUpBtn);

    LabelWidget39 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget39, 9, 7);
    laWidget_SetSize((laWidget*)LabelWidget39, 120, 25);
    laWidget_SetScheme((laWidget*)LabelWidget39, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget39, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget39, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget39, laString_CreateFromID(string_RaceLaps_str));
    laLabelWidget_SetHAlignment(LabelWidget39, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LabelWidget39);

    LabelWidget11 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget11, 11, 73);
    laWidget_SetSize((laWidget*)LabelWidget11, 120, 25);
    laWidget_SetScheme((laWidget*)LabelWidget11, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)LabelWidget11, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget11, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget11, laString_CreateFromID(string_BeepCountOnStartStr));
    laLabelWidget_SetHAlignment(LabelWidget11, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)LabelWidget11);

    StartBeepsDownBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)StartBeepsDownBtn, 134, 72);
    laWidget_SetSize((laWidget*)StartBeepsDownBtn, 25, 25);
    laWidget_SetBackgroundType((laWidget*)StartBeepsDownBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)StartBeepsDownBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(StartBeepsDownBtn, &ArrowDown);
    laButtonWidget_SetReleasedImage(StartBeepsDownBtn, &ArrowDown);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)StartBeepsDownBtn);

    StartBeepsLbl = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)StartBeepsLbl, 160, 72);
    laWidget_SetSize((laWidget*)StartBeepsLbl, 25, 25);
    laWidget_SetScheme((laWidget*)StartBeepsLbl, &BigTextSchema);
    laWidget_SetBackgroundType((laWidget*)StartBeepsLbl, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StartBeepsLbl, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(StartBeepsLbl, laString_CreateFromID(string_Lbl0));
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)StartBeepsLbl);

    StartBeepsUpBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)StartBeepsUpBtn, 189, 72);
    laWidget_SetSize((laWidget*)StartBeepsUpBtn, 25, 25);
    laWidget_SetBackgroundType((laWidget*)StartBeepsUpBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)StartBeepsUpBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(StartBeepsUpBtn, &ArrowUp);
    laButtonWidget_SetReleasedImage(StartBeepsUpBtn, &ArrowUp);
    laWidget_AddChild((laWidget*)GroupBoxWidget38, (laWidget*)StartBeepsUpBtn);

}

static void ScreenCreate_WifiTesting(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget10 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget10, 240, 320);
    laWidget_SetScheme((laWidget*)GradientWidget10, &BackGrowndGradient);
    laWidget_SetBackgroundType((laWidget*)GradientWidget10, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GradientWidget10, LA_WIDGET_BORDER_NONE);
    laGradientWidget_SetDirection((laGradientWidget*)GradientWidget10, LA_GRADIENT_DIRECTION_DOWN);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget10);

    PanelWidget11 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget11, 0, 31);
    laWidget_SetSize((laWidget*)PanelWidget11, 240, 4);
    laWidget_SetBackgroundType((laWidget*)PanelWidget11, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)PanelWidget11, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget11);

    LabelWidget14 = laLabelWidget_New();
    laWidget_SetSize((laWidget*)LabelWidget14, 240, 34);
    laWidget_SetScheme((laWidget*)LabelWidget14, &WindowCaption);
    laWidget_SetBackgroundType((laWidget*)LabelWidget14, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget14, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget14, laString_CreateFromID(string_WiFi_Settings_lbl));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget14);

    ButtonWidget15 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget15, 146, 272);
    laWidget_SetSize((laWidget*)ButtonWidget15, 79, 33);
    laWidget_SetScheme((laWidget*)ButtonWidget15, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget15, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ButtonWidget15, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget15, laString_CreateFromID(string_ButtonExit));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget15, &ButtonWidget15_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget15);

    StartListeningUSARTBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)StartListeningUSARTBtn, 15, 272);
    laWidget_SetSize((laWidget*)StartListeningUSARTBtn, 80, 33);
    laWidget_SetScheme((laWidget*)StartListeningUSARTBtn, &ButtonsNormal);
    laWidget_SetBackgroundType((laWidget*)StartListeningUSARTBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)StartListeningUSARTBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(StartListeningUSARTBtn, laString_CreateFromID(string_TouchStartLbl));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)StartListeningUSARTBtn);

    ATCommandsLst = laListWidget_New();
    laWidget_SetPosition((laWidget*)ATCommandsLst, 15, 51);
    laWidget_SetSize((laWidget*)ATCommandsLst, 185, 100);
    laWidget_SetBackgroundType((laWidget*)ATCommandsLst, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ATCommandsLst, LA_WIDGET_BORDER_BEVEL);
    laListWidget_SetSelectionMode(ATCommandsLst, LA_LIST_WIDGET_SELECTION_MODE_SINGLE);
    laListWidget_SetAllowEmptySelection(ATCommandsLst, LA_TRUE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ATCommandsLst);

    SendATCommandBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)SendATCommandBtn, 202, 75);
    laWidget_SetSize((laWidget*)SendATCommandBtn, 33, 30);
    laWidget_SetBackgroundType((laWidget*)SendATCommandBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)SendATCommandBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(SendATCommandBtn, &send_button);
    laButtonWidget_SetReleasedImage(SendATCommandBtn, &send_button);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)SendATCommandBtn);

    USART_TextLbl = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)USART_TextLbl, 16, 160);
    laWidget_SetSize((laWidget*)USART_TextLbl, 184, 105);
    laWidget_SetBackgroundType((laWidget*)USART_TextLbl, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)USART_TextLbl, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetCursorEnabled(USART_TextLbl, LA_TRUE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)USART_TextLbl);

    ClearUSART_TextBtn = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ClearUSART_TextBtn, 203, 195);
    laWidget_SetSize((laWidget*)ClearUSART_TextBtn, 33, 30);
    laWidget_SetBackgroundType((laWidget*)ClearUSART_TextBtn, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ClearUSART_TextBtn, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetPressedImage(ClearUSART_TextBtn, &Trash);
    laButtonWidget_SetReleasedImage(ClearUSART_TextBtn, &Trash);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ClearUSART_TextBtn);

}



