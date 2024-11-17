#pragma once
#define WIN32_LEAN_AND_MEAN
#include <map>
#include <Libraries.h>

struct HUD {
	std::string name;
	vec2* pos;
	vec4* rect;

	HUD(std::string name, vec2* pos, vec4* rect) {
		this->name = name;
		this->pos = pos;
		this->rect = rect;
	}
};

extern class GameData g_Data;
class ClientInstance;
class GameData {
public:
	static inline bool isMidClickDown = false;
	static inline bool isRightClickDown = false;
	static inline bool isLeftClickDown = false;

	static inline int cpsLeft = 0;
	static inline int cpsLeft2 = 0;
	static inline int cpsRight = 0;
	static inline int cpsRight2 = 0;

	static inline bool rightClick = false;
	static inline bool leftClick = false;
	static inline bool midClick = false;
	static inline std::map<std::string, bool> hudmap;
	static inline std::string dragModule;
	static inline std::vector<HUD*> hud = {};

	ClientInstance* clientinstance = nullptr;
	MinecraftGame* mcGame = nullptr;
	GameMode* gamemode = nullptr;
	LocalPlayer* localPlayer = nullptr;
	GuiData* guiData = nullptr;
	float reach = 0.f;
	std::string reachStr = "0.0";
	struct vec2 mousePos;
	std::map<unsigned char, bool> keymap;
	float deltatime = 1.f;
public:
	static bool isKeyDown(unsigned int key) { return g_Data.keymap[key]; }
	void updateGameData(unsigned char key, bool isDown) { this->keymap[key] = isDown; }
	ClientInstance* getClientInstance() {
		return g_Data.clientinstance;
	}

	void setClientInstance(ClientInstance* ci) { g_Data.clientinstance = ci; };
	void setLocalPlayer(LocalPlayer* lp) { g_Data.localPlayer = lp; };
	void setGuiData(GuiData* gd) { g_Data.guiData = gd; };
	void setMCGame(MinecraftGame* mc) { g_Data.mcGame = mc; }

	LocalPlayer* getLocalPlayer() {
		return g_Data.localPlayer;
	}

	MinecraftGame* getMCGame() {
		return g_Data.mcGame;
	}

	GuiData* getGuiData() {
		return g_Data.guiData;
	}
};