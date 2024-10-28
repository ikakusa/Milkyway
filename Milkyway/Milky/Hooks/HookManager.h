#pragma once
#include "Hooks.h"

//Hooks
#include "KeymapHook/KeymapHook.h"
#include "CommandHook/CommandHook.h"
#include "TrialManager/TrialManager.h"
//
class Hook;
class HookManager {
private:
	static inline std::vector<Hook*> hooks;
public:
	static void initHooks();
	static void DeleteHooks() {
		hooks.clear();
	}
};