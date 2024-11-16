#pragma once
#include "../Module.h"

class NotificationMod : public Module {
public:
	NotificationMod() : Module(0x58, Category::RENDER, "NotificationMod", "Shows notification when module toggled") {
	}
};