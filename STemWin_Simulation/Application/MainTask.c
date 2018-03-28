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
#include "EDIT.h"
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

//MENU_SWITCH UI_DisplayMainMenu(DEVICE_MODES mode, DEVICE_STATES state, s16_t temp, u16_t pressure, u16_t humidity);
//MENU_SWITCH UI_DisplaySettingsMenu(UI_DeviceStateStruct *deviceState);

void UI_DisplaySettingsSlaveMenu(WM_HWIN parentWindow);
void UI_DisplaySettingsMasterMenu(WM_HWIN parentWindow);
void UI_DisplaySettingsMenu(WM_HWIN parentWindow);
void UI_DisplayMainMenu(WM_HWIN parentWindow);

static const GUI_WIDGET_CREATE_INFO settingsSlaveDialogCreate[] = {
	{ FRAMEWIN_CreateIndirect,	"Settings",				WIDGET_FRAME_SLAVE_ID,		0,		0,						XSIZE_PHYS, YSIZE_PHYS,  0, 0 },
	{ TEXT_CreateIndirect,		"Mode:",				0,							LEFT_X, TOP_Y + 1 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Address:",				0,							LEFT_X, TOP_Y + 2 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Baud:",				0,							LEFT_X, TOP_Y + 3 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Waiting time:",		0,							LEFT_X, TOP_Y + 4 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ LISTBOX_CreateIndirect,	NULL,					WIDGET_MODE_ID,				170,	TOP_Y + 1 * INC_YVALUE, 120,		FONT_HEIGHT, 0, 0 },
	{ SPINBOX_CreateIndirect,	NULL,					WIDGET_ADDRESS_ID,			170,	TOP_Y + 2 * INC_YVALUE, 120,		FONT_HEIGHT, 0, 0 },
	{ LISTBOX_CreateIndirect,	NULL,					WIDGET_BAUD_ID,				170,	TOP_Y + 3 * INC_YVALUE,	120,		FONT_HEIGHT, 0, 0 },
	{ SPINBOX_CreateIndirect,	NULL,					WIDGET_WAITING_TIME_ID,		170,	TOP_Y + 4 * INC_YVALUE,	120,		FONT_HEIGHT, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO settingsMasterDialogCreate[] = {
	{ FRAMEWIN_CreateIndirect,	"Settings",				WIDGET_FRAME_MASTER_ID,		0,		0,						XSIZE_PHYS, YSIZE_PHYS,  0, 0 },
	{ TEXT_CreateIndirect,		"Mode:",				0,							LEFT_X, TOP_Y + 1 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Address:",				0,							LEFT_X, TOP_Y + 2 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Baud:",				0,							LEFT_X, TOP_Y + 3 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Interview preiod:",	0,							LEFT_X, TOP_Y + 4 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ LISTBOX_CreateIndirect,	NULL,					WIDGET_MODE_ID,				170,	TOP_Y + 1 * INC_YVALUE, 120,		FONT_HEIGHT, 0, 0 },
	{ SPINBOX_CreateIndirect,	NULL,					WIDGET_ADDRESS_ID,			170,	TOP_Y + 2 * INC_YVALUE, 120,		FONT_HEIGHT, 0, 0 },
	{ LISTBOX_CreateIndirect,	NULL,					WIDGET_BAUD_ID,				170,	TOP_Y + 3 * INC_YVALUE,	120,		FONT_HEIGHT, 0, 0 },
	{ SPINBOX_CreateIndirect,	NULL,					WIDGET_PERIOD_ID,			170,	TOP_Y + 4 * INC_YVALUE,	120,		FONT_HEIGHT, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO mainMenuDialogCreate[] = {
	{ FRAMEWIN_CreateIndirect,	"Main Menu",			WIDGET_FRAME_MAIN_ID,		0,		0,						XSIZE_PHYS, YSIZE_PHYS,  0, 0 },
	{ TEXT_CreateIndirect,		"Current Mode:",		0,							LEFT_X, TOP_Y + 1 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Current State:",		0,							LEFT_X, TOP_Y + 2 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Temperature:",			0,							LEFT_X, TOP_Y + 3 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Pressure:",			0,							LEFT_X, TOP_Y + 4 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"Humidity:",			0,							LEFT_X, TOP_Y + 5 * INC_YVALUE, 140,		FONT_HEIGHT, 0, 0 },

	{ EDIT_CreateIndirect,		NULL,					WIDGET_TEXT_MODE_ID,		170, TOP_Y + 1 * INC_YVALUE,	80,		FONT_HEIGHT, 0, 0 },
	{ EDIT_CreateIndirect,		NULL,					WIDGET_TEXT_STATE_ID,		170, TOP_Y + 2 * INC_YVALUE,	80,		FONT_HEIGHT, 0, 0 },
	{ EDIT_CreateIndirect,		NULL,					WIDGET_TEXT_TEMP_ID,		170, TOP_Y + 3 * INC_YVALUE,	80,		FONT_HEIGHT, 0, 0 },
	{ EDIT_CreateIndirect,		NULL,					WIDGET_TEXT_PRESSURE_ID,	170, TOP_Y + 4 * INC_YVALUE,	80,		FONT_HEIGHT, 0, 0 },
	{ EDIT_CreateIndirect,		NULL,					WIDGET_TEXT_RH_ID,			170, TOP_Y + 5 * INC_YVALUE,	80,		FONT_HEIGHT, 0, 0 },

	{ TEXT_CreateIndirect,		"°C",					0,							270, TOP_Y + 3 * INC_YVALUE,	40,			FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"kPa",					0,							270, TOP_Y + 4 * INC_YVALUE,	40,			FONT_HEIGHT, 0, 0 },
	{ TEXT_CreateIndirect,		"%",					0,							270, TOP_Y + 5 * INC_YVALUE,	40,			FONT_HEIGHT, 0, 0 },
};

u16_t Device_GetMode()
{
	return MODE_SLAVE;
}

u16_t Device_GetState()
{
	return STATE_STOP;
}

s32_t Device_GetTemp()
{
	return 233;
}

u32_t Device_GetPressure()
{
	return 1000;
}

u16_t Device_GetRH()
{
	return 20;
}

void Device_Run()
{

}

void Device_Stop()
{

}


static void UI_SettingsDialogCallback(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;
	GUI_ConstString modeArray[] = {"Slave", "Master"};
	GUI_ConstString baudArray[] = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"};
	static u8_t changeFlag = 0;
	static WM_HWIN focusArray[4] = {0};
	switch (pMsg->MsgId)
	{
		case MESSAGE_CREATE:
		{
			WM_HWIN hItem = WM_GetDialogItem(hWin, WIDGET_MODE_ID);
			for (u8_t i = 0; i < GUI_COUNTOF(modeArray); i++)
				LISTBOX_AddString(hItem, modeArray[i]);
			LISTBOX_SetFont(hItem, &MAIN_FONT);
			focusArray[0] = hItem;

			hItem = WM_GetDialogItem(hWin, WIDGET_ADDRESS_ID);
			SPINBOX_SetRange(hItem, MODBUS_MIN_ADDRESS, MODBUS_MAX_ADDRESS);
			SPINBOX_SetFont(hItem, &MAIN_FONT);
			focusArray[1] = hItem;

			hItem = WM_GetDialogItem(hWin, WIDGET_BAUD_ID);
			for (u8_t i = 0; i < GUI_COUNTOF(baudArray); i++)
				LISTBOX_AddString(hItem, baudArray[i]);
			LISTBOX_SetFont(hItem, &MAIN_FONT);
			focusArray[2] = hItem;

			if (WM_GetId(hWin) == WIDGET_FRAME_SLAVE_ID)
			{
				hItem = WM_GetDialogItem(hWin, WIDGET_WAITING_TIME_ID);
				SPINBOX_SetRange(hItem, 1, 250);
				SPINBOX_SetFont(hItem, &MAIN_FONT);
				focusArray[3] = hItem;
			}
			else
			{
				hItem = WM_GetDialogItem(hWin, WIDGET_PERIOD_ID);
				SPINBOX_SetRange(hItem, 1, 250);
				SPINBOX_SetFont(hItem, &MAIN_FONT);
				focusArray[3] = hItem;
			}
			
			FRAMEWIN_SetTextAlign(hWin, GUI_TA_HCENTER);
			FRAMEWIN_SetFont(hWin, &MAIN_FONT);

			changeFlag = 1;
			LISTBOX_SetSel((LISTBOX_Handle)(WM_GetDialogItem(hWin, WIDGET_MODE_ID)), pMsg->Data.v);
			break;
		}
		case WM_NOTIFY_PARENT:
		{
			int ID = WM_GetId(pMsg->hWinSrc);
			int Ncode = pMsg->Data.v;
			switch (ID)
			{
				case WIDGET_MODE_ID:
				{
					switch (Ncode)
					{
						case WM_NOTIFICATION_SEL_CHANGED:
						{
							if (!changeFlag)
							{
								WM_MESSAGE messageToParent;
								messageToParent.MsgId = MESSAGE_SETTINGS_MODE_CHANGED;
								messageToParent.Data.v = LISTBOX_GetSel((LISTBOX_Handle)(pMsg->hWinSrc));
								WM_SendToParent(hWin, &messageToParent);
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}
		case WM_KEY:
		{
			WM_KEY_INFO key = *(WM_KEY_INFO*)(pMsg->Data.p);
			if (key.PressedCnt == 0)
			{
				switch (key.Key)
				{
					case GUI_KEY_ENTER:
					{
						u8_t i = 0;
						for (i = 0; i < GUI_COUNTOF(focusArray); i++)
						{
							if (WM_GetFocussedWindow() == focusArray[i])
								break;
						}
						if (i != (GUI_COUNTOF(focusArray) - 1))
							WM_SetFocus(focusArray[++i]);
						else
							WM_SetFocus(focusArray[0]);
						break;
					}
					case GUI_KEY_LEFT:
					{
						WM_MESSAGE messageToParent;
						messageToParent.MsgId = MESSAGE_MENU_CHANGED_PREV;
						messageToParent.Data.v = SETTINGS_MENU;
						WM_SendToParent(hWin, &messageToParent);
						break;
					}
				}
			}
			break;
		}
		default:
		{
			WM_DefaultProc(pMsg);
			break;
		}
	}
	changeFlag = 0;
}

void UI_MainMenuInitEdit(WM_HWIN hWin)
{
	WM_HWIN hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_MODE_ID);

	EDIT_SetFont(hItem, &MAIN_FONT);
	EDIT_SetTextMode(hItem);

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_STATE_ID);
	EDIT_SetFont(hItem, &MAIN_FONT);
	EDIT_SetTextMode(hItem);

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_TEMP_ID);
	EDIT_SetFont(hItem, &MAIN_FONT);
	EDIT_SetDecMode(hItem, Device_GetTemp(), -999, 999, 1, GUI_EDIT_SIGNED);
	EDIT_SetMaxLen(hItem, 5);

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_PRESSURE_ID);
	EDIT_SetFont(hItem, &MAIN_FONT);
	EDIT_SetDecMode(hItem, Device_GetPressure(), 0, 2000, 1, GUI_EDIT_NORMAL);

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_RH_ID);
	EDIT_SetFont(hItem, &MAIN_FONT);
	EDIT_SetDecMode(hItem, Device_GetRH(), 0, 99, 0, GUI_EDIT_NORMAL);
	EDIT_SetMaxLen(hItem, 2);
}

void UI_MainMenuSetValue(WM_HWIN hWin)
{
	GUI_ConstString modeArray[] = { "Slave", "Master" };
	GUI_ConstString stateArray[] = { "Stop", "Run" };

	WM_HWIN hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_MODE_ID);
	EDIT_SetText(hItem, modeArray[Device_GetMode()]);

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_STATE_ID);
	EDIT_SetText(hItem, stateArray[Device_GetState()]);

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_TEMP_ID);
	EDIT_SetValue(hItem, Device_GetTemp());

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_PRESSURE_ID);
	EDIT_SetValue(hItem, Device_GetPressure());

	hItem = WM_GetDialogItem(hWin, WIDGET_TEXT_RH_ID);
	EDIT_SetValue(hItem, Device_GetRH());
}

static void UI_MainMenuDialogCallback(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;
	GUI_ConstString modeArray[] = { "Slave", "Master" };
	GUI_ConstString stateArray[] = { "Stop", "Run" };
	GUI_ConstString baudArray[] = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };
	static WM_HWIN focusArray[4] = { 0 };
	switch (pMsg->MsgId)
	{
		case MESSAGE_CREATE:
		{
			FRAMEWIN_SetTextAlign(hWin, GUI_TA_HCENTER);
			FRAMEWIN_SetFont(hWin, &MAIN_FONT);
			WM_HTIMER timer = WM_CreateTimer(WM_GetClientWindow(hWin), 0, 500, 0);
			UI_MainMenuInitEdit(hWin);
			UI_MainMenuSetValue(hWin);
			break;
		}
		case WM_TIMER:
		{
			UI_MainMenuSetValue(hWin);
			WM_RestartTimer((WM_HTIMER)(pMsg->Data.v), 500);
			break;
		}
		default:
		{
			WM_DefaultProc(pMsg);
			break;
		}
	}
}

/*void UI_MenuTask()
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
}*/

static void UI_SettingsWindowCallback(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case MESSAGE_CREATE:
	{
		break;
	}
	case MESSAGE_SETTINGS_MODE_CHANGED:
	{
		u8_t mode = pMsg->Data.v;
		WM_DeleteWindow(pMsg->hWinSrc);
		if (mode == MODE_SLAVE)
			UI_DisplaySettingsSlaveMenu(hWin);
		else
			UI_DisplaySettingsMasterMenu(hWin);
		break;
	}
	case MESSAGE_MENU_CHANGED_NEXT:
	case MESSAGE_MENU_CHANGED_PREV:
	{
		WM_MESSAGE messageToParent;
		messageToParent.MsgId = pMsg->MsgId;
		messageToParent.Data.v = pMsg->Data.v;
		WM_SendToParent(hWin, &messageToParent);
		break;
	}
	default:
	{
		WM_DefaultProc(pMsg);
		break;
	}
	}
}

static void UI_MainMenuWindowCallback(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;

	switch (pMsg->MsgId)
	{
		case MESSAGE_CREATE:
		{
			break;
		}
		case WM_KEY:
		{
			WM_KEY_INFO key = *(WM_KEY_INFO*)(pMsg->Data.p);
			if (key.PressedCnt == 0)
			{
				switch (key.Key)
				{
					case GUI_KEY_RIGHT:
					{
						WM_MESSAGE messageToParent;
						messageToParent.MsgId = MESSAGE_MENU_CHANGED_NEXT;
						messageToParent.Data.v = MAIN_MENU;
						WM_SendToParent(hWin, &messageToParent);
						break;
					}
				}
			}
			break;
		}
		case MESSAGE_MENU_CHANGED_NEXT:
		case MESSAGE_MENU_CHANGED_PREV:
		{
			WM_MESSAGE messageToParent;
			messageToParent.MsgId = pMsg->MsgId;
			messageToParent.Data.v = pMsg->Data.v;
			WM_SendToParent(hWin, &messageToParent);
			break;
		}
		default:
		{
			WM_DefaultProc(pMsg);
			break;
		}
	}
}

void UI_DisplaySettingsSlaveMenu(WM_HWIN parentWindow)
{
	WM_HWIN dialog = GUI_CreateDialogBox(settingsSlaveDialogCreate, GUI_COUNTOF(settingsSlaveDialogCreate), UI_SettingsDialogCallback, parentWindow, 0, 0);
	WM_SetFocus(dialog);
	WM_MESSAGE messageToDialog;
	messageToDialog.MsgId = MESSAGE_CREATE;
	messageToDialog.Data.v = MODE_SLAVE;
	WM_SendMessage(WM_GetClientWindow(dialog), &messageToDialog);
}

void UI_DisplaySettingsMasterMenu(WM_HWIN parentWindow)
{
	WM_HWIN dialog = GUI_CreateDialogBox(settingsMasterDialogCreate, GUI_COUNTOF(settingsMasterDialogCreate), UI_SettingsDialogCallback, parentWindow, 0, 0);
	WM_SetFocus(dialog);
	WM_MESSAGE messageToDialog;
	messageToDialog.MsgId = MESSAGE_CREATE;
	messageToDialog.Data.v = MODE_MASTER;
	WM_SendMessage(WM_GetClientWindow(dialog), &messageToDialog);
}

void UI_DisplaySettingsMenu(WM_HWIN parentWindow)
{
	TEXT_SetDefaultFont(&MAIN_FONT);
	WM_HWIN settingsWindow = WM_CreateWindowAsChild(0, 0, LCD_GetXSize(), LCD_GetYSize(), parentWindow, WM_CF_SHOW, UI_SettingsWindowCallback, 0);
	UI_DisplaySettingsSlaveMenu(settingsWindow);
}

void UI_DisplayMainMenu(WM_HWIN parentWindow)
{
	TEXT_SetDefaultFont(&MAIN_FONT);
	WM_HWIN mainWindow = WM_CreateWindowAsChild(0, 0, LCD_GetXSize(), LCD_GetYSize(), parentWindow, WM_CF_SHOW, UI_MainMenuWindowCallback, 0);
	WM_HWIN dialog = GUI_CreateDialogBox(mainMenuDialogCreate, GUI_COUNTOF(mainMenuDialogCreate), UI_MainMenuDialogCallback, mainWindow, 0, 0);
	WM_SetFocus(WM_GetClientWindow(dialog));
	WM_MESSAGE messageToDialog;
	messageToDialog.MsgId = MESSAGE_CREATE;
	WM_SendMessage(WM_GetClientWindow(dialog), &messageToDialog);
}

static void UI_MainWindowCallback(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;
	static u8_t currentMenu = MAIN_MENU;
	switch (pMsg->MsgId)
	{
		case MESSAGE_CREATE:
		{
			//UI_DisplaySettingsMenu(hWin);
			UI_DisplayMainMenu(hWin);
			break;
		}
		case WM_KEY:
		{
			WM_DefaultProc(pMsg);
			break;
		}
		case MESSAGE_MENU_CHANGED_NEXT:
		{
			u8_t menu = pMsg->Data.v;
			switch (menu)
			{
				case MAIN_MENU:
				{
					WM_DeleteWindow(pMsg->hWinSrc);
					UI_DisplaySettingsMenu(hWin);
					break;
				}
			}
			break;
		}
		case MESSAGE_MENU_CHANGED_PREV:
		{
			u8_t menu = pMsg->Data.v;
			switch (menu)
			{
				case SETTINGS_MENU:
				{
					WM_DeleteWindow(pMsg->hWinSrc);
					UI_DisplayMainMenu(hWin);
					break;
				}
			}
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
	WM_HWIN window = WM_CreateWindow(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_CF_SHOW, UI_MainWindowCallback, 16);
	WM_SendMessageNoPara(window, MESSAGE_CREATE);
	GUI_Clear();
	while (1)
	{
		GUI_Delay(100);
	}
}

/*MENU_SWITCH UI_DisplayMainMenu(DEVICE_MODES mode, DEVICE_STATES state, s16_t temp, u16_t pressure, u16_t humidity)
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
}*/

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

/*MENU_SWITCH UI_DisplaySettingsMenu(UI_DeviceStateStruct *deviceState)
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
}*/

void MainTask(void) 
{
	GUI_Init();
	GUI_Clear();
	GUI_SetFont(&MAIN_FONT);
	UI_MenuTask();
	while(1);
}

/*************************** End of file ****************************/
