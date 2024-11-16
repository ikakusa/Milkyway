#pragma once
#include "Hooks.h"

//Hooks
#include "RenderCtxHook/RenderCtxHook.h"
#include "FreeLibsAndExitHook/FreeLibsAndExitHook.h"
#include "KeymapHook/KeymapHook.h"
#include "CommandHook/CommandHook.h"
#include "DirectXHook/DirectXHook.h"
#include "TrialManager/TrialManager.h"
#include "ClientInstanceHook/ClientInstanceHook.h"
#include "ActorHook/ActorHook.h"
#include "Concre/Concre.h"
#include "GameModeHook/GameModeHook.h"
#include "LoopbackPacketSender/LoopbackHook.h"
#include "FontHook/FontHook.h"
#include "OptionsHook/OptionsHook.h"
#include "ItemHook/ItemHook.h"
#include "MouseDevice/MouseDevice.h"
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