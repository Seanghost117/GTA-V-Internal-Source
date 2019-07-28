#pragma once
//K Don't need any useless mismatching
namespace Unload {
	extern LPVOID Gotem;
	extern bool handle_unload;
	void unload_handler();
	DWORD WINAPI main(const LPVOID lpvoid);
}
