#include "ClientInstanceHook.h"

static std::chrono::time_point<std::chrono::steady_clock> lastExecutionTime;
void ClientInstanceHook::Update::handle(ClientInstance* _this, bool isInitFinished) {
	static auto oFunc = funcPtr->GetFastcall<void, ClientInstance*, bool>();
	g_Data.setClientInstance(_this);
	g_Data.setLocalPlayer(_this->getLocalPlayer());
	if (_this->guiData) {
		g_Data.setGuiData(_this->guiData);
	}
	std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedTime = currentTime - lastExecutionTime;
	if (elapsedTime.count() >= 1.f) {
		g_Data.cpsLeft = g_Data.cpsLeft2;
		g_Data.cpsLeft2 = 0;
		g_Data.cpsRight = g_Data.cpsRight2;
		g_Data.cpsRight2 = 0;

		lastExecutionTime = std::chrono::steady_clock::now();
	}
	return oFunc(_this, isInitFinished);
}

void ClientInstanceHook::MinecraftHook::update::handle(MinecraftGame* _this) {
	static auto oFunc = funcPtr->GetFastcall<void, MinecraftGame*>();
	g_Data.setMCGame(_this);
	return oFunc(_this);
}