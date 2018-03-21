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

MENU_SWITCH UI_DisplayMainMenu(DEVICE_MODES mode, DEVICE_STATES state, s16_t temp, u16_t pressure, u16_t humidity);
MENU_SWITCH UI_DisplaySettingsMenu();

void UI_MenuTask()
{
	u8_t currentMenu = MAIN_MENU;
	u8_t nextMenu = MAIN_MENU;
	while(1)
	{
		switch(currentMenu)
		{
			case MAIN_MENU:
			{
				nextMenu = UI_DisplayMainMenu(MODE_SLAVE, STATE_STOP, 26, 100, 50);
				if(nextMenu == MENU_NEXT)
					currentMenu++;
				break;
			}
			case SETTINGS_MENU:
			{
				nextMenu = UI_DisplaySettingsMenu();
				if(nextMenu == MENU_PREV)
					currentMenu--;
				break;
			}
		}
	}
}

MENU_SWITCH UI_DisplayMainMenu(DEVICE_MODES mode, DEVICE_STATES state, s16_t temp, u16_t pressure, u16_t humidity)
{
	u8_t startY = 20;
	u8_t key = 0;

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

	while(1)
	{
		key = GUI_GetKey();
		switch (key)
		{
			case GUI_KEY_RIGHT:
			{
				return MENU_NEXT;
				break;
			}
			default:
			{
				key = 0;
				break;
			}
		}
		GUI_ClearKeyBuffer();
		GUI_Delay(800);
	}
}

MENU_SWITCH UI_DisplaySettingsMenu()
{
	u8_t startY = 20;
	u8_t key = 0;
	WM_HWIN window;
	SPINBOX_Handle address;
	DROPDOWN_Handle mode;
	LISTBOX_Handle baud;
	SPINBOX_Handle waitingTime;
	TEXT_Handle text;
	WM_HWIN hParent;
	GUI_ConstString baudArray[] = {"1200", "2400", "9600", NULL};
	WM_HMEM *focusArray[] = {&mode, &address, &baud, &waitingTime};
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
	waitingTime = SPINBOX_CreateEx(140, startY + 5 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), WM_HBKWIN, WM_CF_SHOW, 0, 1, 250);
	WM_SetFocus(*focusArray[focusCount]);

	while(1)
	{
		key = GUI_GetKey();
		switch (key)
		{
			case GUI_KEY_ENTER:
			{
				if((++focusCount) == sizeof(focusArray)/sizeof(focusArray[0]))
					focusCount = 0;
				WM_SetFocus(*focusArray[focusCount]);
				break;
			}
			case GUI_KEY_LEFT:
			{
				WM_DeleteWindow(mode);
				WM_DeleteWindow(address);
				WM_DeleteWindow(baud);
				WM_DeleteWindow(waitingTime);
				return MENU_PREV;
				break;
			}
			default:
			{
				key = 0;
				break;
			}
		}
		GUI_ClearKeyBuffer();
		GUI_Delay(800);
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
	UI_MenuTask();
	while(1);
}

/*************************** End of file ****************************/
