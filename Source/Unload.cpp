#include "stdafx.h"
LPVOID Unload::yoink;
bool Unload::handle_unload = false;


void Unload::unload_handler() {

	if (Unload::handle_unload) {

		fclose(stdout);

		fclose(stdin);

		fclose(stderr);



		FreeConsole();



		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(yoink), 1);

	}

}



DWORD WINAPI Unload::main(const LPVOID lpvoid) {

	Hooking::Start((HMODULE)lpvoid);
	Unload::yoink = lpvoid;



	if (AllocConsole()) {

		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

		freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);

		freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);

	}



	while (true) {

		//std::cout << "Looped." << '\n';



		Unload::unload_handler();



		std::this_thread::yield();

	}



	// if code somehow reaches here

	return FALSE;

}