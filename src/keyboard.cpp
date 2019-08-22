//keyboard.cpp
#include "stdafx.h"

const int KEYS_SIZE = 255;

DWORD trainerResetTime = 0;

bool gameInputDisabledByUs = false;
bool gameInputBlockedByUs = false;

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

bool KeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool KeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}
#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000
bool KeyPressedOnce(bool& bIsPressed, DWORD vk)
{
	if (IsKeyPressed(vk))
	{
		if (bIsPressed == false)
		{
			bIsPressed = true;
			return true;
		}
	}
	else if (bIsPressed == true)
	{
		bIsPressed = false;
	}
	return false;
}

bool trainer_switch_pressed()
{
	bool result = KeyJustUp(VK_F4);
	return result;
}

void reset_trainer_switch()
{
	trainerResetTime = GetTickCount();
}

void get_button_state(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r)
{
	if (a) *a = KeyDown(VK_NUMPAD5);
	if (b) *b = KeyJustUp(VK_NUMPAD0);
	if (up) *up = KeyDown(VK_NUMPAD8);
	if (down) *down = KeyDown(VK_NUMPAD2);
	if (r) *r = KeyDown(VK_NUMPAD6);
	if (l) *l = KeyDown(VK_NUMPAD4);
}

void menu_beep(int snd)
{
	switch (snd)
	{
		case NAV_SELECT: AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FREEMODE_SOUNDSET", 1);
		case NAV_CANCEL: AUDIO::PLAY_SOUND_FRONTEND(-1, "CANCEL", "HUD_FREEMODE_SOUNDSET", 1);
		case NAV_UP_DOWN: AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FREEMODE_SOUNDSET", 1);
		case NAV_LEFT_RIGHT: AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FREEMODE_SOUNDSET", 1);
		default: break;
	}
}

void setGameInputToEnabled(bool enabled, bool force)
{
	if (enabled && (gameInputDisabledByUs || force))
	{
		PLAYER::SET_PLAYER_CONTROL(0, 1, 0);
		//CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(1);
		gameInputDisabledByUs = false;
	}
	else if (!enabled)
	{
		PLAYER::SET_PLAYER_CONTROL(0, 0, 256);
		//CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(1);
		gameInputDisabledByUs = true;
	}
}