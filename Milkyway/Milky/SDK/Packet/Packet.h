#pragma once
#include <system_error>
#include <bitset>
#include <vector>
#include <string>
#include <Math/Math.h>
#include <MemUtils.h>

class ItemStack;
class Packet {
public:
	uintptr_t** vTable;  //0x0000
private:
	char pad_0x8[0x28];
public:
	std::string getName();
	template <class T>
	bool isInstanceOf() {
		T packet;
		if (packet.vTable == this->vTable)
			return true;
		else
			return false;
	}
};

enum class InputData : int {
	Ascend = 0x0,
	Descend = 0x1,
	NorthJump = 0x2,
	JumpDown = 0x3,
	SprintDown = 0x4,
	ChangeHeight = 0x5,
	Jumping = 0x6,
	AutoJumpingInWater = 0x7,
	Sneaking = 0x8,
	SneakDown = 0x9,
	Up = 0xA,//forward
	Down = 0xB,//backward
	Left = 0xC,
	Right = 0xD,
	UpLeft = 0xE,
	UpRight = 0xF,
	WantUp = 0x10,
	WantDown = 0x11,
	WantDownSlow = 0x12,
	WantUpSlow = 0x13,
	Sprinting = 0x14,
	AscendBlock = 0x15,
	DescendBlock = 0x16,
	SneakToggleDown = 0x17,
	PersistSneak = 0x18,
	StartSprinting = 0x19,
	StopSprinting = 0x1A,
	StartSneaking = 0x1B,
	StopSneaking = 0x1C,
	StartSwimming = 0x1D,
	StopSwimming = 0x1E,
	StartJumping = 0x1F,
	StartGliding = 0x20,
	StopGliding = 0x21,
	PerformItemInteraction = 0x22,
	PerformBlockActions = 0x23,
	PerformItemStackRequest = 0x24,
	HandledTeleport = 0x25,
	Emoting = 0x26,
	MissedSwing = 0x27,
	StartCrawling = 0x28,
	StopCrawling = 0x29,
	StartFlying = 0x2A,
	StopFlying = 0x2B,
	ReceivedServerData = 0x2C,
	InClientPredictedInVehicle = 0x2D,
	PaddlingLeft = 0x2E,
	PaddlingRight = 0x2F,
};

class ModalFormResponsePacket : public Packet {
public:
	BUILD_ACCESS(std::string, JSONResponse, 0x30);
public:
	ModalFormResponsePacket();
};

class ModalFormRequestPacket : public Packet {
public:
	BUILD_ACCESS(std::string, JSONRequest, 0x30);
public:
	ModalFormRequestPacket();
};

enum class PlayerActionType {
	START_DESTROY_BLOCK,
	ABORT_DESTROY_BLOCK,
	STOP_DESTROY_BLOCK,
	GET_UPDATED_BLOCK,
	DROP_ITEM,
	START_SLEEPING,
	STOP_SLEEPING,
	RESPAWN,
	START_JUMP,
	START_SPRINTING,
	STOP_SPRINTING,
	START_SNEAKING,
	STOP_SNEAKING,
	CREATIVE_DESTROY_BLOCK,
	CHANGE_DIMENSION_ACK,
	START_GLIDING,
	STOP_GLIDING,
	DENY_DESTROY_BLOCK,
	CRACK_BLOCK,
	CHANGE_SKIN,
	UPDATED_ENCHANTING_SEED,
	START_SWIMMING,
	STOP_SWIMMING,
	START_SPIN_ATTACK,
	STOP_SPIN_ATTACK,
	INTERACT_WITH_BLOCK,
	PREDICT_DESTROY_BLOCK,
	CONTINUE_DESTROY_BLOCK,
	START_ITEM_USE_ON,
	STOP_ITEM_USE_ON,
	HANDLED_TELEPORT,
	MISSED_SWING,
	START_CRAWLING,
	STOP_CRAWLING,
	START_FLYING,
	STOP_FLYING
};

class BlockPos {

};
class PlayerBlockActionData {
public:
	PlayerActionType action;
	BlockPos position;
	int facing;
};

class PlayerBlockActions {
public:
	std::vector<PlayerBlockActionData> mActions;
};

class PlayerAuthInputPacket : public Packet {
public:
	vec2 rot; //0x0030
	vec3 pos; //0x0038
	float yawUnused; //0x0044
	vec3 velocity; //0x0048
	vec2 VehicleRotation; //0x0054
	vec2 AnalogMoveVector;
	vec2 MoveVector; //0x005C
	char pad_0050[12]; //0x0054
	std::bitset<39> flags; //0x0070
	__int64 inputMode; //0x0078
	__int64 clientPlayMode;
	__int64 interactionModel; // 0x007C (size: 4)
	uint64_t ticksAlive; //0x0088
	__int64 itemUseTransaction;
	__int64 itemStackRequest;
	PlayerBlockActions playerBlockActions;

