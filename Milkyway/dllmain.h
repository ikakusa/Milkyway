#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>

#include <filesystem>
namespace fs = std::filesystem;

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

#include <MinHook.h>
#include "Milky/Logger/Logger.h"
#include "Libraries/Libraries.h"
#include "Milky/Hooks/Hooks.h"
#include "Milky/Hooks/HookManager.h"
#include "Milky/GameData.h"