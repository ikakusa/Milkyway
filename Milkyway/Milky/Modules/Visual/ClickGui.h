#pragma once
#include "../Module.h"

class ClickGui : public Module {
public:
	static inline float yCatOff = 0.f;
	std::string text = "a";
	static inline vec4 catRect;
	static inline vec4 guiRect;
	float percent = 0.f;
	ClickGui() : Module(VK_INSERT, Category::RENDER, "ClickGui", "Shows clickgui") {
		text = "a";
	}
	virtual void onEnable() override { if (g_Data.getClientInstance()) { ImGuiUtils::searchQuery.clear(); g_Data.getClientInstance()->releaseCursor(); } }
	virtual void onDisable() override { if (g_Data.getClientInstance()) { ImGuiUtils::searchQuery.clear (); g_Data.getClientInstance()->grabCursor(); } }
};