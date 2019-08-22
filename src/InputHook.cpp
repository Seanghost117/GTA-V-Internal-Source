//InputHook.cpp
#include "stdafx.h"

#define GXLPARAM(lp) ((short)LOWORD(lp))
#define GYLPARAM(lp) ((short)HIWORD(lp))

InputHook iHook;
WNDPROC	oWndProc;

//using namespace Utility;

static std::set<InputHook::TKeyboardFn> g_keyboardFunctions;

void InputHook::keyboardHandlerRegister(TKeyboardFn function) {

	g_keyboardFunctions.insert(function);
}

void InputHook::keyboardHandlerUnregister(TKeyboardFn function) {

	g_keyboardFunctions.erase(function);
}

bool InputHook::Initialize() {

	hWindow = NULL;
	while (hWindow == NULL) {

		hWindow = FindWindow(L"grcWindow", NULL);
		Sleep(100);
	}
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	if (oWndProc == NULL) {

		Log::Error("Failed to attach input hook");
		return false;
	}
	else {
		keyboardHandlerRegister(OnKeyboardMessage);
		Log::Msg("Input hook attached:  WndProc 0x%p", (DWORD_PTR)oWndProc);
		enabled = true;
		return true;
	}
}

void InputHook::Remove() {
	if (enabled) {
		SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
		Log::Msg("Removed input hook");
	}

	enabled = false;
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MBUTTONDOWN:
		break;
	case WM_MBUTTONUP:
		break;
	case WM_MOUSEWHEEL:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_KEYDOWN: case WM_KEYUP: case WM_SYSKEYDOWN: case WM_SYSKEYUP:
	{
		auto functions = g_keyboardFunctions; for (auto & function : functions) function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
	}
		break;
	case WM_CHAR:
		break;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);

}
