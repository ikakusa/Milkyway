#pragma once
#include "Actor.h"
#include "Mob.h"

class ContainerManagerModel;
class PlayerInventoryProxy;
class SerializedSkin;
class Player : public Mob {
public:
	BUILD_ACCESS(SerializedSkin, serializedSkin, 0x780);
	BUILD_ACCESS(ContainerManagerModel*, containerManagerModel, 0x750);
	BUILD_ACCESS(PlayerInventoryProxy*, Supplies, 0x628);
	void setHotbarSlot(int slot, bool silent = false);
public:
	std::string* getName() {
		using name = std::string*(*)(Player*);
		static name func = reinterpret_cast<name>(SigScan("48 83 EC ?? 4C 8B 51 ?? 8B 49 ?? 49 8B 52 ?? 49 8B 42 ?? 4D 8B 4A ?? 48 2B C2 48 C1 F8 ?? 48 FF C8 25 22"));
		return func(this);
	}
};