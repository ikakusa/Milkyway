#pragma once
#include <system_error>
#include <bitset>
#include <vector>
#include <string>
#include <Math/Math.h>
#include <MemUtils.h>

class PacketHandlerDispatcherInstance {
public:
	uintptr_t** vTable;
};

class ItemStack;
class Packet {
public:
	BUILD_ACCESS(PacketHandlerDispatcherInstance*, handler, 0x18);
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

enum SetTitleType {

	Clear,
	Reset_0,
	Title,
	Subtitle,
	Actionbar,
	Times,
	TitleTextObject,
	SubtitleTextObject,
	ActionbarTextObject,

};


class SetTitlePacket : public Packet {

public:
	SetTitleType type;         // 0x30
	std::string text;              // 0x50
	float fadeInTime;   // 0x70
	float stayTime;  // 0x88
	float fadeOutTime;

	std::string xuid;
	std::string platformId;

	SetTitlePacket();
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

enum class MinecraftPacketIds : int {
	KeepAlive = 0x0,
	Login = 0x1,
	PlayStatus = 0x2,
	ServerToClientHandshake = 0x3,
	ClientToServerHandshake = 0x4,
	Disconnect = 0x5,
	ResourcePacksInfo = 0x6,
	ResourcePackStack = 0x7,
	ResourcePackClientResponse = 0x8,
	Text = 0x9,
	SetTime = 0xA,
	StartGame = 0xB,
	AddPlayer = 0xC,
	AddActor = 0xD,
	RemoveActor = 0xE,
	AddItemActor = 0xF,
	UNUSED = 0x10,
	TakeItemActor = 0x11,
	MoveAbsoluteActor = 0x12,
	MovePlayer = 0x13,
	PassengerJump = 0x14,
	UpdateBlock = 0x15,
	AddPainting = 0x16,
	TickSync = 0x17,
	LevelSoundEventV1 = 0x18,
	LevelEvent = 0x19,
	TileEvent = 0x1A,
	ActorEvent = 0x1B,
	MobEffect = 0x1C,
	UpdateAttributes = 0x1D,
	InventoryTransaction = 0x1E,
	PlayerEquipment = 0x1F,
	MobArmorEquipment = 0x20,
	Interact = 0x21,
	BlockPickRequest = 0x22,
	ActorPickRequest = 0x23,
	PlayerAction = 0x24,
	ActorFall_deprecated = 0x25,
	HurtArmor = 0x26,
	SetActorData = 0x27,
	SetActorMotion = 0x28,
	SetActorLink = 0x29,
	SetHealth = 0x2A,
	SetSpawnPosition = 0x2B,
	Animate = 0x2C,
	Respawn = 0x2D,
	ContainerOpen = 0x2E,
	ContainerClose = 0x2F,
	PlayerHotbar = 0x30,
	InventoryContent = 0x31,
	InventorySlot = 0x32,
	ContainerSetData = 0x33,
	CraftingData = 0x34,
	CraftingEvent = 0x35,
	GuiDataPickItem = 0x36,
	AdventureSettings_Deprecated = 0x37,
	BlockActorData = 0x38,
	PlayerInput = 0x39,
	FullChunkData = 0x3A,
	SetCommandsEnabled = 0x3B,
	SetDifficulty = 0x3C,
	ChangeDimension = 0x3D,
	SetPlayerGameType = 0x3E,
	PlayerList = 0x3F,
	SimpleEvent = 0x40,
	Event = 0x41,
	SpawnExperienceOrb = 0x42,
	MapData = 0x43,
	MapInfoRequest = 0x44,
	RequestChunkRadius = 0x45,
	ChunkRadiusUpdated = 0x46,
	ItemFrameDropItem = 0x47,
	GameRulesChanged = 0x48,
	Camera = 0x49,
	BossEvent = 0x4A,
	ShowCredits = 0x4B,
	AvailableCommands = 0x4C,
	CommandRequest = 0x4D,
	CommandBlockUpdate = 0x4E,
	CommandOutput = 0x4F,
	UpdateTrade = 0x50,
	UpdateEquip = 0x51,
	ResourcePackDataInfo = 0x52,
	ResourcePackChunkData = 0x53,
	ResourcePackChunkRequest = 0x54,
	Transfer = 0x55,
	PlaySound = 0x56,
	StopSound = 0x57,
	SetTitle = 0x58,
	AddBehaviorTree = 0x59,
	StructureBlockUpdate = 0x5A,
	ShowStoreOffer = 0x5B,
	PurchaseReceipt = 0x5C,
	PlayerSkin = 0x5D,
	SubclientLogin = 0x5E,
	AutomationClientConnect = 0x5F,
	SetLastHurtBy = 0x60,
	BookEdit = 0x61,
	NPCRequest = 0x62,
	PhotoTransfer = 0x63,
	ShowModalForm = 0x64, // ModalFormRequest
	ModalFormResponse = 0x65,
	ServerSettingsRequest = 0x66,
	ServerSettingsResponse = 0x67,
	ShowProfile = 0x68,
	SetDefaultGameType = 0x69,
	RemoveObjective = 0x6A,
	SetDisplayObjective = 0x6B,
	SetScore = 0x6C,
	LabTable = 0x6D,
	UpdateBlockSynced = 0x6E,
	MoveDeltaActor = 0x6F,
	SetScoreboardIdentity = 0x70,
	SetLocalPlayerAsInit = 0x71,
	UpdateSoftEnum = 0x72,
	Ping = 0x73,
	BlockPalette = 0x74,
	ScriptCustomEvent = 0x75,
	SpawnParticleEffect = 0x76,
	AvailableActorIDList = 0x77,
	LevelSoundEventV2 = 0x78,
	NetworkChunkPublisherUpdate = 0x79,
	BiomeDefinitionList = 0x7A,
	LevelSoundEvent = 0x7B,
	LevelEventGeneric = 0x7C,
	LecternUpdate = 0x7D,
	VideoStreamConnect_DEPRECATED = 0x7E,
	AddEntity = 0x7F,
	RemoveEntity = 0x80,
	ClientCacheStatus = 0x81,
	OnScreenTextureAnimation = 0x82,
	MapCreateLockedCopy = 0x83,
	StructureTemplateDataExportRequest = 0x84,
	StructureTemplateDataExportResponse = 0x85,
	UNUSED_PLS_USE_ME2 = 0x86,
	ClientCacheBlobStatusPacket = 0x87,
	ClientCacheMissResponsePacket = 0x88,
	EducationSettingsPacket = 0x89,
	Emote = 0x8A,
	MultiplayerSettingsPacket = 0x8B,
	SettingsCommandPacket = 0x8C,
	AnvilDamage = 0x8D,
	CompletedUsingItem = 0x8E,
	NetworkSettings = 0x8F,
	PlayerAuthInputPacket = 0x90,
	CreativeContent = 0x91,
	PlayerEnchantOptions = 0x92,
	ItemStackRequest = 0x93,
	ItemStackResponse = 0x94,
	PlayerArmorDamage = 0x95,
	CodeBuilderPacket = 0x96,
	UpdatePlayerGameType = 0x97,
	EmoteList = 0x98,
	PositionTrackingDBServerBroadcast = 0x99,
	PositionTrackingDBClientRequest = 0x9A,
	DebugInfoPacket = 0x9B,
	PacketViolationWarning = 0x9C,
	MotionPredictionHints = 0x9D,
	TriggerAnimation = 0x9E,
	CameraShake = 0x9F,
	PlayerFogSetting = 0xA0,
	CorrectPlayerMovePredictionPacket = 0xA1,
	ItemComponentPacket = 0xA2,
	FilterTextPacket = 0xA3,
	ClientBoundDebugRendererPacket = 0xA4,
	SyncActorProperty = 0xA5,
	AddVolumeEntityPacket = 0xA6,
	RemoveVolumeEntityPacket = 0xA7,
	SimulationTypePacket = 0xA8,
	NpcDialoguePacket = 0xA9,
	EduUriResourcePacket = 0xAA,
	CreatePhotoPacket = 0xAB,
	UpdateSubChunkBlocks = 0xAC,
	PhotoInfoRequest_DEPRECATED = 0xAD,
	SubChunkPacket = 0xAE,
	SubChunkRequestPacket = 0xAF,
	PlayerStartItemCooldown = 0xB0,
	ScriptMessagePacket = 0xB1,
	CodeBuilderSourcePacket = 0xB2,
	TickingAreasLoadStatus = 0xB3,
	DimensionDataPacket = 0xB4,
	AgentAction = 0xB5,
	ChangeMobProperty = 0xB6,
	LessonProgressPacket = 0xB7,
	RequestAbilityPacket = 0xB8,
	RequestPermissionsPacket = 0xB9,
	ToastRequest = 0xBA,
	UpdateAbilitiesPacket = 0xBB,
	UpdateAdventureSettingsPacket = 0xBC,
	DeathInfo = 0xBD,
	EditorNetworkPacket = 0xBE,
	FeatureRegistryPacket = 0xBF,
	ServerStats = 0xC0,
	RequestNetworkSettings = 0xC1,
	GameTestRequestPacket = 0xC2,
	GameTestResultsPacket = 0xC3,
	PlayerClientInputPermissions = 0xC4,
	ClientCheatAbilityPacket = 0xC5,
	CameraPresets = 0xC6,
	UnlockedRecipes = 0xC7,
	CameraInstruction = 0x12C,
	CompressedBiomeDefinitionList = 0x12D,
	TrimData = 0x12E,
	OpenSign = 0x12F,
	AgentAnimation = 0x130,
	RefreshEntitlements = 0x131,
	EndId,
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

class PlaySoundPacket : public Packet {
public:
	PlaySoundPacket();
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
