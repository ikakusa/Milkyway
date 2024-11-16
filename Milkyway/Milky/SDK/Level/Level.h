#pragma once
#include <vector>
#include <unordered_map>
#include "../Actor/Actor.h"

class HitResult {
public:
	Actor* getEntity() {
		using getEntity = Actor*(*)(HitResult*);
		static getEntity getEnt = reinterpret_cast<getEntity>(SigScan("48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 8D 51 ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? 80 7C 24 ?? ?? 74 31"));//dead
		return getEnt(this);
	}
    BUILD_ACCESS(__int64, type, 0x18);
    vec3 startPos;
    vec3 rayHitVec;
    int rayHitType;
    int blockSide;
    vec3i block;
    vec3 pos;
    Actor* entity;
    bool IsHitLiquid;
    int LiquidFacing;
    vec3i Liquid;
    vec3 LiquidPos;
    bool IndirectHit;
};
class Level {
public:
    typedef std::unordered_map<__int64, PlayerListEntry> playerListdef;
	std::vector<Actor*> getRuntimeActorList();
    playerListdef* getPlayerList() {
        return *reinterpret_cast<playerListdef**>(this + 0xBF0);
    }

	BUILD_ACCESS(HitResult*, hitResult, 0x0B38);
};