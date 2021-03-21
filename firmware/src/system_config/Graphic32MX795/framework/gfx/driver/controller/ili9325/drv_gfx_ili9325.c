/*******************************************************************************
  Company:
    Ernesto Pareja 

  File Name:
    drv_gfx_ili9325.c

  Summary:
    Main source file for ILI9325 display driver
    MPLABX 4.05
    Harmony 2.05

  Description:
    None
*******************************************************************************/

#include "system_config.h"
#include "system_definitions.h"
//#include <xc.h>
//#include <bsp.h>
#include "drv_gfx_ili9325.h"
#include "gfx/hal/inc/gfx_driver_interface.h"
#include "gfx/hal/inc/gfx_default_impl.h"

// Active Page
uint8_t  _activePage = 0;

#define MAX_LAYER_COUNT  1
#define MAX_BUFFER_COUNT 1

const char* DRIVER_NAME = "ILI9325";

#define DISPLAY_WIDTH   240
#define DISPLAY_HEIGHT  320

static uint32_t supportedColorModes = GFX_COLOR_MASK_RGB_565;


/*********************************************************************
 /*                      LOCAL FUNCTION DECLARATIONS        
 /*********************************************************************/
void WriteDispPort(uint16_t Data);
void WritePixel(uint16_t color);
uint16_t ILI9325_SetAddress(uint32_t address);
uint16_t ILI9325_SetAddressXY(uint16_t x, uint16_t y);
static void destroy(GFX_Context* context);
static GFX_Result ILI9325_pixelSet(const GFX_PixelBuffer* buf,
                           const GFX_Point* pnt,
                           GFX_Color color);
static GFX_Color pixelGet(const GFX_PixelBuffer* buf,
                          const GFX_Point* pnt);
void  ILI9325_PixelArrayPut(uint16_t *color, uint16_t x, uint16_t y, uint16_t count, uint16_t lineCount);
uint16_t ILI9325_SetReg(uint8_t index, uint16_t value);
uint8_t  ILI9325_GetReg(uint8_t index, uint16_t *data);
GFX_Result ILI9325_fillRect(const GFX_Rect* pRect, const GFX_DrawState* pState);

static GFX_Result brightnessRangeGet(uint32_t* low, uint32_t* high);
static GFX_Result brightnessSet(uint32_t val);
static GFX_Result layerActiveSet(uint32_t idx);
static GFX_Result layerEnabledSet(GFX_Bool val);
static GFX_Result layerPositionSet(int32_t x, int32_t y);
static GFX_Result layerSizeSet(int32_t width, int32_t height);
static GFX_Result layerBufferCountSet(uint32_t count);
static GFX_Result layerBufferAddressSet(uint32_t idx, GFX_Buffer address);
static GFX_Result layerBufferCoherentSet(uint32_t idx, GFX_Bool coherent);
static GFX_Result layerBufferAllocate(uint32_t idx);
static GFX_Result layerBufferFree(uint32_t idx);
static GFX_Result layerVisibleSet(GFX_Bool val);
static GFX_Result layerAlphaEnableSet(GFX_Bool enable, GFX_Bool enable2); // second parameter needed in Harmony 2.05



/*********************************************************************
* Function:  void DelayMs(int ms)
********************************************************************/
void DelayMs(int ms) {
  uint32_t start = _CP0_GET_COUNT();
  uint32_t end = start + SYS_CLK_SystemFrequencyGet() / 1000 / 2 * ms;
  if (end > start) {
    while (_CP0_GET_COUNT() < end);
  } else {
    while (_CP0_GET_COUNT() > start || _CP0_GET_COUNT() < end);
  }
}



/*********************************************************************
* Function:  void ResetDevice()
*
* PreCondition: none
* Input: none
* Output: none
* Side Effects: none
* Overview: Resets LCD
* Note: 
********************************************************************/
void ILI9325_Reset(void) {
  DisplayResetEnable();
  DelayMs(10);
  DisplayResetDisable();
}

