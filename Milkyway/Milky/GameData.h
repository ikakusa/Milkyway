#pragma once
#include <map>
#include <Math/Math.h>
#include "Memories/MemUtils.h"

extern class GameData g_Data;
class GameData {
private:
	class ClientInstance* clientInstace = nullptr;
	class GameMode* gameMode = nullptr;
	class LocalPlayer* localPlayer = nullptr;
	class GuiData* guiData = nullptr;
	struct vec2 mousePos;
	std::map<unsigned char, bool> keymap;
public:
	static bool isKeyDown(unsigned int key) { return g_Data.keymap[key]; }
	void updateGameData(unsigned char key, bool isDown) { this->keymap[key] = isDown; }
};

