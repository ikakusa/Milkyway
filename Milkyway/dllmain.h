﻿#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class dllmain {
public:
	static HMODULE mod;
	static bool isRunning;
};