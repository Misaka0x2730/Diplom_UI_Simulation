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
#include "FRAMEWIN.h"
#include "BUTTON.h"
#include "LCDConf.h"
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
MENU_SWITCH UI_DisplaySettingsMenu(UI_DeviceStateStruct *deviceState);

static const GUI_WIDGET_CREATE_INFO settingsDialogCreate[] = {
	{FRAMEWIN_CreateIndirect, "Settings", WIDGET_FRAME_ID, 0, 0, XSIZE_PHYS, YSIZE_PHYS, 0, 0 },
	{TEXT_CreateIndirect, "Mode:", WIDGET_TEXT_MODE_ID, LEFT_X, TOP_Y + 2 * INC_YVALUE, 120, FONT_HEIGHT, 0, 0}
	{TEXT_CreateIndirect, "Address:", WIDGET_TEXT_MODE_ID, LEFT_X, TOP_Y + 2 * INC_YVALUE, 120, FONT_HEIGHT, 0, 0}
	{TEXT_CreateIndirect, "Baud:", WIDGET_TEXT_MODE_ID, LEFT_X, TOP_Y + 2 * INC_YVALUE, 120, FONT_HEIGHT, 0, 0}
};

static void UI_DialogCallback(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;
	WM_HWIN hItem;
	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
	{
		hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_MODE_ID);
		break;
	}
	case WM_KEY:
	{
		WM_DefaultProc(pMsg);
		break;
	}
	default:
	{
		WM_DefaultProc(pMsg);
		break;
	}
	}
}

void UI_MenuTask()
{
	DEVICE_SettingsStruct deviceSettings = {0,23,0,42};
	UI_DeviceStateStruct deviceState;
	u8_t currentMenu = MAIN_MENU;

	deviceState.settings = deviceSettings;
	deviceState.modeChanged = 0;
	deviceState.menuSwitch = MENU_STAY;

	while(1)
	{
		switch(currentMenu)
		{
			case MAIN_MENU:
			{
				deviceState.menuSwitch = MENU_STAY;
				deviceState.menuSwitch = UI_DisplayMainMenu(MODE_SLAVE, STATE_STOP, 26, 100, 50);
				if(deviceState.menuSwitch == MENU_NEXT)
					currentMenu++;
				break;
			}
			case SETTINGS_MENU:
			{
				deviceState.menuSwitch = MENU_STAY;
				deviceState.menuSwitch = UI_DisplaySettingsMenu(&deviceState);
				if(deviceState.menuSwitch == MENU_PREV)
					currentMenu--;
				break;
			}
		}
	}
}

