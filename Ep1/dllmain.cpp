// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "PauseLayer.h"



DWORD WINAPI my_thread(void* hModule) {
    if (MH_Initialize() != MH_OK) {
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    }
    /*AllocConsole();
    SetConsoleTitleA("mod lol");
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    */

    //MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1E4620), PauseLayer_Hook, reinterpret_cast<void**>(&PauseLayer_init));
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1E4620), PauseLayer::hook, reinterpret_cast<void**>(&PauseLayer::init));
    MH_EnableHook(MH_ALL_HOOKS);
    
    //This line will dettach your DLL when executed. Remove if needed
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

