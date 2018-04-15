#include "UI_Device.h"

static u8_t currentState = STATE_STOP;
static u8_t currentMode = MODE_SLAVE;
static DEVICE_SettingsStruct settings = { MODE_SLAVE, STATE_STOP, 1, 2, 3, 4, 0, 0};

void Device_NullStats()
{
	settings.recv = 0;
	settings.transm = 0;
}

u32_t Device_GetReceived()
{
	return settings.recv;
}

u32_t Device_GetTransmitted()
{
	return settings.transm;
}

void Device_IncRecv()
{
	settings.recv++;
}

void Device_IncTransm()
{
	settings.transm++;
}

u8_t Device_GetAddress()
{
	return settings.address;
}

void Device_SetAddress(u8_t address)
{
	settings.address = address;
}

u8_t Device_GetBaud()
{
	return settings.baud;
}

void Device_SetBaud(u8_t baud)
{
	settings.baud = baud;
}

u16_t Device_GetWaitingTime()
{
	return settings.waitingTime;
}

void Device_SetWaitingTime(u16_t waitingTime)
{
	settings.waitingTime = waitingTime;
}

u16_t Device_GetInterviewPeriod()
{
	return settings.interviewPeriod;
}
void Device_SetInterviewPeriod(u16_t interviewPeriod)
{
	settings.interviewPeriod = interviewPeriod;
}

u16_t Device_GetMode()
{
	return settings.deviceMode;
}

void Device_SetMode(u8_t mode)
{
	settings.deviceMode = mode;
}

u16_t Device_GetState()
{
	return settings.deviceState;
}

void Device_SetState(u8_t state)
{
	settings.deviceState = state;
}

void Device_SwitchState()
{
	if (Device_GetState() == STATE_RUN)
		Device_SetState(STATE_STOP);
	else
		Device_SetState(STATE_RUN);
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