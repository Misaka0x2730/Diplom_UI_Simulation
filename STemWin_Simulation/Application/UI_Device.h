#pragma once

#include "types.h"
#include "UI_Struct.h"

typedef struct
{
	u8_t deviceMode;
	u8_t deviceState;
	u8_t address;
	u8_t baud;
	u16_t waitingTime;
	u16_t interviewPeriod;
	u32_t recv;
	u32_t transm;
}DEVICE_SettingsStruct;

void Device_NullStats();
u32_t Device_GetReceived();
u32_t Device_GetTransmitted();
void Device_IncRecv();
void Device_IncTransm();

u8_t Device_GetAddress();
void Device_SetAddress(u8_t address);
u8_t Device_GetBaud();
void Device_SetBaud(u8_t baud);
u16_t Device_GetWaitingTime();
void Device_SetWaitingTime(u16_t waitingTime);
u16_t Device_GetInterviewPeriod();
void Device_SetInterviewPeriod(u16_t interviewPeriod);

s32_t Device_GetTemp();
u32_t Device_GetPressure();
u16_t Device_GetRH();

u16_t Device_GetMode();
void Device_SetMode(u8_t mode);

u16_t Device_GetState();
void Device_SetState(u8_t state);
void Device_SwitchState();