/*********************************************************************
* Function:  void ILI9325_InitHardware(GFX_Context * context) 
*
* PreCondition: Must be defined the GFX_Context structure
*
* Input: GFX_Context structure. It uses the orientation and size of the screen
*
* Output: none
*
* Side Effects: none
*
* Overview: Initialize the controller registers in standard form
*
* Note: none
*
********************************************************************/
void ILI9325_InitHardware(GFX_Context * context) {
  uint16_t  horizontalSize, verticalSize;
	uint16_t horzWidth;
	uint16_t vertHeight;
  GFX_Orientation Orient2;
  
  horzWidth = context->display_info->rect.width;
  vertHeight = context->display_info->rect.height;
  Orient2 = context->orientation;
  
  DisplayDisable();
  DisplayConfig();                    // enable chip select line config
  DisplayPortConfig(DISP_OUTPUT);    
  DisplayResetEnable();               // hold in reset by default
  DisplayResetConfig();               // enable RESET line
  DelayMs(2); // ILI9325 requirement for 1ms to be on hold the reset line
  DisplayCmdDataConfig();
  DispLatchClr();
  DispLatchConfig();          // Configura el Enable del Latch 74HC573
  DisplayBacklightOff();
  DisplayBacklightConfig();   // Configura el puerto del Back Light del display
  DisplayWRClr();
  DisplayWRConfig();
  DisplayRDClr();
  DisplayRDConfig();

  /*time for the controller to power up*/
//  DelayMs(50);
  DisplayResetDisable();
//  DelayMs(50);
  DisplayEnable();
//  DelayMs(100);

  
  if((Orient2 == GFX_ORIENTATION_90) || (Orient2 == GFX_ORIENTATION_270)) {
    horizontalSize = vertHeight;
    verticalSize   = horzWidth;
//    drvILI9325Obj.maxX = horizontalSize - 1;
//    drvILI9325Obj.maxY = verticalSize - 1;
  }
  else {
    horizontalSize = horzWidth;
    verticalSize   = vertHeight;
//    drvILI9325Obj.maxX = horizontalSize - 1;
//    drvILI9325Obj.maxY = verticalSize - 1;
  }

  //************* Start Initial Sequence **********//
  ILI9325_SetReg(0xE3, 0x3008); // set SRAM internal timing ##Changed
  ILI9325_SetReg(0xE7, 0x0012); 
  ILI9325_SetReg(0xEf, 0x1231); 

  switch(Orient2) {
    case GFX_ORIENTATION_90:
      ILI9325_SetReg(0x01, 0x0000); // set SS==1 (shift direction of outputs is from S1 to S720) and SM bit=0
      ILI9325_SetReg(0x03, 0x1038); // set GRAM write direction and BGR=1.
      break;

    case GFX_ORIENTATION_180:
      ILI9325_SetReg(0x01, 0x0000); // set SS==1 (shift direction of outputs is from S720 to S1) and SM bit=0
      ILI9325_SetReg(0x03, 0x1030); //estaba en 1030 set GRAM write direction and BGR=1.
      break;

    case GFX_ORIENTATION_270:
      ILI9325_SetReg(0x01, 0x0100); // set SS and SM bit
      ILI9325_SetReg(0x03, 0x1038); // set GRAM write direction and BGR=1.
      break;

    /*case 0:*/
    default:
      ILI9325_SetReg(0x01, 0x0100); // set SS=0 and SM=0 bit
      ILI9325_SetReg(0x03, 0x1030); // set GRAM write direction and BGR=1.
      break;

  }

  ILI9325_SetReg(0x02, 0x0700); // set 1 line inversion
  ILI9325_SetReg(0x04, 0x0000); // Resize register SAME
  ILI9325_SetReg(0x08, 0x0202); // set the back porch and front porch  (2 lines front and 2 lines back)

  ILI9325_SetReg(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]
  ILI9325_SetReg(0x0A, 0x0000); // FMARK function
  ILI9325_SetReg(0x0C, 0x0000); // RGB interface setting
  ILI9325_SetReg(0x0D, 0x0000); // Frame marker Position
  ILI9325_SetReg(0x0F, 0x0000); // RGB interface polarity

  //*************Power On sequence ****************//
  ILI9325_SetReg(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
  ILI9325_SetReg(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
  ILI9325_SetReg(0x12, 0x0000); // VREG1OUT voltage
  ILI9325_SetReg(0x13, 0x0000); // VDV[4:0] for VCOM amplitude
  ILI9325_SetReg(0x07, 0x0001); // 
	

  DelayMs(100); // Dis-charge capacitor power voltage ##Changed was 50

  ILI9325_SetReg(0x10, 0x1690); // 1490//SAP, BT[3:0], AP, DSTB, SLP, STB  ##Changed
  ILI9325_SetReg(0x11, 0x0220); // DC1[2:0], DC0[2:0], VC[2:0]  ##Changed

  DelayMs(50); // Delay 50ms
  ILI9325_SetReg(0x12, 0x0091); //001C// Internal reference voltage= Vci;  ##Changed

  DelayMs(50); // Delay 50ms
  ILI9325_SetReg(0x13, 0x1700); //0x1000//1400   Set VDV[4:0] for VCOM amplitude  1A00  ##Changed
  ILI9325_SetReg(0x29, 0x001A); //0x0012 //001a  Set VCM[5:0] for VCOMH  //0x0025  0034 ##Changed

  DelayMs(50); // Delay 50ms ##Changed added

  ILI9325_SetReg(0x2B, 0x000B); // Set Frame Rate   000C ##Changed

  DelayMs(50); // Delay 50ms

  ILI9325_SetReg(0x20, 0x0000); // GRAM horizontal Address
  ILI9325_SetReg(0x21, 0x0000); // GRAM Vertical Address

  // ----------- Adjust the Gamma Curve ----------//
  ILI9325_SetReg(0x30, 0x0007);	//##Changed
  ILI9325_SetReg(0x31, 0x0507);	//##Changed
  ILI9325_SetReg(0x32, 0x0006);	//##Changed
  ILI9325_SetReg(0x35, 0x0001);

  ILI9325_SetReg(0x36, 0x0709);//0207	##Changed
  ILI9325_SetReg(0x37, 0x0104);//0306  ##Changed
  ILI9325_SetReg(0x38, 0x0502);//0102  ##Changed

  ILI9325_SetReg(0x39, 0x0706);//0707	##Changed
  ILI9325_SetReg(0x3C, 0x0500);//0702  ##Changed
  ILI9325_SetReg(0x3D, 0x000C);//1604  ##Changed

  //------------------ Set GRAM area ---------------//
  ILI9325_SetReg(0x50, 0x0000); // Horizontal GRAM Start Address
  ILI9325_SetReg(0x51, 0x00EF); // Horizontal GRAM End Address
  ILI9325_SetReg(0x52, 0x0000); // Vertical GRAM Start Address
  ILI9325_SetReg(0x53, 0x013F); // Vertical GRAM Start Address

  switch(Orient2) {
    case GFX_ORIENTATION_90:
      ILI9325_SetReg(0x60, 0xA700); // Gate Scan Line to 320 lines and GS = 1
      break;

    case GFX_ORIENTATION_180:
      ILI9325_SetReg(0x60, 0x2700); // Gate Scan Line to 320 lines and GS = 1
      break;

    case GFX_ORIENTATION_270:
      ILI9325_SetReg(0x60, 0x2700); // Gate Scan Line to 320 lines and GS = 1
      break;

    /*case 0:*/
    default:
      ILI9325_SetReg(0x60, 0xA700); // Gate Scan Line to 320 lines and GS = 1
      break;

  }

  ILI9325_SetReg(0x61, 0x0001); // NDL,VLE, REV
  ILI9325_SetReg(0x6A, 0x0000); // set scrolling line

  //-------------- Partial Display Control ---------//
  ILI9325_SetReg(0x80, 0x0000);
  ILI9325_SetReg(0x81, 0x0000);
  ILI9325_SetReg(0x82, 0x0000);
  ILI9325_SetReg(0x83, 0x0000);
  ILI9325_SetReg(0x84, 0x0000);
  ILI9325_SetReg(0x85, 0x0000);

  //-------------- Panel Control -------------------//
  ILI9325_SetReg(0x90, 0x0010);
  ILI9325_SetReg(0x92, 0x0000);	//##Changed
  ILI9325_SetReg(0x93, 0x0003);	//##Changed added
  ILI9325_SetReg(0x95, 0x0110);	//##Changed added
  ILI9325_SetReg(0x97, 0x0000);	//##Changed added
  ILI9325_SetReg(0x98, 0x0000);	//##Changed added

  ILI9325_SetReg(0x07, 0x0133); // 262K color and display ON ##Changed

  DelayMs(50);	//Added

  DisplayDisable();
  DisplayBacklightOn();
}

/*********************************************************************
 * Function:  void NewFunction(void)
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
static GFX_Result ILI9325_initialize(GFX_Context* context) {
  uint32_t i;

  GFX_Result resultBufferCreate;

  // initialize all layers
  for(i = 0; i < context->layer.count; i++)  {
    context->layer.layers[i].enabled = GFX_TRUE;
    context->layer.layers[i].visible = GFX_TRUE;

    context->layer.layers[i].vsync = GFX_FALSE;
    context->layer.layers[i].swap = GFX_FALSE;

    context->layer.layers[i].rect.local.x = 0;
    context->layer.layers[i].rect.local.y = 0;
    context->layer.layers[i].rect.local.width = context->display_info->rect.width;
    context->layer.layers[i].rect.local.height = context->display_info->rect.height;

    context->layer.layers[i].rect.display = context->layer.layers[i].rect.local;

    context->layer.layers[i].alphaEnable = GFX_FALSE;
    context->layer.layers[i].alphaAmount = 255;

    context->layer.layers[i].maskEnable = GFX_FALSE;
    context->layer.layers[i].maskColor = 0;

    context->layer.layers[i].buffer_count = 1;
    context->layer.layers[i].buffer_read_idx = 0;
    context->layer.layers[i].buffer_write_idx = 0;

    resultBufferCreate =
      GFX_PixelBufferCreate(context->display_info->rect.width,
                            context->display_info->rect.height,
                            GFX_COLOR_MODE_RGB_565,
                            NULL,
                            &context->layer.layers[i].buffers[0].pb);
    assert(resultBufferCreate == GFX_SUCCESS);

    context->layer.layers[i].buffers[0].state = GFX_BS_MANAGED;
  }

  ILI9325_InitHardware(context);
  return GFX_SUCCESS;
}


/*********************************************************************
* Function:  SetArea(start_x,start_y,end_x,end_y)
*
* PreCondition: SetActivePage(page)
*
* Input: start_x, end_x - start column and end column
*        start_y,end_y  - start row and end row position (i.e. page address)
*
* Output: none
*
* Side Effects: none
*
* Overview: defines start/end columns and start/end rows for memory access
*           from host to SSD1963
* Note: none
********************************************************************/
void ILI9325_SetArea(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y) {

  GFX_Context* pContext = GFX_ActiveContext();

  if (pContext->orientation == GFX_ORIENTATION_0 ||
       pContext->orientation == GFX_ORIENTATION_180) {
      ILI9325_SetReg(0x0050, start_x); 
      ILI9325_SetReg(0x0051, end_x); 
      ILI9325_SetReg(0x0052, start_y);
      ILI9325_SetReg(0x0053, end_y);
  } else { // 90 or 270
      ILI9325_SetReg(0x0044, ((end_y << 8) | start_y)); // Source RAM address window 
      ILI9325_SetReg(0x0045, start_x); // Gate RAM address window 
      ILI9325_SetReg(0x0046, end_x); // Gate RAM address window 
  }
//  commandBuffer.address = ((uint32_t) (drvILI9325Obj.initData->verticalResolution) * (y1)) + x1;
//  commandBuffer.address = (((uint32_t) (drvILI9325Obj.initData->verticalResolution)) * (y1) + (x1)) << 1;

  ILI9325_SetAddressXY(start_x,start_y);

}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
GFX_Result ILI9325_fillRect(const GFX_Rect* pRect,
                    const GFX_DrawState* pState) {
  int16_t      x, y, left, right, top, bottom;
  GFX_Context* pContext = GFX_ActiveContext();
//  GFX_Layer*   pLayer  = pContext->layer.active;
  GFX_Rect     clipRect;
  GFX_Color    color;

//  // a basic fill is an optimal case for this driver
//  // everything else should go through software pixel pipeline
//  if(pContext->orientation != GFX_ORIENTATION_0 ||
//     pContext->mirrored != GFX_FALSE)
//      return cpuDrawRect_Fill(pRect, pState);
//
//  // clip against the physical pLayer bounds
//  if(GFX_PixelBufferClipRect(&pLayer->buffers[pLayer->buffer_write_idx].pb,
//                             pRect,
//                             &clipRect) == GFX_FAILURE)
//  { // Input rectangle doesn't intersect with clip rectangle, we're done!
//      return GFX_FAILURE;
//  }

#if GFX_BOUNDS_CLIPPING_ENABLED
  // clip against the global clipping rectangle
  if(pState->clipEnable == GFX_TRUE)
  {
      if(GFX_RectIntersects(pRect, &pState->clipRect) == GFX_FALSE)
          return GFX_SUCCESS;

      GFX_RectClip(pRect, &pState->clipRect, &clipRect);
  }
  else
  { // Clipping not on
      clipRect = *pRect;
  }
#else
  clipRect = *pRect; // Clipping disabled.
#endif

  left   = clipRect.x;
  right  = left + clipRect.width;
  top    = clipRect.y;
  bottom = top + clipRect.height;
  color  = pState->color;

  DisplayEnable();

  ILI9325_SetArea(left,top,right,bottom);

  for(y=top; y<bottom+1; y++){
      for(x=left; x<right+1; x++){
        WritePixel((uint16_t)color);
      }
  }

  ILI9325_SetArea(0,0,pContext->display_info->rect.width,pContext->display_info->rect.height);
  DisplayDisable();

  return(GFX_SUCCESS);
}

/*********************************************************************
 * @brief 
 * @param GFX_Rect* pRect : Pointer to a 4 point structure
 * @param GFX_DrawState* pState : Pointer to a DrawState structure that has the color to draw.          
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
GFX_Result ILI9325_drawLine(const GFX_Rect* pRect, const GFX_DrawState* pState) {
  int16_t      x, y, left, right, top, bottom;
  GFX_Context* pContext = GFX_ActiveContext();
//  GFX_Layer*   pLayer  = pContext->layer.active;
  GFX_Rect     clipRect;
  GFX_Color    color;
}

/*********************************************************************
 * Function:        GFX_Result ClrScreen(GFX_Color color); 
 * 
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ********************************************************************/
GFX_Result ILI9325_ClrScreen(GFX_Color color) {
  GFX_Context * pContext;
  GFX_Color ActualColor;
  
  pContext = GFX_ActiveContext();
  ActualColor = pContext->draw.color; // Save the color it had before calling ClrScreen
  pContext->draw.color = color;
  
  DisplayEnable();

  ILI9325_fillRect(&pContext->display_info->rect, &pContext->draw);    
  pContext->draw.color = ActualColor; // Retorna el color que ten?a

  DisplayDisable();
  
  return GFX_SUCCESS;
  
}


/*********************************************************************
* Function:  void EnterSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: ILI9325 enters sleep mode and Stby mode
* Note: Host must wait 5mS after sending before sending next command
********************************************************************/
void ILI9325_EnterSleepMode (void)
{
  ILI9325_SetReg(0x10, 0x1693); // 1490//SAP, BT[3:0], AP, DSTB, SLP, STB  ##Sets STB and SLP
}

/*********************************************************************
* Function:  void ExitSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: ILI9325 exits sleep mode and Stdby Mode
* Note:   none
********************************************************************/
void ILI9325_ExitSleepMode (void) {
  ILI9325_SetReg(0x10, 0x1690); // 1490//SAP, BT[3:0], AP, DSTB, SLP, STB  ##Clear STB and SLP
}

/*********************************************************************
* Function      : void DisplayOff(void)
* PreCondition  : none
* Input         : none
* Output        : none
* Side Effects  : none
* Overview      : SSD1963 changes the display state to OFF state
* Note          : none
********************************************************************/
void ILI9325_DisplayOff(void) {
  ILI9325_SetReg(0x07, 0x0000); // 
}

/*********************************************************************
* Function      : void DisplayOn(void)
* PreCondition  : none
* Input         : none
* Output        : none
* Side Effects  : none
* Overview      : ILI9325 changes the display state to ON state
* Note          : none
********************************************************************/
void ILI9325_DisplayOn(void) {
  ILI9325_SetReg(0x07, 0x0133); // 262K color and display ON ##Changed
}


/*********************************************************************
* Function:  void  SetBacklight(BYTE intensity)
*
* Overview: This function makes use of PWM feature of ssd1963 to adjust
*           the backlight intensity.
*
* PreCondition: Backlight circuit with shutdown pin connected to PWM output of ssd1963.
*
* Input:    (BYTE) intensity from
*           0x00 (total backlight shutdown, PWM pin pull-down to VSS)
*           0xff (99% pull-up, 255/256 pull-up to VDD)
*
* Output: none
*
* Note: The base frequency of PWM set to around 300Hz with PLL set to 120MHz.
*       This parameter is hardware dependent
********************************************************************/
void ILI9325_SetBacklight(uint8_t  intensity) // NOT YET SUPPORTED ON HARDWARE!!!
{
  //WriteCommand(0xBE);         // Set PWM configuration for backlight control
//    WriteCommand(CMD_SET_PWM_CONF);

}

/*********************************************************************
 * @name void ILI9325_destroy(GFX_Context* context) 
 * @brief Destroy the Context object tha has all the graphic options config
 * @param GFX_Context* context
 * @retval None 
 * Overview: This functions is assigned in the ILI9325_ContextInitialize       
 * @note            
 ********************************************************************/
static void ILI9325_destroy(GFX_Context* context) {
  // driver specific shutdown tasks
  if(context->driver_data != GFX_NULL)
  {
      context->memory.free(context->driver_data);
      context->driver_data = GFX_NULL;
  }

  // general default shutdown
  defDestroy(context);
}


static GFX_Result ILI9325_pixelSet(const GFX_PixelBuffer* buf,
                           const GFX_Point* pnt,
                           GFX_Color color)
{
  DisplayEnable();
  while(ILI9325_SetAddressXY(pnt->x,pnt->y));
  WritePixel((uint16_t)color);
  DisplayDisable();

  return GFX_SUCCESS;
}

/*****************************************************************************
  Function: void  DRV_GFX_ILI9325_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count)

  THIS FUNCTION IS NOT WORKING WITH THIS MODULE YET
  Summary:
    outputs an array of pixels of length count starting at *color 

  Description: none
  Input:
          instance - driver instance
          *color - start of the array
		  x - x coordinate of the start point.
		  y - y coordinate of the end point.
		  count - number of pixels
  Output:
         handle to the number of pixels remaining
// *****************************************************************************/
void  ILI9325_PixelArrayPut(uint16_t *color, uint16_t x, uint16_t y, uint16_t count, uint16_t lineCount){
  uint16_t i;

  DisplayEnable();

//  commandBuffer.address = ((uint32_t) (drvILI9325Obj.initData->verticalResolution) * (y)) + x;

  while(lineCount)  {
    while(ILI9325_SetAddressXY(x,y));

    for(i = 0; i < count; i++)    {
      WritePixel(*color);
      color++;
    }
//    x += drvILI9325Obj.initData->horizontalResolution;
    x += 1;
    lineCount--;
  }
  //commandBuffer.data = 0;
  DisplayDisable();
} 

/*******************************************************************************
  Function: uint8_t ILI9325_SetReg(uint8_t index, uint16_t value)

  Summary:
    updates graphics controller register value (byte access)

  Description: none

  Input:
    index - register number 
    value - value to write to register

  Output:
    1 - call was not passed
    0 - call was passed
*******************************************************************************/
uint16_t ILI9325_SetReg(uint8_t index, uint16_t value) {
  DisplaySetCommand(); // SET RS to 0 to send command
  WriteDispPort((uint16_t)index);
  DisplaySetData(); // Now we are going to write the Data into the register
  WriteDispPort(value);
  return GFX_SUCCESS;
}

/******************************************************************************
  Function: uint8_t DRV_GFX_ILI9325_GetReg(uint16_t index, uint8_t *data)

  Summary:
    returns graphics controller register value (byte access)

  Description:
    none

  Input:
    index - register number 
    *data - array to store data

  Output:
    0 - when call was passed
*******************************************************************************/
uint8_t  ILI9325_GetReg(uint8_t index, uint16_t *data) { 
  uint16_t temp;
  uint16_t tempData;
   
//#if (GFX_LCD_PORT_BITS == 8)
  
}

/*********************************************************************
 * Function:        void WriteCmd(uint16_t Data)
 *
 * PreCondition:    None
 * Input:           Data : the Command or Data to be sent to the LCD
 * Output:          None
 * Side Effects:    None
 * Overview:        Escribe en el puerto del display el dato a enviar,
 *                  sea Comando o dato. Antes de llamar la funci?n debe
 *                  ponerse el nivel de RS en 0 para Comandos o en 1 para datos
 *                  usando DisplaySetCommand() o DisplaySetData().
 * 
 *                  Tambi?n debe tenerse habilitado el CS del display
 *                  llamando a DisplayEnable()
 *
 * Note:            None
 ********************************************************************/
void WriteDispPort(uint16_t Data) {
  uint8_t temp;

#if (GFX_LCD_PORT_BITS == 8) 
  DisplayWRSet();
  temp = (Data >> 8) & 0xFF;
  DisplayPort(temp); // LSB Byte of the value
  Nop();
  DisplayWRClr(); // Flank Triggered (Low to High transition)
  Nop();
  temp = (Data) & 0xFF;
  DisplayPort(temp);
  Nop();
  DisplayWRSet();
  Nop();
  DisplayWRClr();
#elif (GFX_LCD_PORT_BITS == 16)


  DisplayPort(Data & 0x00FF); // LSB Byte of the value
  asm ("NOP");
  DispLatchSet();

  asm ("NOP");
  asm ("NOP");
  asm ("NOP");
  asm ("NOP");
  DispLatchClr();
  
  DisplayPort((Data >> 8) & 0x00FF); // MSB Byte of the value
  asm ("NOP");
  DisplayWRSet();
  asm ("NOP");
  asm ("NOP");
  DisplayWRClr();
#else
  #error "Debe definir un tama?o de bits para el puerto del display"
#endif
}


/*********************************************************************
* Macro:  WritePixel(color)
*
* PreCondition: none
*
* Input: color
*
* Output: none
*
* Side Effects: none
*
* Overview: writes pixel at the current address
*
* Note: chip select should be enabled
*
********************************************************************/
void WritePixel(uint16_t color) {
  DisplaySetData();
  WriteDispPort(color);
  
}



/*********************************************************************
 * Function:        uint16_t ReadDispPort(void
 *
 * PreCondition:    None
 * Input:           None 
 * Output:          The value read from the display
 * Side Effects:    None
 * Overview:        Antes de llamar la funci?n debe
 *                  ponerse el nivel de RS en 0 para Comandos o en 1 para datos
 *                  usando DisplaySetCommand() o DisplaySetData().
 * 
 *                  Tambi?n debe tenerse habilitado el CS del display
 *                  llamando a DisplayEnable()
 *
 * Note:            None
 ********************************************************************/
uint16_t  ReadDispPort(void) {
  uint8_t temp;

#if (GFX_LCD_PORT_BITS == 8) 

#elif (GFX_LCD_PORT_BITS == 16)

#else
  #error "Debe definir un tama?o de bits para el puerto del display"
#endif
}

/*********************************************************************
 * @brief Actualiza el color de escritura de la estructura Context
 * @param GFX_Color NewColor: El color en formato RGB_565 asignado
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void SetColor(GFX_Color NewColor) {
  GFX_Context* pContext = GFX_ActiveContext();
  pContext->draw.color  = NewColor;
}

/*****************************************************************************
  Function: uint16_t DRV_GFX_ILI9325_SetAddress(DWORD address)

  Summary:
    sets the pmp address for read/write operations

  Description:
 Debe estar habilitado el CS del display al llamar esta funcion

  Input:
    address - address

  Output:
    0 - when call was passed
 *****************************************************************************/
uint16_t ILI9325_SetAddress(uint32_t address) {
    uint16_t tempY;
    uint16_t tempX;
    
    tempY = ((address >> 8) & 0xFF) + ((address >> 16) & 0xFF);
    tempX = (address & 0xFF);
   
    ILI9325_SetAddressXY(tempX, tempY);
    return(0);
}

/*****************************************************************************
  Function: uint16_t DRV_GFX_ILI9325_SetAddress(DWORD address)

  Summary:
    sets the pmp address for read/write operations

  Description:
 Debe estar habilitado el CS del display al llamar esta funcion

  Input:
    address - address

  Output:
    0 - when call was passed
 *****************************************************************************/
uint16_t ILI9325_SetAddressXY(uint16_t x, uint16_t y) {
    
  switch(GFX_ActiveContext()->orientation){
    case GFX_ORIENTATION_0:
    case GFX_ORIENTATION_180: {
      ILI9325_SetReg(0x20, x );
      ILI9325_SetReg(0x21, y );
      break;
    }
    case GFX_ORIENTATION_90:
    case GFX_ORIENTATION_270: {
      ILI9325_SetReg(0x20, y );
      ILI9325_SetReg(0x21,(DISPLAY_HEIGHT - 1 - x));
      break;
    }
//    case GFX_ORIENTATION_180: {
//      ILI9325_SetReg(0x20,DISPLAY_WIDTH - 1 - x);
//      ILI9325_SetReg(0x21,(DISPLAY_HEIGHT - 1 - y));
//      break;
//    }
//    case GFX_ORIENTATION_270: {
//      ILI9325_SetReg(0x20,DISPLAY_WIDTH - 1 - y);
//      ILI9325_SetReg(0x21, x );
//      break;
//    }
  }
  DisplaySetCommand(); //Set Address Line Low
  WriteDispPort(0x22); // Writes the address to GRAM

  return GFX_SUCCESS;
}

static GFX_Result brightnessRangeGet(uint32_t* low, uint32_t* high)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result brightnessSet(uint32_t val)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerActiveSet(uint32_t idx)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerEnabledSet(GFX_Bool val)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerPositionSet(int32_t x, int32_t y)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerSizeSet(int32_t width, int32_t height)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferCountSet(uint32_t count)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferAddressSet(uint32_t idx, GFX_Buffer address)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferCoherentSet(uint32_t idx, GFX_Bool coherent)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferAllocate(uint32_t idx)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferFree(uint32_t idx)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerVisibleSet(GFX_Bool val)
{
    return GFX_UNSUPPORTED;
}

static GFX_Result layerAlphaEnableSet(GFX_Bool enable, GFX_Bool enable2)
{
    return GFX_UNSUPPORTED;
}

static GFX_Color ILI9325_pixelGet(const GFX_PixelBuffer* buf,
                                  const GFX_Point* pnt) {
    return 0xA8;
}

// function that returns the information for this driver
GFX_Result ILI9325_InfoGet(GFX_DriverInfo* info)
{
    if(info == GFX_NULL)
        return GFX_FAILURE;

    // populate info struct
    strcpy(info->name, DRIVER_NAME);
    info->color_formats = supportedColorModes;
    info->layer_count = MAX_LAYER_COUNT;

    return GFX_SUCCESS;
}

// function that initialized the driver context
GFX_Result ILI9325_ContextInitialize(GFX_Context* context) {
    // set driver-specific function implementations
    context->hal.initialize = &ILI9325_initialize;
    context->hal.destroy = &ILI9325_destroy;
    context->hal.brightnessRangeGet = &brightnessRangeGet;
    context->hal.brightnessSet = &brightnessSet;
    context->hal.layerActiveSet = &layerActiveSet;
    context->hal.layerEnabledSet = &layerEnabledSet;
    context->hal.layerPositionSet = &layerPositionSet;
    context->hal.layerSizeSet = &layerSizeSet;
    context->hal.layerBufferCountSet = &layerBufferCountSet;
    context->hal.layerBufferAddressSet = &layerBufferAddressSet;
    context->hal.layerBufferCoherentSet = &layerBufferCoherentSet;
    context->hal.layerBufferAllocate = &layerBufferAllocate;
    context->hal.layerBufferFree = &layerBufferFree;
    context->hal.layerVisibleSet = &layerVisibleSet;
    context->hal.layerAlphaEnableSet = &layerAlphaEnableSet;

    context->hal.drawPipeline[GFX_PIPELINE_GCU].pixelSet = &ILI9325_pixelSet;
    context->hal.drawPipeline[GFX_PIPELINE_GCU].pixelGet = &ILI9325_pixelGet;

    context->hal.drawPipeline[GFX_PIPELINE_GCUGPU].pixelSet = &ILI9325_pixelSet;
    context->hal.drawPipeline[GFX_PIPELINE_GCUGPU].pixelGet = &ILI9325_pixelGet;

    context->hal.drawPipeline[GFX_PIPELINE_GCU].drawRect[GFX_DRAW_FILL][GFX_ANTIALIAS_OFF] = &ILI9325_fillRect;
    context->hal.drawPipeline[GFX_PIPELINE_GCUGPU].drawRect[GFX_DRAW_FILL][GFX_ANTIALIAS_OFF] = &ILI9325_fillRect;
    
    context->orientation = DISP_ORIENTATION; //TODO: Esto deber?a venir de la configuraci?n del Graphic Composer

    return GFX_SUCCESS;
}


