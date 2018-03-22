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
	DEVICE_SettingsStruct deviceSettings = {0,23,0,42};
	UI_DeviceStateStruct deviceState;
	u8_t currentMenu = MAIN_MENU;
	u8_t nextMenu = MAIN_MENU;

	deviceState.settings = deviceSettings;
	deviceState.modeChanged = 0;
	deviceState.menuSwitch = MENU_STAY;

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
				nextMenu = UI_DisplaySettingsMenu(&deviceState);
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

static u8_t modeChanged = 0;

static void UI_ModeSlaveListBoxCallback(WM_MESSAGE *pMsg)
{
	u16_t startY = 20;
	u16_t leftX = 10;
	WM_KEY_INFO key;
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
						modeChanged = 1;
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
			GUI_SetFont(&GUI_Font20_1);
			GUI_DispStringHCenterAt("Settings", LCD_GetXSize()/2, startY);
			GUI_DispStringAt("Mode:", leftX, startY + 2 * INC_YVALUE);
			GUI_DispStringAt("Address: ", leftX, startY + 3 * INC_YVALUE);
			GUI_DispStringAt("Baud: ", leftX, startY + 4 * INC_YVALUE);
			GUI_DispStringAt("Waiting time: ", leftX, startY + 5 * INC_YVALUE);
		}
		else
		if(pMsg->MsgId == WM_KEY)
		{
			key = *(WM_KEY_INFO*)(pMsg->Data.p);
			if(key.PressedCnt = 0)
			{

			}
		}
		else
			WM_DefaultProc(pMsg);
	}
}

MENU_SWITCH nextMenu = MENU_STAY;

static void UI_ModeMasterListBoxCallback(WM_MESSAGE *pMsg)
{
	u16_t startY = 20;
	u16_t leftX = 10;

	SPINBOX_Handle address;
	LISTBOX_Handle mode;
	LISTBOX_Handle baud;
	SPINBOX_Handle waitingTime;
	GUI_ConstString baudArray[] = {"1200", "2400", "9600", NULL};
	GUI_ConstString modeArray[] = {"Slave", "Master", NULL};
	WM_HMEM *focusArray[] = {&mode, &address, &baud, &waitingTime};
	u8_t focusCount = 0;
	WM_KEY_INFO key;
	UI_DeviceStateStruct *deviceState;
	u8_t num = 0;

	WM_GetUserData(pMsg->hWin, &deviceState, sizeof(deviceState));

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
			GUI_SetFont(&GUI_Font20_1);
			GUI_DispStringHCenterAt("Settings", LCD_GetXSize()/2, startY);
			GUI_DispStringAt("Mode:", leftX, startY + 2 * INC_YVALUE);
			GUI_DispStringAt("Address: ", leftX, startY + 3 * INC_YVALUE);
			GUI_DispStringAt("Baud: ", leftX, startY + 4 * INC_YVALUE);
			GUI_DispStringAt("Waiting time: ", leftX, startY + 5 * INC_YVALUE);
			mode = LISTBOX_CreateEx(140, startY + 2 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, 0, WIDGET_MODE_ID, modeArray);
			address = SPINBOX_CreateEx(140, startY + 3*INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, WIDGET_ADDRESS_ID, MODBUS_MIN_ADDRESS, MODBUS_MAX_ADDRESS);
			baud = LISTBOX_CreateEx(140, startY + 4 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, 0, WIDGET_BAUD_ID, baudArray);
			waitingTime = SPINBOX_CreateEx(140, startY + 5 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), pMsg->hWin, WM_CF_SHOW, WIDGET_WAITING_TIME_ID, 1, 250);
			LISTBOX_SetSel(mode, deviceState->settings.deviceMode);
			SPINBOX_SetValue(address, deviceState->settings.address);
			LISTBOX_SetSel(baud, deviceState->settings.baud);
			SPINBOX_SetValue(waitingTime, deviceState->settings.waitingTime);
			deviceState->modeChanged = 0;
			WM_SetFocus(*focusArray[focusCount]);
		}
		else
		if(pMsg->MsgId == WM_KEY)
		{
			key = *(WM_KEY_INFO*)(pMsg->Data.p);
			if(key.PressedCnt = 0)
			{
				switch (key.Key)
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
	}
}

