#pragma once
#include "../Module.h"
#include "../ModuleManager.h"

class CPS : public Module {
public:
	bool isDragging = false;
	float posX = 100.f;
	float posY = 100.f;
	float fontSize = 1.f;
	CPS() : Module(VK_TAB, Category::COMBAT, "CPS", "Shows reach") {
		addFloat("Text size", &fontSize, 1.f, 0.1f, 4.f);
		addFloat("PosX", &posX, 100.f, 0.f, 1980.f);
		addFloat("PosY", &posY, 100.f, 0.f, 1080.f);
	}
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onImGuiRender(ImDrawList* d) override;
};