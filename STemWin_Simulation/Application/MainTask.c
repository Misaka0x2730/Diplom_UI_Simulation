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
#include "SPINBOX.h"
#include "TEXT.h"
#include "DROPDOWN.h"
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
	GUI_DispStringHCenterAt("Main", LCD_GetXSize()/2, startY);

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

void UI_DisplaySettingsMenu()
{
	u8_t startY = 20;
	u8_t key = 0;
	SPINBOX_Handle address;
	DROPDOWN_Handle mode;
	LISTBOX_Handle baud;
	SPINBOX_Handle waitingTime;
	TEXT_Handle text;
	WM_HWIN hParent;
	GUI_ConstString baudArray[] = {"1200", "2400", "9600", NULL};
	WM_HMEM *focusArray[] = {&mode, &address, &baud};
	u8_t focusCount = 0;

	GUI_Clear();
	GUI_DispStringHCenterAt("Settings", LCD_GetXSize()/2, startY);
	GUI_DispStringAt("Mode:", 10, startY + 2 * INC_YVALUE);
	GUI_DispStringAt("Address: ", 10, startY + 3 * INC_YVALUE);
	GUI_DispStringAt("Baud: ", 10, startY + 4 * INC_YVALUE);
	GUI_DispStringAt("Waiting time: ", 10, startY + 5 * INC_YVALUE);

	mode = DROPDOWN_CreateEx(140, startY + 2 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), WM_HBKWIN, WM_CF_SHOW, DROPDOWN_CF_AUTOSCROLLBAR, 1);
	DROPDOWN_AddString(mode, "Slave");
	DROPDOWN_AddString(mode, "Master");
	address = SPINBOX_CreateEx(140, startY + 3*INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), WM_HBKWIN, WM_CF_SHOW, 0, 1, 250);
	baud = LISTBOX_CreateEx(140, startY + 4 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), WM_HBKWIN, WM_CF_SHOW, 0, 1, baudArray);
	address = SPINBOX_CreateEx(140, startY + 5 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), WM_HBKWIN, WM_CF_SHOW, 0, 1, 250);
	WM_SetFocus(*focusArray[focusCount]);
	//LISTBOX_SetAutoScrollV(baud, 1);
	//baud = DROPDOWN_CreateEx(140, startY + 4 * INC_YVALUE, 80, 60, WM_HBKWIN, WM_CF_SHOW, DROPDOWN_CF_AUTOSCROLLBAR, 1);
	//DROPDOWN_AddString(baud, "1200");
	//DROPDOWN_AddString(baud, "9600");
	//address = SPINBOX_CreateEx(140, startY + 5*INC_YVALUE, 50, 20, WM_HBKWIN, WM_CF_SHOW, 0, 1, 250);
	//hParent = WM_CreateWindow(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_CF_SHOW, _cbParent, 0);
	//GUI_Clear();
	//text = TEXT_CreateEx(20, 40, 20, 20, WM_HBKWIN, WM_CF_SHOW, TEXT_CF_TOP, 1, "123"); 
	
	//("Settings", LCD_GetXSize()/2, startY);
	
	//addressSpinbox = SPINBOX_CreateEx(100, startY + 2*INC_YVALUE, 50, 20, WM_HBKWIN, WM_CF_SHOW, 0, 1, 250);
	//text = TEXT_CreateEx(20, 40, 20, 20, WM_HBKWIN, WM_CF_SHOW, TEXT_CF_TOP, 1, "123"); 
	//TEXT_SetTextColor(text, GUI_WHITE);
	//SPINBOX_SetValue(addressSpinbox, 12);
	while(1)
	{
		key = GUI_GetKey();
		switch (key)
		{
			case GUI_KEY_ENTER:
			{
				WM_SetFocus(*focusArray[focusCount++]);
				if(focusCount == sizeof(focusArray)/sizeof(focusArray[0]))
					focusCount = 0;
				break;
			}
			default:
			{
				key = 0;
				break;
			}
		}
		GUI_Delay(700);
	}

	/*if(mode == MODE_MASTER)
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
	GUI_DispString("%");*/
}

void MainTask(void) 
{
	u8_t key = 0;
	GUI_KEY_STATE keyState;
	keyState.Key = GUI_KEY_ENTER;
	GUI_Init();
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	UI_DisplayMainMenu(MODE_SLAVE, STATE_STOP, 26, 100, 50);
	while (1)
	{
		key = GUI_GetKey();
		switch (key)
		{
			case GUI_KEY_RIGHT:
			{
				UI_DisplaySettingsMenu();
				break;
			}
			case GUI_KEY_LEFT:
			{
				UI_DisplayMainMenu(MODE_SLAVE, STATE_STOP, 26, 100, 50);
				break;
			}
			default:
			{
				key = 0;
				break;
			}
		}

	}
}

/*************************** End of file ****************************/
