#pragma once
#include "Hooks.h"

//Hooks
#include "KeymapHook/KeymapHook.h"
//

class HookManager {
public:
	static std::vector<Hook*> hooks;
	static void initHooks();
};