MENU_SWITCH UI_DisplayMasterSettingsMenu(UI_DeviceStateStruct *deviceState)
{
	u16_t startY = 20;
	u16_t leftX = 10;
	u8_t key = 0;
	u8_t num = 0;
	u8_t focusCount = 0;
	WM_HWIN window;

	window = WM_CreateWindow(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_CF_SHOW, UI_ModeMasterListBoxCallback, sizeof(deviceState));
	num = WM_SetUserData(window, &deviceState, sizeof(deviceState));

	while(1)
	{
		while((!deviceState->modeChanged) && (deviceState->menuSwitch == MENU_STAY))
		{
			GUI_Delay(100);
		}
		deviceState->modeChanged = 0;
		if(deviceState->settings.deviceMode == MODE_MASTER)
			deviceState->settings.deviceMode = MODE_SLAVE;
		else
			deviceState->settings.deviceMode = MODE_MASTER;
		WM_Paint(window);
	}
	WM_DeleteWindow(window);
	return nextMenu;
}

MENU_SWITCH UI_DisplaySlaveSettingsMenu(DEVICE_SettingsStruct *settings)
{
	u16_t startY = 20;
	u16_t leftX = 10;
	u8_t key = 0;
	MENU_SWITCH nextMenu = MENU_STAY;
	SPINBOX_Handle address;
	LISTBOX_Handle mode;
	LISTBOX_Handle baud;
	SPINBOX_Handle waitingTime;
	GUI_ConstString baudArray[] = {"1200", "2400", "9600", NULL};
	GUI_ConstString modeArray[] = {"Slave", "Master", NULL};
	WM_HMEM *focusArray[] = {&mode, &address, &baud, &waitingTime};
	u8_t focusCount = 0;
	WM_HWIN window;

	window = WM_CreateWindow(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_CF_SHOW, UI_ModeSlaveListBoxCallback, 4);
	WM_SetUserData(window, settings, 4);

	mode = LISTBOX_CreateEx(140, startY + 2 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), window, WM_CF_SHOW, 0, WIDGET_MODE_ID, modeArray);
	address = SPINBOX_CreateEx(140, startY + 3*INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), window, WM_CF_SHOW, WIDGET_ADDRESS_ID, MODBUS_MIN_ADDRESS, MODBUS_MAX_ADDRESS);
	baud = LISTBOX_CreateEx(140, startY + 4 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), window, WM_CF_SHOW, 0, WIDGET_BAUD_ID, baudArray);
	waitingTime = SPINBOX_CreateEx(140, startY + 5 * INC_YVALUE, 60, GUI_GetYDistOfFont(GUI_GetFont()), window, WM_CF_SHOW, WIDGET_WAITING_TIME_ID, 1, 250);
	LISTBOX_SetSel(mode, settings->deviceMode);
	SPINBOX_SetValue(address, settings->address);
	LISTBOX_SetSel(baud, settings->baud);
	SPINBOX_SetValue(waitingTime, settings->waitingTime);
	modeChanged = 0;
	WM_SetFocus(*focusArray[focusCount]);
	
	while((!modeChanged) && (nextMenu == MENU_STAY))
	{
		GUI_ClearKeyBuffer();
		GUI_Delay(100);

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
				nextMenu = MENU_PREV;
				break;
			}
			default:
			{
				key = 0;
				break;
			}
		}
	}
	GUI_Clear();
	WM_DeleteWindow(window);
	WM_DeleteWindow(mode);
	WM_DeleteWindow(address);
	WM_DeleteWindow(baud);
	WM_DeleteWindow(waitingTime);
	return nextMenu;
}

MENU_SWITCH UI_DisplaySettingsMenu(UI_DeviceStateStruct *deviceState)
{
	MENU_SWITCH nextMenu = MENU_STAY;
	while(1)
	{
		//if(settings->deviceMode == MODE_SLAVE)
			//nextMenu = UI_DisplaySlaveSettingsMenu(settings);
		//else
			nextMenu = UI_DisplayMasterSettingsMenu(deviceState);

		while(nextMenu == MENU_STAY)
		{
			GUI_Delay(100);
		}

		/*if(nextMenu != MENU_STAY)
			return nextMenu;
		else
		{
			if(modeChanged)
			{
				modeChanged = 0;
				if(settings->deviceMode == MODE_SLAVE)
					settings->deviceMode = MODE_MASTER;
				else
					settings->deviceMode = MODE_SLAVE;
			}
		}*/
	}

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
