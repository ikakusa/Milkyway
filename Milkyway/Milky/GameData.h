#pragma once
#include <map>
#include <Math/Math.h>
#include "SDK/SDK.h"

extern class GameData g_Data;
class ClientInstance;
class GameData {
public:
	ClientInstance* clientinstance = nullptr;
	MinecraftGame* mcGame = nullptr;
	GameMode* gamemode = nullptr;
	GuiData* guiData = nullptr;
	struct vec2 mousePos;
	std::map<unsigned char, bool> keymap;
public:
	static bool isKeyDown(unsigned int key) { return g_Data.keymap[key]; }
	void updateGameData(unsigned char key, bool isDown) { this->keymap[key] = isDown; }
	ClientInstance* getClientInstance() {
		return g_Data.clientinstance;
	}

	GuiData* getGuiData() {
		return g_Data.guiData;
	}
};

