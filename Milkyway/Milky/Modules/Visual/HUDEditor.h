#pragma once
#include "../Module.h"

class HUDEditor : public Module {
public:
	std::vector<HUD*> huds;
	HUDEditor() : Module('L', Category::RENDER, "HUDEditor", "Shows HUDEditor") {
	}
	virtual void onEnable() override { if (g_Data.getClientInstance()) { g_Data.getClientInstance()->releaseCursor(); } }
	virtual void onDisable() override { if (g_Data.getClientInstance()) { g_Data.getClientInstance()->grabCursor(); } }
	void setPosition();
};