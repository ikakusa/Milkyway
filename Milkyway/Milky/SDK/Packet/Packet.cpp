#include "Packet.h"

std::string Packet::getName() {
	std::string* str = new std::string();
	std::string name = *CallVFunc<2, std::string*>(this, str);
	delete str;
	return name;
}

//1.21.4x
ModalFormResponsePacket::ModalFormResponsePacket() {
	static uintptr_t** ModalFormResponsePacketVtable = 0x0;
	if (ModalFormResponsePacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? 48 89 4D B0 89 45 E0"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		ModalFormResponsePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (ModalFormResponsePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ModalFormResponsePacket));
	vTable = ModalFormResponsePacketVtable;
}

ModalFormRequestPacket::ModalFormRequestPacket() {
	static uintptr_t** ModalFormRequestPacketVtable = 0x0;
	if (ModalFormRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8d 0d ? ? ? ? c7 40 ? ? ? ? ? c7 40 ? ? ? ? ? 48 89 48 ? c7 40 ? ? ? ? ? c7 40 ? ? ? ? ? 66 89 78 ? 48 89 78 ? 48 89 78 ? 89 78 ? 89 78 ? 0f 11 40 ? 48 89 78 ? 48 c7 40 ? ? ? ? ? 40 88 78 ? eb ? 48 8b c7 48 8d 48 ? 48 8d 15 ? ? ? ? 48 89 51 ? 48 89 43 ? 48 8b c3 48 89 0b 48 8b 5c 24 ? 48 83 c4 ? 5f c3 48 8d 0d ? ? ? ? e8 ? ? ? ? 83 3d ? ? ? ? ? 0f 85 ? ? ? ? 48 8d 0d ? ? ? ? e8 ? ? ? ? 48 8d 0d ? ? ? ? e8 ? ? ? ? e9 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc 48 89 5c 24 ? 57 48 83 ec ? 65 48 8b 04 25"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		ModalFormRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (ModalFormRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ModalFormRequestPacket));
	vTable = ModalFormRequestPacketVtable;
}
//

//1.21.4x
PlaySoundPacket::PlaySoundPacket() {
	static uintptr_t** PlaySoundPacketVtable = 0x0;
	if (PlaySoundPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 01 48 83 C1 ?? E8 ?? ?? ?? ?? 48 89 6E");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlaySoundPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
	}
}
//

//1.21.4x
PlayerAuthInputPacket::PlayerAuthInputPacket() {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 45 A0 0F 57 C0 0F 29 45 D0"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
}

PlayerAuthInputPacket::PlayerAuthInputPacket(vec3 pos, vec2 rot, float yawUnused) {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 45 A0 0F 57 C0 0F 29 45 D0"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
	this->rot = rot;
	this->pos = pos;
	this->yawUnused = yawUnused;
}
//

//1.21.4x
TextPacket::TextPacket() {
	static uintptr_t** textPacketVtable = 0x0;
	if (textPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 01 33 D2 48 89 51 ?? 0F 57 C0 48 89 51 ?? 48 8B C1 89 51"); // 
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		textPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (textPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif 
	}
	memset(this, 0, sizeof(TextPacket));  // Avoid overwriting vtable
	vTable = textPacketVtable;
}
//

//1.21.4x
InteractPacket::InteractPacket() {
	static uintptr_t** interactPacketVtable = 0x0;
	if (interactPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? 48 89 4D E7 C6 45 ?? ?? 48 89 45 ?? F2 0F 10 05 ?? ?? ?? ?? F2 0F 11 45 ?? 8B 05 ?? ?? ?? ?? 89 45 ?? 48 8D 15 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 90 48 8B 06 48 8B CE 48 8B 80 ?? ?? ?? ?? FF 15 ?? ?? ?? ?? 4C 8B C0 48 8B 08 48 8B 41 ?? 48 8D 55 E7 49 8B C8 FF 15 ?? ?? ?? ?? 90 48 8B 4D"); // 
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		interactPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (interactPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(InteractPacket)); // Avoid overwriting vtable
	vTable = interactPacketVtable;
}
//

//1.21.4x
CommandRequestPacket::CommandRequestPacket() {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? 48 89 48 ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? 66 89 78 ?? 48 89 78 ?? 48 89 78 ?? 89 78 ?? 0F 11 40 ?? 48 89 78 ?? 48 C7 40 ?? ?? ?? ?? ?? 40 88 78 ?? 40 88 78 ?? 48 89 78"); //
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		commandRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (commandRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));  // Avoid overwriting vtable
	vTable = commandRequestPacketVtable;
}

CommandRequestPacket::CommandRequestPacket(std::string cmd) {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? 48 89 48 ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? 66 89 78 ?? 48 89 78 ?? 48 89 78 ?? 89 78 ?? 0F 11 40 ?? 48 89 78 ?? 48 C7 40 ?? ?? ?? ?? ?? 40 88 78 ?? 40 88 78 ?? 48 89 78");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		commandRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (commandRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));  // Avoid overwriting vtable
	vTable = commandRequestPacketVtable;
	this->origin = Origin::PLAYER;
	this->isExternal = 0;
}
//

//1.21.4x
MovePlayerPacket::MovePlayerPacket() {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 42 ?? 48 8B 43"); // 
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		movePlayerPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (movePlayerPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MovePlayerPacket));  // Avoid overwriting vtable
	vTable = movePlayerPacketVtable;
}

MovePlayerPacket::MovePlayerPacket(Player* player, vec3 pos) {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 42 ?? 48 8B 43");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		movePlayerPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (movePlayerPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MovePlayerPacket));  // Avoid overwriting vtable
	vTable = movePlayerPacketVtable;
	entityRuntimeID = 1;
	this->Position = pos;
	this->pitch = pitch;
	this->yaw = yaw;
	this->headYaw = yaw;
	onGround = true;
	mode = 0;
}
//

//1.21.4x
InventoryTransactionPacket::InventoryTransactionPacket() {
	static uintptr_t** InventoryTransactionPacketVtable = 0x0;
	if (InventoryTransactionPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? 48 89 4D C7 48 8D 35");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		InventoryTransactionPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (InventoryTransactionPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(InventoryTransactionPacket));  // Avoid overwriting vtable
	vTable = InventoryTransactionPacketVtable;
}
//

//1.21.4x
PlayerHotbarPacket::PlayerHotbarPacket() {  // Client
	static uintptr_t** playerHotbarPacketVtable = 0x0;
	if (playerHotbarPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? 66 89 78 ?? 48 89 78 ?? 48 89 78 ?? 89 78 ?? 48 89 48 ?? 89 78 ?? 66 C7 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerHotbarPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerHotbarPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerHotbarPacket));  // Avoid overwriting vtable
	vTable = playerHotbarPacketVtable;
}

PlayerHotbarPacket::PlayerHotbarPacket(int selectedHotbarSlot, char containerId, bool selectHotbarSlot) {  // Client
	static uintptr_t** playerHotbarPacketVtable = 0x0;
	if (playerHotbarPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? C7 40 ?? ?? ?? ?? ?? 66 89 78 ?? 48 89 78 ?? 48 89 78 ?? 89 78 ?? 48 89 48 ?? 89 78 ?? 66 C7 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerHotbarPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerHotbarPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerHotbarPacket));  // Avoid overwriting vtable
	vTable = playerHotbarPacketVtable;
	this->selectedHotbarSlot = selectedHotbarSlot;
	this->containerId = containerId;
	this->selectHotbarSlot = selectHotbarSlot;
}
//

//1.21.4x

MobEquipmentPacket::MobEquipmentPacket(__int64 entityRuntimeId, ItemStack* item, int hotbarSlot, int inventorySlot) {
	memset(this, 0x0, sizeof(MobEquipmentPacket));
	using MobEquimentPacketConstructor_t = void(__fastcall*)(MobEquipmentPacket*, __int64, ItemStack*, int, int, char);
	static MobEquimentPacketConstructor_t MobEquimentPacketConstructor = reinterpret_cast<MobEquimentPacketConstructor_t>(SigScan("48 8D 05 ?? ?? ?? ?? 48 89 06 48 8B C6 4C 8D 9C 24"));

	if (MobEquimentPacketConstructor != 0)
		MobEquimentPacketConstructor(this, entityRuntimeId, item, hotbarSlot, inventorySlot, 0);
}
MobEquipmentPacket::MobEquipmentPacket() {
	static uintptr_t** PacketVtable = 0x0;
	if (PacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 06 48 8B C6 4C 8D 9C 24"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (PacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MobEquipmentPacket));  // Avoid overwriting vtable
	vTable = PacketVtable;
}

//

//1.21.4x
NetworkLatencyPacket::NetworkLatencyPacket() {
	static uintptr_t** networkLatencyPacketVtable = 0x0;
	if (networkLatencyPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 49 8B 40 ?? 48 89 44 24"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		networkLatencyPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (networkLatencyPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(NetworkLatencyPacket));  // Avoid overwriting vtable
	vTable = networkLatencyPacketVtable;
}
//

//1.21.4x
PlayerActionPacket::PlayerActionPacket() {
	static uintptr_t** playerActionPacketVtable = 0x0;
	if (playerActionPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ?? ?? ?? ?? 48 89 4C 24 ?? 66 0F 7F 45 A7"); // 
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerActionPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerActionPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerActionPacket));  // Avoid overwriting vtable
	vTable = playerActionPacketVtable;
}
//