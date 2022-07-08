#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "memory.h"
#include "proc.h"

DWORD WINAPI Thread(HMODULE hModule)
{
	/* Create Console */
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "Lexa's Internal\n";

	/* Get Module */
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

	bool healthSwitch = false;
	bool rifleAmmoSwitch = false;
	bool pistolAmmoSwitch = false;
	bool grenadeSwitch = false;

	/* Hack Loop */
	while (true)
	{
		/* Key Input*/
		/* Hack */
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			healthSwitch = !healthSwitch;
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			rifleAmmoSwitch = !rifleAmmoSwitch;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			pistolAmmoSwitch = !pistolAmmoSwitch;
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			grenadeSwitch = !grenadeSwitch;
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			return 0;
		}

		/* Freeze */
		uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10f4f4);

		if (localPlayerPtr)
		{
			if (healthSwitch)
			{
				*(int*)(*localPlayerPtr + 0xf8) = 1337;
			}

			if (rifleAmmoSwitch)
			{
				*(int*)(*localPlayerPtr + 0x150) = 1337;
			}

			if (pistolAmmoSwitch)
			{
				*(int*)(*localPlayerPtr + 0x13c) = 1337;
			}

			if (grenadeSwitch)
			{
				*(int*)(*localPlayerPtr + 0x158) = 1337;
			}
		}
	}

	/* Clean Up */
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, hModule, 0, nullptr));
	}

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}
