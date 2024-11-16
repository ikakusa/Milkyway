#include "ClientInstanceHook.h"

void ClientInstanceHook::Update::handle(ClientInstance* _this, bool isInitFinished) {
	static auto oFunc = funcPtr->GetFastcall<void, ClientInstance*, bool>();
	g_Data.setClientInstance(_this);
	g_Data.setLocalPlayer(_this->getLocalPlayer());
	if (_this->guiData) {
		g_Data.setGuiData(_this->guiData);
	}
	return oFunc(_this, isInitFinished);
}

void ClientInstanceHook::MinecraftHook::update::handle(MinecraftGame* _this) {
	static auto oFunc = funcPtr->GetFastcall<void, MinecraftGame*>();
	g_Data.setMCGame(_this);
	return oFunc(_this);
}