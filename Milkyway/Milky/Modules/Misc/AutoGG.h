#pragma once
#include "../Module.h"

class AutoGG : public Module {
public:
	AutoGG() : Module('M', Category::MISC, "AutoGG", "Automatically sends GG to the chat") {}
};