	inline bool hasFlag(InputData flag) const {
		return this->flags.test(static_cast<size_t>(flag));
	}
	inline void setFlag(InputData flag, bool toggle = true) {
		this->flags.set(static_cast<size_t>(flag), toggle);
	}

public:
	PlayerAuthInputPacket();
	PlayerAuthInputPacket(vec3 pos, vec2 rot, float yawUnused);
public:
	void Copy(PlayerAuthInputPacket* other) {
		rot = other->rot;
		pos = other->pos;
		yawUnused = other->yawUnused;
		velocity = other->velocity;
		VehicleRotation = other->VehicleRotation;
		AnalogMoveVector = other->AnalogMoveVector;
		MoveVector = other->MoveVector;
		flags = other->flags;
		inputMode = other->inputMode;
		clientPlayMode = other->clientPlayMode;
		interactionModel = other->interactionModel;
		ticksAlive = other->ticksAlive;
		playerBlockActions = other->playerBlockActions;
		playerBlockActions.mActions = other->playerBlockActions.mActions;
	}
};

enum class TextPacketType : char {
	Raw = 0x0,
	Chat = 0x1,
	Translate = 0x2,
	Popup = 0x3,
	JukeboxPopup = 0x4,
	Tip = 0x5,
	SystemMessage = 0x6,
	Whisper = 0x7,
	Announcement = 0x8,
	TextObjectWhisper = 0x9,
	TextObject = 0xA,
	TextObjectAnnouncement = 0xB,
};

class TextPacket : public Packet {
public:
	TextPacketType Type;       // this+0x30
	std::string Author;     // this+0x38
	std::string Message;    // this+0x58
	std::vector<std::string> params;      // this+0x78
	bool Localize;   // this+0x90
	std::string Xuid;       // this+0x98
	std::string PlatformId; // this+0xB8
public:
	TextPacket();
};


class InteractPacket : public Packet {
public:
	InteractPacket();

public:
	int action;
	long target;
};

class CommandRequestPacket : public Packet {
public:
	CommandRequestPacket();
	CommandRequestPacket(std::string cmd);

	enum class Origin {
		PLAYER = 0,
		COMMAND_BLOCK = 1,
		MINECART_COMMAND_BLOCK = 2,
		DEV_CONSOLE = 3,
		AUTOMATION_PLAYER = 4,
		CLIENT_AUTOMATION = 5,
		DEDICATED_SERVER = 6,
		ENTITY = 7,
		VIRTUAL = 8,
		GAME_ARGUMENT = 9,
		INTERNAL = 10
	};

	std::string command;
	Origin origin = Origin::PLAYER;
	bool isExternal = 0;
	char shit[0x256];
};

class MobEquipmentPacket : public Packet {
public:
	MobEquipmentPacket(__int64 entityRuntimeId, ItemStack* item, int hotbarSlot, int inventorySlot);
	MobEquipmentPacket();
private:
	char pad_0x8[0x28];  // 0x0
public:
	__int64 entityRuntimeId;  // 0x30
	__int64 itemStack;        // 0x38;
private:
	char pad_0x40[0x78];  // 0x40
public:
	int slot1;  // 0xB8
	int slot2;  // 0xBC
	char windowId;
	char inventorySlot;
	char selectedSlot;
	char windowIdByte;
};

class PlayerHotbarPacket : public Packet {
public:
	PlayerHotbarPacket();
	PlayerHotbarPacket(int selectedHotbarSlot, char containerId, bool selectHotbarSlot);

	int selectedHotbarSlot;
	char containerId;
	bool selectHotbarSlot;
};

class Player;

__declspec(align(8)) class MovePlayerPacket : public Packet {
public:
	MovePlayerPacket();
	MovePlayerPacket(Player* player, vec3 pos);

	__int64 entityRuntimeID;  //0x28
	vec3 Position;          //0x30
	float pitch;              //0x3c
	float yaw;                //0x40
	float headYaw;            //0x44
	uint8_t mode;             //0x48
	bool onGround;
	__int64 ridingEid;
	int int1;
	int int2;
};

class NetworkLatencyPacket : public Packet {
public:
	NetworkLatencyPacket();

	unsigned long timeStamp;
	bool sendBack;
	int pad[0x100];           // 0x0
};

class PlayerActionPacket : public Packet {
public:
	PlayerActionPacket();

	vec3i blockPosition;    // 0x28
	int face;                 // 0x34
	int action;               // 0x38
	__int64 entityRuntimeId;  // 0x40
};

class ComplexInventoryTransaction {
public:
	uintptr_t** vTable;              //0x0000
	int actionType;                  //0x8
	int unknown;                     //0xC
};
class InventoryTransactionPacket : public Packet {
public:
	InventoryTransactionPacket();
	
	BUILD_ACCESS(ComplexInventoryTransaction*, complexTransaction, 0x58);
};
