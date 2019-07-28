#pragma once

class Log
{
public:
	static void Init(HMODULE hModule);
#ifdef _DEBUG
	static void Debug(const char* fmt, ...);
#endif
	static void Msg(const char* fmt, ...);
	static void Error(const char* fmt, ...);
	static void Fatal(const char* fmt, ...);
};