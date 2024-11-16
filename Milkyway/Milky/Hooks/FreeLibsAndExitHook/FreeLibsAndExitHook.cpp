#include "FreeLibsAndExitHook.h"
#include "../HookManager.h"
#include "../../dllmain.h"

void FreeLibsAndExitHook::Exit::handle(HMODULE mod, DWORD code) {
	static auto oFunc = funcPtr->GetFastcall<void, HMODULE, DWORD>();
	if (dllmain::isRunning&& mod == dllmain::mod) {
		dllmain::isRunning = false;
		return;
	}
	return oFunc(mod, code);
}
