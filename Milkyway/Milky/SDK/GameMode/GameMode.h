#pragma once
#include <MemUtils.h>
#include <Math/Math.h>
#include <functional>
#include "../Item/ItemStack.h"
#include "../Actor/Player.h"
#include "../Block/Block.h"
class Actor;
class Player;
class GameMode {
public:
	virtual void destructor(); // 0
	virtual bool startDestroyBlock(vec3i const &, unsigned char, bool&); // 1
	virtual bool destroyBlock(vec3i*, unsigned char); // 2
	virtual bool continueDestroyBlock(vec3i const&, unsigned char, const vec3&, bool&); // 3
	virtual void stopDestroyBlock(vec3i const&); // 4
	virtual void startBuildBlock(vec3i const&, unsigned char); // 5
	virtual bool buildBlock(vec3i*, unsigned char, bool); // 6
	virtual void continueBuildBlock(vec3i const&, unsigned char); // 7
	virtual void stopBuildBlock(); // 8
	virtual void tick(); // 9
	virtual float getPickRange(__int64, bool); // 10
	virtual bool useItem(ItemStack&); // 11
	virtual __int64 useItemOn(ItemStack&, vec3i*, unsigned char, const vec3&, const Block*); // 12
	virtual bool interact(Actor&, const vec3&); // 13
	virtual bool attack(Actor*); // 14
	virtual void releaseUsingItem(); // 15
	virtual void unknown_16(); // 16
	virtual bool hasGetStrictParsingVersion(); // 17
	virtual void exitVRMode(std::function<void()>); // 18
	bool tryPlace(vec3i pos);
public:
	Player* player;
private:
	char pad_0008[8];
	char pad_0010[8];
	char pad_0018[4];      
public:
	//float destroyProgress;
	BUILD_ACCESS(float, destroyProgress, 0x24);
	void baseUseItem(ItemStack* stack) {
		using baseUseItem = void (*)(GameMode*, ItemStack*);
		static baseUseItem baseUseItemFunc = reinterpret_cast<baseUseItem>(SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 90 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 ?? 48 8B F2 48 8B F9 45 33 F6 4C 89 75 ?? 48 8D 4D ?? E8 ?? ?? ?? ?? 90 48")); // 1.21.2
		return baseUseItemFunc(this, stack);
	}

	float getDestroyRate(Block* block) {
		using getDestroyRateFunc = float(__fastcall*)(GameMode*, Block*);
		static getDestroyRateFunc Func = (getDestroyRateFunc)(SigScan("48 89 5c 24 ? 57 48 83 ec ? 48 8b f9 0f 29 74 24 ? 48 8b 49 ? e8")); // 1.21.2
		return Func(this, block);
	}
};