MENU_SWITCH UI_DisplayMainMenu(DEVICE_MODES mode, DEVICE_STATES state, s16_t temp, u16_t pressure, u16_t humidity)
{
	u8_t startY = 20;
	u16_t leftX = 10;
	u8_t key = 0;

	GUI_Clear();
	GUI_DispStringHCenterAt("Main", LCD_GetXSize()/2, startY);

	if(mode == MODE_MASTER)
		GUI_DispStringAt("Current Mode: Master", leftX, startY + 2*INC_YVALUE);
	else
		GUI_DispStringAt("Current Mode: Slave", leftX, startY + 2*INC_YVALUE);

	if(state == STATE_RUN)
		GUI_DispStringAt("Current State: Running", leftX, startY + 3 * INC_YVALUE);
	else
		GUI_DispStringAt("Current State: Stopped", leftX, startY + 3 * INC_YVALUE);

	GUI_DispStringAt("Temperature: ", leftX, startY + 4 * INC_YVALUE);
	GUI_DispDecMin(temp);
	GUI_DispString("°C");
	GUI_DispStringAt("Pressure: ", leftX, startY + 5 * INC_YVALUE);
	GUI_DispDecMin(pressure);
	GUI_DispString("kPa");
	GUI_DispStringAt("Humidity: ", leftX, startY + 6 * INC_YVALUE);
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

static void UI_FrameWinCallback(WM_MESSAGE *pMsg)
{
	u16_t startY = 20;
	u16_t leftX = 10;
	GUI_ConstString baudArray[] = { "1200", "2400", "9600", "115200", NULL };
	GUI_ConstString modeArray[] = { "Slave", "Master", NULL };

	UI_DeviceStateStruct *deviceState;
	WM_HWIN backup = WM_HBKWIN;
	if (pMsg->MsgId == WM_PAINT)
	{
		GUI_Clear();
		GUI_SetFont(&MAIN_FONT);
		GUI_SetColor(GUI_BLACK);
		GUI_DispStringAt("Mode:", leftX, startY + 2 * INC_YVALUE - 23);
		GUI_DispStringAt("Address: ", leftX, startY + 3 * INC_YVALUE - 23 );
		GUI_DispStringAt("Baud: ", leftX, startY + 4 * INC_YVALUE - 23);
		GUI_DispStringAt("Waiting time: ", leftX, startY + 5 * INC_YVALUE - 23);
		LISTBOX_Handle mode = LISTBOX_CreateEx(140, startY + 2 * INC_YVALUE, 90, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, 0, WIDGET_MODE_ID, modeArray);
		SPINBOX_Handle address = SPINBOX_CreateEx(140, startY + 3 * INC_YVALUE, 90, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, WIDGET_ADDRESS_ID, MODBUS_MIN_ADDRESS, MODBUS_MAX_ADDRESS);
		LISTBOX_Handle baud = LISTBOX_CreateEx(140, startY + 4 * INC_YVALUE, 90, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, 0, WIDGET_BAUD_ID, baudArray);
		SPINBOX_Handle waitingTime = SPINBOX_CreateEx(140, startY + 5 * INC_YVALUE, 90, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, WIDGET_WAITING_TIME_ID, 1, 250);

		LISTBOX_SetFont(mode, &MAIN_FONT);
		SPINBOX_SetFont(address, &MAIN_FONT);
		LISTBOX_SetFont(baud, &MAIN_FONT);
		SPINBOX_SetFont(waitingTime, &MAIN_FONT);

		/*LISTBOX_SetSel(mode, deviceState->settings.deviceMode);
		SPINBOX_SetValue(address, deviceState->settings.address);
		LISTBOX_SetSel(baud, deviceState->settings.baud);
		SPINBOX_SetValue(waitingTime, deviceState->settings.waitingTime);*/

		WM_SetFocus(mode);

	}
	else
	{
		if (pMsg->MsgId == WM_NOTIFY_PARENT)
		{
			FRAMEWIN_Callback(pMsg);
		}
		if (pMsg->MsgId == WM_KEY)
		{
			FRAMEWIN_Callback(pMsg);
		}
		FRAMEWIN_Callback(pMsg);
	}
}

static void UI_ModeMasterListBoxCallback(WM_MESSAGE *pMsg)
{
	u16_t startY = 20;
	u16_t leftX = 10;
	
	GUI_ConstString baudArray[] = {"1200", "2400", "9600", "115200", NULL};
	GUI_ConstString modeArray[] = {"Slave", "Master", NULL};
	static u8_t focusCount = 0;
	u16_t focusID = 0;
	WM_KEY_INFO key;
	UI_DeviceStateStruct *deviceState;

	/*WM_GetUserData(pMsg->hWin, &deviceState, sizeof(deviceState));

	if(deviceState == NULL)
		WM_DefaultProc(pMsg);
	else
	{
	if(pMsg->MsgId == WM_NOTIFY_PARENT)
	{
		int ID = WM_GetId(pMsg->hWinSrc);
		int Ncode = pMsg->Data.v;
		switch(ID)
		{
			case WIDGET_MODE_ID:
			{
				switch(Ncode)
				{
					case WM_NOTIFICATION_SEL_CHANGED:
					{
						deviceState->modeChanged = 1;
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		if(pMsg->MsgId == WM_PAINT)
		{  
			GUI_Clear();
			GUI_SetFont(&MAIN_FONT);
			FRAMEWIN_Handle frame = FRAMEWIN_CreateUser(0, 0, LCD_GetXSize(), LCD_GetYSize(), pMsg->hWin, WM_CF_SHOW, 0, WIDGET_FRAME_ID, "Settings", UI_FrameWinCallback, sizeof(deviceState));
			//FRAMEWIN_SetUserData(frame, &deviceState, sizeof(deviceState));
			deviceState->modeChanged = 0;
		}
		else
		if(pMsg->MsgId == WM_KEY)
		{
			key = *(WM_KEY_INFO*)(pMsg->Data.p);
			if(key.PressedCnt == 0)
			{
				switch (key.Key)
				{
					case GUI_KEY_ENTER:
					{
						switch (++focusCount)
						{
							case 1:
							{
								focusID = WIDGET_ADDRESS_ID;
								break;
							}
							case 2:
							{
								focusID = WIDGET_BAUD_ID;
								break;
							}
							case 3:
							{
								focusID = WIDGET_WAITING_TIME_ID;
								break;
							}
							case 4:
							{
								focusCount = 0;
								focusID = WIDGET_MODE_ID;
								break;
							}
						}
						WM_SetFocus(WM_GetDialogItem(pMsg->hWin, focusID));
						break;
					}
					case GUI_KEY_LEFT:
					{
						deviceState->menuSwitch = MENU_PREV;
						break;
					}
					default:
					{
						WM_DefaultProc(pMsg);
						break;
					}
				}
			}

		}
		else
			WM_DefaultProc(pMsg);
	}
	}*/
}

MENU_SWITCH UI_DisplaySettingsMenu(UI_DeviceStateStruct *deviceState)
{
	u16_t startY = 20;
	u16_t leftX = 10;

	while (deviceState->menuSwitch == MENU_STAY)
	{
		TEXT_SetDefaultFont(&MAIN_FONT);
		WM_HWIN window = WM_CreateWindow(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_CF_SHOW, UI_ModeMasterListBoxCallback, sizeof(deviceState));
		WM_HWIN dialog = GUI_CreateDialogBox(settingsDialogCreate, GUI_COUNTOF(settingsDialogCreate), UI_DialogCallback, window, 0, 0);
		//WM_HWIN window = WM_CreateWindow(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_CF_SHOW, UI_ModeMasterListBoxCallback, sizeof(deviceState));
		//u8_t num = WM_SetUserData(window, &deviceState, sizeof(deviceState));

		while ((!deviceState->modeChanged) && (deviceState->menuSwitch == MENU_STAY))
		{
			GUI_Delay(100);
		}

		WM_DeleteWindow(window);

		if (deviceState->menuSwitch == MENU_STAY)
		{
			deviceState->modeChanged = 0;
			if (deviceState->settings.deviceMode == MODE_MASTER)
				deviceState->settings.deviceMode = MODE_SLAVE;
			else
				deviceState->settings.deviceMode = MODE_MASTER;
		}
	}
	return deviceState->menuSwitch;
}

void MainTask(void) 
{
	GUI_Init();
	GUI_Clear();
	GUI_SetFont(&MAIN_FONT);
	UI_MenuTask();
	while(1);
}

/*************************** End of file ****************************/
