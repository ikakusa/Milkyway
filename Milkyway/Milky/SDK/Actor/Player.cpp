#include "Player.h"
#include "../Packet/Packet.h"
#include "../Item/ItemStack.h"
#include "../../GameData.h"
void Player::setHotbarSlot(int slot, bool silent) {
	if (!silent) Supplies->setselectedHotbarSlot(slot);
	PlayerHotbarPacket hotbar;
	hotbar.containerId = 10;
	hotbar.selectHotbarSlot = true;
	hotbar.selectedHotbarSlot = slot;
	MobEquipmentPacket p(this->getRuntimeIDComponent()->runtimeid, this->Supplies->GetItemAtSlot(slot), slot, slot);
	g_Data.getClientInstance()->loopbackSender->sendToServer(&p);
	g_Data.getClientInstance()->loopbackSender->sendToServer(&hotbar);
}