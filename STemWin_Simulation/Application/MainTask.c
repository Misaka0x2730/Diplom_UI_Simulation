/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : BASIC_HelloWorld.c
Purpose     : Simple demo drawing "Hello world"
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "MainTask.h"
#include <conio.h>

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void UI_DisplayMainMenu(DEVICE_MODES mode, DEVICE_STATES state, s16_t temp, u16_t pressure, u16_t humidity)
{
	u8_t startY = 20;
	GUI_Clear();
	GUI_DispStringHCenterAt("Main window", LCD_GetXSize()/2, startY);

	if(mode == MODE_MASTER)
		GUI_DispStringAt("Current Mode: Master", 20, startY + 2*INC_YVALUE);
	else
		GUI_DispStringAt("Current Mode: Slave", 20, startY + 2*INC_YVALUE);

	if(state == STATE_RUN)
		GUI_DispStringAt("Current State: Running", 20, startY + 3 * INC_YVALUE);
	else
		GUI_DispStringAt("Current State: Stopped", 20, startY + 3 * INC_YVALUE);

	GUI_DispStringAt("Temperature: ", 20, startY + 4 * INC_YVALUE);
	GUI_DispDecMin(temp);
	GUI_DispString("°C");
	GUI_DispStringAt("Pressure: ", 20, startY + 5 * INC_YVALUE);
	GUI_DispDecMin(pressure);
	GUI_DispString("kPa");
	GUI_DispStringAt("Humidity: ", 20, startY + 6 * INC_YVALUE);
	GUI_DispDecMin(humidity);
	GUI_DispString("%");
}

void MainTask(void) 
{
	u8_t key = 0;
	GUI_KEY_STATE keyState;
	keyState.Key = GUI_KEY_ENTER;
	GUI_Init();
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
  
	while (1)
	{
		key = GUI_GetKey();
		switch (key)
		{
			case GUI_KEY_RIGHT:
			{
				UI_DisplayMainMenu(MODE_SLAVE, STATE_STOP, 25, 100, 50);
				break;
			}
			case GUI_KEY_LEFT:
			{
				UI_DisplayMainMenu(MODE_SLAVE, STATE_STOP, 26, 100, 50);
				break;
			}
		}
	}
}

/*************************** End of file ****************************/
