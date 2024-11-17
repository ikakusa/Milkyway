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

bool ActorHook::Hurt::handle(Actor* ent, ActorDamageByActorSource* src, int damage, bool knoick, bool ignite) {
	static auto oFunc = funcPtr->GetFastcall<bool, Actor*, ActorDamageSource*, int, bool, bool>();
	return oFunc(ent, src, damage, knoick, ignite);
}