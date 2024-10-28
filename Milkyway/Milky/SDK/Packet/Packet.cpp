#include "Packet.h"

std::string Packet::getName() {
	std::string* str = new std::string();
	std::string name = *CallVFunc<2, std::string*>(this, str);
	delete str;
	return name;
}

ModalFormResponsePacket::ModalFormResponsePacket() {
	static uintptr_t** ModalFormResponsePacketVtable = 0x0;
	if (ModalFormResponsePacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 45 E7 44 89 45"); // 1.21
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
		uintptr_t sigOffset = SigScan("48 8d 0d ? ? ? ? 48 89 4d ? 89 5d ? 0f 57 c0 0f 11 45 ? 48 89 7d ? 48 89 7d ? 4c 8b 40 ? 48 83 78 ? ? 72 ? 48 8b 00 48 8b d0 48 8d 4d ? e8 ? ? ? ? 90 48 8b 55 ? 48 83 fa ? 72 ? 48 ff c2 48 8b 4d ? 48 8b c1 48 81 fa ? ? ? ? 72 ? 48 83 c2 ? 48 8b 49 ? 48 2b c1 48 83 c0 ? 48 83 f8 ? 76 ? ff 15 ? ? ? ? cc e8 ? ? ? ? 66 0f 6f 05 ? ? ? ? f3 0f 7f 45 ? c6 45 ? ? 4c 89 6c 24 ? 48 8d 4c 24 ? e8 ? ? ? ? 48 8d 05 ? ? ? ? 48 89 44 24 ? 49 8b 8f ? ? ? ? 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 48 8b d8 48 8b 00 4c 8b 58 ? 41 8b 47 ? 89 44 24 ? 48 8d 54 24 ? 49 8b 4f ? e8 ? ? ? ? 4c 8d 45 ? 48 8b d0 48 8b cb 49 8b c3 ff 15 ? ? ? ? 48 8d 55 ? 49 8b ce e8 ? ? ? ? 90 48 8d 4d ? e8 ? ? ? ? 48 8d 05 ? ? ? ? 48 89 45 ? 80 7d ? ? 74 ? 48 8b 4d ? 48 85 c9 74 ? 8b 45 ? 39 41 ? 75 ? 48 8b 39 48 85 ff 74 ? 0f 10 45 ? 0f 29 45 ? 48 8d 55 ? 48 8b cf e8 ? ? ? ? 90 48 8d 05 ? ? ? ? 48 89 45 ? 48 8b ce e8 ? ? ? ? 49 8b c6 48 8b 4d ? 48 33 cc e8 ? ? ? ? 48 81 c4 ? ? ? ? 41 5f 41 5e 41 5d 5f 5e 5b 5d c3 cc cc cc cc cc cc cc cc cc cc cc cc 48 89 5c 24 ? 48 89 4c 24"); // 1.21
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

PlayerAuthInputPacket::PlayerAuthInputPacket() {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 01 F2 0F 10 42 ? F2 0F 11 41 ? F2 0F 10 42 ?"); // 1.21
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
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 01 F2 0F 10 42 ? F2 0F 11 41 ? F2 0F 10 42 ?"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
	this->rot = rot;
	this->pos = pos;
	this->yawUnused = yawUnused;
}

TextPacket::TextPacket() {
	static uintptr_t** textPacketVtable = 0x0;
	if (textPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 8B F9 48 89 01 48 8B 99 ?? ?? ?? ?? 48 8B A9"); // 
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

InteractPacket::InteractPacket() {
	static uintptr_t** interactPacketVtable = 0x0;
	if (interactPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 45 E7 C6 45 17 06 48 89 4D 1F F2 0F 10 05 ? ? ? ? F2 0F 11 45 ? 8B 05 ? ? ? ? 89 45 2F 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 90 48 8B 07 48 8B CF 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 4C 8B C0 48 8B 08 48 8B 41 08 48 8D 55 E7 49 8B C8 FF 15 ? ? ? ? 90 48 8B 4D 37 48 33 CC E8 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B 28 49 8B 73 30 49 8B E3 41 5E 5F 5D"); // 
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

CommandRequestPacket::CommandRequestPacket() {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 73 28 48 89 43 10 C7 43 ? ? ? ? ? C7 43 ? ? ? ? ? 66 89 73 20 48 89 73 30 89 73 38 0F 11 43 40 48 89 73 50 48 C7 43 ? ? ? ? ? 40 88 73 40 40 88 73 60 48 89 73 68 48 89 73"); //
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
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 73 28 48 89 43 10 C7 43 ? ? ? ? ? C7 43 ? ? ? ? ? 66 89 73 20 48 89 73 30 89 73 38 0F 11 43 40 48 89 73 50 48 C7 43 ? ? ? ? ? 40 88 73 40 40 88 73 60 48 89 73 68 48 89 73");
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

MovePlayerPacket::MovePlayerPacket() {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 43 08 48 8B 46 30 48 89 43 38 F2 0F 10 46 ? F2 0F 11 43 ? 8B 46 40 89 43 48 F2 0F 10 46 ? F2 0F 11 43 ? 8B 46 4C 89 43 54 48 8B C7 0F B6 4E 50 88 4B 58 0F"); // 
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
		uintptr_t sigOffset = SigScan("48 8D 05 ? ? ? ? 48 89 43 08 48 8B 46 30 48 89 43 38 F2 0F 10 46 ? F2 0F 11 43 ? 8B 46 40 89 43 48 F2 0F 10 46 ? F2 0F 11 43 ? 8B 46 4C 89 43 54 48 8B C7 0F B6 4E 50 88 4B 58 0F");
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
InventoryTransactionPacket::InventoryTransactionPacket() {
	static uintptr_t** InventoryTransactionPacketVtable = 0x0;
	if (InventoryTransactionPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? C7 43 ?? ?? ?? ?? ?? 48 89 43 ?? 48 8D 05 ?? ?? ?? ?? 48 89 43 ?? C7 43 ?? ?? ?? ?? ?? C7 43");
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
PlayerHotbarPacket::PlayerHotbarPacket() {  // Client
	static uintptr_t** playerHotbarPacketVtable = 0x0;
	if (playerHotbarPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 85 ?? ?? ?? ?? 89 8D ?? ?? ?? ?? C6 85 ?? ?? ?? ?? ?? 88 95 ?? ?? ?? ?? 48 8B 8F");
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
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 48 89 85 ?? ?? ?? ?? 89 8D ?? ?? ?? ?? C6 85 ?? ?? ?? ?? ?? 88 95 ?? ?? ?? ?? 48 8B 8F");
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

MobEquipmentPacket::MobEquipmentPacket(__int64 entityRuntimeId, ItemStack* item, int hotbarSlot, int inventorySlot) {
	memset(this, 0x0, sizeof(MobEquipmentPacket));
	using MobEquimentPacketConstructor_t = void(__fastcall*)(MobEquipmentPacket*, __int64, ItemStack*, int, int, char);
	static MobEquimentPacketConstructor_t MobEquimentPacketConstructor = reinterpret_cast<MobEquimentPacketConstructor_t>(SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 81 EC ?? ?? ?? ?? 41 8B F9 48"));

	if (MobEquimentPacketConstructor != 0)
		MobEquimentPacketConstructor(this, entityRuntimeId, item, hotbarSlot, inventorySlot, 0);
}
MobEquipmentPacket::MobEquipmentPacket() {
	static uintptr_t** PacketVtable = 0x0;
	if (PacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8d 05 ? ? ? ? 48 89 06 48 8b c6 4c 8d 9c 24 ? ? ? ? 49 8b 5b ? 49 8b 73 ? 49 8b e3 5f c3 cc cc cc cc cc cc cc cc cc cc cc cc cc"); // 1.21
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (networkLatencyPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MobEquipmentPacket));  // Avoid overwriting vtable
	vTable = PacketVtable;
}

NetworkLatencyPacket::NetworkLatencyPacket() {
	static uintptr_t** networkLatencyPacketVtable = 0x0;
	if (networkLatencyPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 05 ?? ?? ?? ?? 0F 11 43 10"); // 1.21
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

PlayerActionPacket::PlayerActionPacket() {
	static uintptr_t** playerActionPacketVtable = 0x0;
	if (playerActionPacketVtable == 0x0) {
		uintptr_t sigOffset = SigScan("48 8D 0D ? ? ? ? 48 89 4C 24 ? 0F 57 C0 66 0F 7F 44 24 ? 66 0F 6F 0D ? ? ? ? 66 0F 7F 4C 24 ? 48 89 84 24 ? ? ? ? 40 88 BC 24 ? ? ? ? 48 8B 8B ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 40 08 FF 15 ? ? ? ? 89 BB ? ? ? ? 48 8B 03 41 B0 01 8D 57 38 48 8B CB 48 8B 40 08 FF 15 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 33 CC E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 48 81 C4 ? ? ? ? 5F C3"); // 
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
