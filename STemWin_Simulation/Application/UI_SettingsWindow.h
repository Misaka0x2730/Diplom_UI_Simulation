#pragma once

#include "LCDConf.h"
#include "GUI.h"
#include "SPINBOX.h"
#include "TEXT.h"
#include "DROPDOWN.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"
#include "EDIT.h"
#include "UI_Struct.h"
#include "UI_Device.h"

void		UI_DisplaySettingsMenu(WM_HWIN parentWindow);
static void UI_DisplaySettingsSlaveMenu(WM_HWIN parentWindow);
static void UI_DisplaySettingsMasterMenu(WM_HWIN parentWindow);
static void UI_SettingsWindowCallback(WM_MESSAGE *pMsg);
static void UI_SettingsDialogCallback(WM_MESSAGE *pMsg);