#pragma once

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef signed char s8_t;
typedef signed short s16_t;
typedef signed int s32_t;

#define MODBUS_MIN_ADDRESS 1
#define MODBUS_MAX_ADDRESS 247

#define WIDGET_MODE_ID				(GUI_ID_USER + 0)
#define WIDGET_ADDRESS_ID			(GUI_ID_USER + 1)
#define WIDGET_BAUD_ID				(GUI_ID_USER + 2)
#define WIDGET_WAITING_TIME_ID		(GUI_ID_USER + 3)
#define WIDGET_FRAME_SLAVE_ID		(GUI_ID_USER + 4)
#define WIDGET_FRAME_MASTER_ID		(GUI_ID_USER + 5)
#define WIDGET_PERIOD_ID			(GUI_ID_USER + 6)
#define WIDGET_FRAME_MAIN_ID		(GUI_ID_USER + 7)

#define WIDGET_TEXT_MODE_ID			(GUI_ID_USER + 8)
#define WIDGET_TEXT_STATE_ID		(GUI_ID_USER + 9)
#define WIDGET_TEXT_TEMP_ID			(GUI_ID_USER + 10)
#define WIDGET_TEXT_PRESSURE_ID		(GUI_ID_USER + 11)
#define WIDGET_TEXT_RH_ID			(GUI_ID_USER + 12)

#define MESSAGE_SET_DATA					(WM_USER + 0)
#define MESSAGE_CREATE						(WM_USER + 1)
#define MESSAGE_MENU_CHANGED_NEXT			(WM_USER + 2)
#define MESSAGE_MENU_CHANGED_PREV			(WM_USER + 3)
#define MESSAGE_SETTINGS_MODE_CHANGED		(WM_USER + 4)

#define LEFT_X	10
#define TOP_Y	20

typedef struct 
{
	u8_t deviceMode;
	u8_t address;
	u8_t baud;
	u16_t waitingTime;
}DEVICE_SettingsStruct;

typedef enum
{
	MODE_SLAVE = 0,
	MODE_MASTER = 1
}DEVICE_MODES;

typedef enum
{
	STATE_STOP = 0,
	STATE_RUN = 1
}DEVICE_STATES;

typedef enum
{
	KEY_NOT_PRESSED = 0,
	KEY_PRESSED = 1,
	KEY_NOT_DETERMINED = -1
}KEY_STATES;

typedef enum
{
	MENU_NONE = 0,
	MAIN_MENU = 1,
	SETTINGS_MENU = 2
}KEY_STATES;

typedef enum
{
	MENU_NEXT = 0,
	MENU_PREV = 1,
	MENU_STAY = 2
}MENU_SWITCH;

typedef struct 
{
	MENU_SWITCH menuSwitch;
	u8_t modeChanged;
	DEVICE_SettingsStruct settings;
}UI_DeviceStateStruct;

#define INC_YVALUE	28
#define FONT_HEIGHT	24
#define MAIN_FONT GUI_Font20_1