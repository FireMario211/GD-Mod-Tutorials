#include "pch.h"
#include <imgui-hook.hpp>
#include <imgui.h>

bool show = true;
bool noclipEnabled = false;

void RenderMain() {
    if (show) {
        ImGui::Begin("Tutorial Mod");
        ImGui::Text("Welcome to Tutorial Mod 3!\nHere are some buttons you can press.");
        if (ImGui::Button("Mod Information")) {
            gd::FLAlertLayer::create(nullptr, "Tutorial Mod 3", "OK", nullptr, "Made by <cr>Fire</c>\nFor Mod Tutorial Part 3")->show();
        }
        if (ImGui::Checkbox("Noclip", &noclipEnabled)) { // Toggles noclip
            if (noclipEnabled) { // Noclip is enabled
                WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\xe9\x79\x06\x00\x00", 5, NULL);
            } else { // Noclip is disabled
                WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\x6a\x14\x8b\xcb\xff", 5, NULL);
            }
        }
        ImGui::Text("Press K to toggle this!");
        ImGui::End();
    }
}

DWORD WINAPI my_thread(void* hModule) {
    ImGuiHook::setRenderFunction(RenderMain);
    ImGuiHook::setToggleCallback([]() {
        show = !show; // Toggles imgui from showing (Press K to toggle)
    });
    if (MH_Initialize() == MH_OK) {
        ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
            MH_CreateHook(target, hook, trampoline); // Sets up hook for imgui
        });
        MH_EnableHook(MH_ALL_HOOKS);
    } else {
        // Comment this if this causes crashes.
        std::cout << "MinHook failed to load! Unlolading..." << std::endl;
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    }
    return true;
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

