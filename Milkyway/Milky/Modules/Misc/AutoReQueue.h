#pragma once
#include "../Module.h"

class AutoRequeue : public Module {
public:
	AutoRequeue() : Module('M', Category::MISC, "AutoRequeue", "Automatically requeue in the hive") {}
};