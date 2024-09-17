#include "HookManager.h"

void HookManager::initHooks() {
	hooks.push_back(new KeyboardHook::Feed());
	hooks.push_back(new TrialManagerHook::IsTrial());

	for (auto hook : hooks) {
		if (hook->Initialize()) {
			writelog("%s has been initialized", hook->name.c_str());
		}
		MH_EnableHook(MH_ALL_HOOKS);
	}
}