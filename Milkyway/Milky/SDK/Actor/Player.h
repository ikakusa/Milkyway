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
	BUILD_ACCESS(PlayerInventoryProxy*, Supplies, 0x760);
	void setHotbarSlot(int slot, bool silent = false);
};