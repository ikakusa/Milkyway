#include "ActorHook.h"

void ActorHook::LocalPlayerHook::NormalTick::handle(Actor* lp) {
	static auto oFunc = funcPtr->GetFastcall<void, Actor*>();
	g_Data.localPlayer = (LocalPlayer*)lp;
	return oFunc(lp);
}

int ActorHook::MobHook::getCurrentSwingDurationHook::handle(Actor* ent) {
	static auto oFunc = funcPtr->GetFastcall<int, Actor*>();
	if (g_Data.getLocalPlayer() && ent == g_Data.getLocalPlayer()) {
		return 30;
	}
	return oFunc(ent);
}