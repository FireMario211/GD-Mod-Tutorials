#include "pch.h"
#include "PauseLayer.h"

DWORD WINAPI my_thread(void* hMod) {
    if (MH_Initialize() != MH_OK) {
        // Deattach the DLL file by freeing the library and exiting the thread
        FreeLibraryAndExitThread(
            reinterpret_cast<HMODULE>(hMod),
            0
        );
        // Reinterpreting cast due to hMod being void*, and FreeLibraryAndExitThread accepts HMODULE as the 1st param
    }
    // PauseLayer::init = base + 0x1E4620
    MH_CreateHook(
        reinterpret_cast<void*>(gd::base + 0x1E4620),
        PauseLayer::hook,
        reinterpret_cast<void**>(&PauseLayer::init)
    );
    MH_EnableHook(MH_ALL_HOOKS); // Enables all hooks
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // Creating a thread
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    }
    return TRUE;
}