#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <cstdarg>
#include <cstdlib>
#include <Psapi.h>
#include <memory>
#include <utility>
#include <vector>

#include <MinHook/MinHook.h>
#include "Milky/Utils/Utility.h"
#include "Milky/Utils/TextCol.h"
#include "Milky/Logger/Logger.h"
#include "Libraries/Libraries.h"
#include "Milky/Hooks/Hooks.h"
#include "Milky/Hooks/HookManager.h"
#include "Milky/GameData.h"
#include "Milky/SDK/SDK.h"

class dllmain {
public:
	static bool isRunning;
};