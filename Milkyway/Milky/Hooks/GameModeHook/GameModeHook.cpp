#include "GameModeHook.h"

static std::chrono::time_point<std::chrono::steady_clock> lastExecutionTime;
float GameModeHook::getPickRange::handle(GameMode* gm, __int64 inputMode, bool isVR) {
	static auto oFunc = funcPtr->GetFastcall<float, GameMode*, __int64, bool>();
	std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedTime = currentTime - lastExecutionTime;
	if (elapsedTime.count() >= 10.f) {
		g_Data.reach = 0.f;
		g_Data.reachStr = "0.0";
	}
	return oFunc(gm, inputMode, isVR);
}

bool GameModeHook::startDestroyBlock::handle(GameMode* gm, vec3i blockPos, int face) {
	static auto oFunc = funcPtr->GetFastcall<bool, GameMode*, vec3i, int>();
	return oFunc(gm, blockPos, face);
}

void GameModeHook::attack::handle(GameMode* gm, Actor* ent) {
	static auto oFunc = funcPtr->GetFastcall<void, GameMode*, Actor*>();
	lastExecutionTime = std::chrono::steady_clock::now();
	g_Data.reach = toFixed(g_Data.getLocalPlayer()->state->Position.dist(ent->state->Position), 1);
	g_Data.reachStr = removeZero(std::to_string(toFixed(g_Data.getLocalPlayer()->state->Position.dist(ent->state->Position), 1)));
	return oFunc(gm, ent);
}