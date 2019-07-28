#pragma once
namespace Unload {
	extern LPVOID yoink;
	extern bool handle_unload;
	void unload_handler();
	DWORD WINAPI main(const LPVOID lpvoid);
}