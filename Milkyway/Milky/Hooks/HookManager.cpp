#include "HookManager.h"

void HookManager::initHooks() {
	hooks.push_back(new KeyboardHook::Feed);
}