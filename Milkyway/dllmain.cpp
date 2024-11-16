#include "dllmain.h"
#include "Milky/Hooks/HookManager.h"
#include "Milky/Utils/TextCol.h"
#include "Milky/Logger/Logger.h"
#include "Milky/Modules/ModuleManager.h"

bool dllmain::isRunning = true;
HMODULE dllmain::mod = nullptr;

auto GetDllMod(void) -> HMODULE {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetDllMod, &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? (HMODULE)info.AllocationBase : NULL;
}

DWORD WINAPI init(LPVOID lpParam) {
    FileUtils::createFolder("Milkyway");
    FileUtils::createAssetsFolder("Logs");
    FileUtils::createAssetsFolder("Audios");
    FileUtils::createAssetsFolder("Configs");
    FileUtils::createAssetsFolder("Assets");

    MH_Initialize();
    initColors();
    HookManager::initHooks();
    moduleMgr.Initialize();

    while (dllmain::isRunning) {
        if ((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::isKeyDown(VK_END)) {
            dllmain::isRunning = false;
            writelog("Ejecting...");
        }
        Sleep(100);
    }

    moduleMgr.get<ClickGui>()->setEnabled(false);
    moduleMgr.saveConfig();
    moduleMgr.uninitialize();
    HookManager::DeleteHooks();
    kiero::shutdown();
    MH_Uninitialize();
    Sleep(1000);
    writelog("Ejected!");

    FreeLibraryAndExitThread(GetDllMod(), 1);
    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        dllmain::mod = hModule;
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)init, hModule, NULL, NULL);
        DisableThreadLibraryCalls(hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

