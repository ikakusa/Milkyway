#pragma once
#include "../Module.h"

class Brightness : public Module {
public:
	Brightness() : Module(VK_TAB, Category::RENDER, "Brightness", "this can change ur brightness") {}
	virtual void onEnable() override;
	virtual void onDisable() override;
};