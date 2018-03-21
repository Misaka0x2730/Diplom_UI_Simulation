#pragma once

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef signed char s8_t;
typedef signed short s16_t;
typedef signed int s32_t;

typedef enum DEVICE_MODES
{
	MODE_MASTER = 0,
	MODE_SLAVE = 1
}DEVICE_MODES;

typedef enum DEVICE_STATES
{
	STATE_STOP = 0,
	STATE_RUN = 1
}DEVICE_STATES;

typedef enum KEY_STATES
{
	KEY_NOT_PRESSED = 0,
	KEY_PRESSED = 1,
	KEY_NOT_DETERMINED = -1
}KEY_STATES;

typedef enum MENU_STATES
{
	MAIN_MENU = 0,
	SETTINGS_MENU = 1
}KEY_STATES;

typedef enum MENU_SWITCH
{
	MENU_NEXT = 0,
	MENU_PREV = 1,
	MENU_STAY = 2
}MENU_SWITCH;

#define INC_YVALUE	20