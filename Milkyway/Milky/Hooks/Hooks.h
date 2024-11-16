#pragma once
#include "../GameData.h"
#include <vector>
#include <string>
#include <memory>
#include <Libraries.h>

#include "../Modules/ModuleManager.h"
class FuncHook;
class Hook {
public:
	std::string name = "";
	Hook(const char* a) {
		name = a;
	};
	virtual bool Initialize() = 0;
};