#include "dllmain.h"

bool dllmain::isRunning = true;
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

    while (dllmain::isRunning) {
        if ((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::isKeyDown(VK_END)) {
            dllmain::isRunning = false;
            writelog("Ejecting...");
        }
        Sleep(100);
    }

    HookManager::DeleteHooks();
    MH_Uninitialize();
    Sleep(1000);
    writelog("Ejected!");

    FreeLibraryAndExitThread(GetDllMod(), 1);
    return 1;

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)init, hModule, NULL, NULL);
        DisableThreadLibraryCalls(hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

