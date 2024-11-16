#pragma once
#include <Colors/Color.h>
#include <optional>

class BlockLegacy;
class BlockRenderLayer;
class Block;
class BlockPos;
class ItemStack;
class IConstBlockSource;
class BlockSource;
class Material;
class Container;
class ActorBlockSyncMessage;
class ItemStack;

class BlockLegacy {
public:
    char pad_0008[32]; //0x0008
    std::string tileName;

    BUILD_ACCESS(uintptr_t**, vTable, 0x0);
    BUILD_ACCESS(std::string, name, 0x28);
    BUILD_ACCESS(std::string, itemNamespace, 0xA0);
    BUILD_ACCESS(uint16_t, id, 0x1A6);
    BUILD_ACCESS(BlockRenderLayer*, renderLayer, 0x0B4);
    BUILD_ACCESS(Material*, material, 0x128);
    BUILD_ACCESS(bool, isSolid, 0x164);

    // new vTable
    virtual ~BlockLegacy();
    virtual void newBlockEntity(BlockPos const&, Block const&);
    virtual void getNextBlockPermutation(Block const&);
    virtual void clip(BlockSource const&, BlockPos const&, vec3 const&, vec3 const&, bool);
    virtual void getCollisionShape(/*AABB&, Block const&, IConstBlockSource const&, BlockPos const&, optional_ref<GetCollisionShapeInterface const>*/);
    virtual void addCollisionShapes(/*Block const&, BlockSource const&, BlockPos const&, AABB const*, std::vector<AABB>&, optional_ref<GetCollisionShapeInterface const>*/);
    virtual void getAABB(class IConstBlockSource const&, BlockPos const&, Block const&, AABB&, bool);
    virtual void addAABBs(Block const&, BlockSource const&, BlockPos const&, AABB const*, std::vector<AABB>&);
    virtual void getOutline(BlockSource&, BlockPos const&, AABB&);
    virtual void getVisualShapeInWorld(Block const&, class IConstBlockSource const&, BlockPos const&, AABB&);
    virtual void getVisualShape(Block const&, AABB&);
    virtual void getUIShape(Block const&, AABB&);
    virtual void getLiquidClipVolume(BlockSource&, BlockPos const&, AABB&);
    virtual bool isObstructingChests(BlockSource&, BlockPos const&, Block const&);
    virtual void randomlyModifyPosition(BlockPos const&, int&);
    virtual void randomlyModifyPosition(BlockPos const&);
    virtual void onProjectileHit(BlockSource&, BlockPos const&, Actor const&);
    virtual void onLightningHit(BlockSource&, BlockPos const&);
    virtual bool hasVariableLighting(void);
    virtual bool isStrippable(Block const&);
    virtual void getStrippedBlock(Block const&);
    virtual bool canProvideSupport(Block const&, unsigned char, class BlockSupportType);
    virtual bool canProvideMultifaceSupport(Block const&, unsigned char);
    virtual bool canConnect(Block const&, unsigned char, Block const&);
    virtual bool isMovingBlock(void);
    virtual void tryGetCopperBehavior(void);
    virtual bool canDamperVibrations(void);
    virtual bool canOccludeVibrations(void);
    virtual bool isStemBlock(void);
    virtual bool isContainerBlock(void);
    virtual bool isCraftingBlock(void);
    virtual bool isWaterBlocking(void);
    virtual bool isFenceBlock(void);
    virtual bool isFenceGateBlock(void);
    virtual bool isThinFenceBlock(void);
    virtual bool isWallBlock(void);
    virtual bool isStairBlock(void);
    virtual bool isSlabBlock(void);
    virtual bool isDoubleSlabBlock(void);
    virtual bool isDoorBlock(void);
    virtual bool isRailBlock(void);
    virtual bool isButtonBlock(void);
    virtual bool isLeverBlock(void);
    virtual bool isCandleCakeBlock(void);
    virtual bool isMultifaceBlock(void);
    virtual bool isSignalSource(void);
    virtual bool canBeOriginalSurface(void);
    virtual bool isSilentWhenJumpingOff(void);
    virtual bool isValidAuxValue(int);
    virtual bool canFillAtPos(BlockSource&, BlockPos const&, Block const&);
    virtual void sanitizeFillBlock(BlockSource&, BlockPos const&, Block const&);
    virtual void onFillBlock(BlockSource&, BlockPos const&, Block const&);
    virtual void getDirectSignal(BlockSource&, BlockPos const&, int);
    virtual bool canBeDestroyedByWaterSpread(void);
    virtual void waterSpreadCausesSpawn(void);
    virtual bool canContainLiquid(void);
    virtual void getRequiredMedium(void);
    virtual void shouldConnectToRedstone(BlockSource&, BlockPos const&, int);
    virtual void handlePrecipitation(BlockSource&, BlockPos const&, float, float);
    virtual bool canBeUsedInCommands(class BaseGameVersion const&);
    virtual void checkIsPathable(Actor&, BlockPos const&, BlockPos const&);
    virtual void shouldDispense(BlockSource&, Container&);
    virtual void dispense(BlockSource&, Container&, int, vec3 const&, unsigned char);
    virtual void transformOnFall(BlockSource&, BlockPos const&, Actor*, float);
    virtual void onRedstoneUpdate(BlockSource&, BlockPos const&, int, bool);
    virtual void onMove(BlockSource&, BlockPos const&, BlockPos const&);
    virtual void detachesOnPistonMove(BlockSource&, BlockPos const&);
    virtual void movedByPiston(BlockSource&, BlockPos const&);
    virtual void onStructureBlockPlace(BlockSource&, BlockPos const&);
    virtual void onStructureNeighborBlockPlace(BlockSource&, BlockPos const&);
    virtual void setupRedstoneComponent(BlockSource&, BlockPos const&);
    virtual void getRedstoneProperty(BlockSource&, BlockPos const&);
    virtual void updateEntityAfterFallOn(BlockPos const&, class UpdateEntityAfterFallOnInterface&);
    virtual bool isBounceBlock(void);
    virtual bool isPreservingMediumWhenPlaced(BlockLegacy const*);
    virtual bool isFilteredOut(BlockRenderLayer);
    virtual bool canRenderSelectionOverlay(BlockRenderLayer);
    virtual void ignoreEntitiesOnPistonMove(Block const&);
    virtual void onFertilized(BlockSource&, BlockPos const&, Actor*, class FertilizerType);
    virtual void mayConsumeFertilizer(BlockSource&);
    virtual bool canBeFertilized(BlockSource&, BlockPos const&, Block const&);
    virtual void mayPick(void);
    virtual void mayPick(BlockSource const&, Block const&, bool);
    virtual void mayPlace(BlockSource&, BlockPos const&, unsigned char);
    virtual bool mayPlace(BlockSource&, BlockPos const&);
    virtual bool mayPlaceOn(BlockSource&, BlockPos const&);
    virtual void tryToPlace(BlockSource&, BlockPos const&, Block const&, ActorBlockSyncMessage const*);
    virtual void tryToTill(BlockSource&, BlockPos const&, Actor&, ItemStack&);
    virtual void breaksFallingBlocks(Block const&, BaseGameVersion);
    virtual void destroy(BlockSource&, BlockPos const&, Block const&, Actor*);
    virtual void getIgnoresDestroyPermissions(Actor&, BlockPos const&);
    virtual void neighborChanged(BlockSource&, BlockPos const&, BlockPos const&);
    virtual void getSecondPart(BlockSource const&, BlockPos const&, BlockPos&);
    virtual void playerWillDestroy(Actor&, BlockPos const&, Block const&);
    virtual void asItemInstance(Block const&, class BlockActor const*);
    virtual void trySpawnResourcesOnExplosion(BlockSource&, BlockPos const&, Block const&, class Randomize&, float);
    virtual void getPlacementBlock(Actor const&, BlockPos const&, unsigned char, vec3 const&, int);
    virtual void calcVariant(BlockSource&, BlockPos const&, rgb const&);
    virtual bool isAttachedTo(BlockSource&, BlockPos const&, BlockPos&);
    virtual void attack(Actor*, BlockPos const&);
    virtual void shouldTriggerEntityInside(BlockSource&, BlockPos const&, Actor&);
    virtual bool canBeBuiltOver(BlockSource&, BlockPos const&, class BlockItem const&);
    virtual bool canBeBuiltOver(BlockSource&, BlockPos const&);
    virtual void triggerEvent(BlockSource&, BlockPos const&, int, int);
    virtual void executeEvent(BlockSource&, BlockPos const&, Block const&, std::string const&, Actor&);
    virtual bool hasTag(BlockSource&, BlockPos const&, Block const&, std::string const&);
    virtual void getMobToSpawn(class SpawnConditions const&, BlockSource&);
    virtual void shouldStopFalling(Actor&);
    virtual void pushesUpFallingBlocks(void);
    virtual bool canHaveExtraData(void);
    virtual bool hasComparatorSignal(void);
    virtual void getComparatorSignal(BlockSource&, BlockPos const&, Block const&, unsigned char);
    virtual bool canSlide(BlockSource&, BlockPos const&);
    virtual bool canInstatick(void);
    virtual bool canSpawnAt(BlockSource const&, BlockPos const&);
    virtual void notifySpawnedAt(BlockSource&, BlockPos const&);
    virtual void causesFreezeEffect(void);
    virtual void getIconYOffset(void);
    virtual void buildDescriptionId(Block const&);
    virtual bool isAuxValueRelevantForPicking(void);
    virtual void getColor(Block const&);
    virtual void getColorAtPos(BlockSource&, BlockPos const&);
    virtual void getColor(BlockSource&, BlockPos const&, Block const&);
    virtual void getColorForParticle(BlockSource&, BlockPos const&, Block const&);
    virtual bool isSeasonTinted(Block const&, BlockSource&, BlockPos const&);
    virtual void onGraphicsModeChanged(class BlockGraphicsModeChangeContext const&);
    virtual void getShadeBrightness(Block const&);
    virtual void telemetryVariant(BlockSource&, BlockPos const&);
    virtual void getVariant(Block const&);
    virtual bool canSpawnOn(Actor*);
    virtual void getRenderBlock(void);
    virtual void getMappedFace(unsigned char, Block const&);
    virtual void getFaceFlip(unsigned char, Block const&);
    virtual void animateTickBedrockLegacy(BlockSource&, BlockPos const&, class Random&);
    virtual void animateTick(BlockSource&, BlockPos const&, class Random&);
    virtual void init(void);
    virtual void tryLegacyUpgrade(unsigned short);
    virtual void dealsContactDamage(Actor const&, Block const&, bool);
    virtual void tryGetInfested(Block const&);
    virtual void tryGetUninfested(Block const&);
    virtual void _addHardCodedBlockComponents(void);
    virtual void onRemove(BlockSource&, BlockPos const&);
    virtual void onExploded(BlockSource&, BlockPos const&, Actor*);
    virtual void onStandOn(class EntityContext&, BlockPos const&);
    virtual void onPlace(BlockSource&, BlockPos const&);
    virtual void shouldTickOnSetBlock(void);
    virtual void tick(BlockSource&, BlockPos const&, class Random&);
    virtual void randomTick(BlockSource&, BlockPos const&, class Random&);
    virtual bool isInteractiveBlock(void);
    virtual void use(Actor&, BlockPos const&, unsigned char, std::optional<vec3>);
    virtual void use(Actor&, BlockPos const&, unsigned char);
    virtual void allowStateMismatchOnPlacement(Block const&, Block const&);
    virtual bool canSurvive(BlockSource&, BlockPos const&);
    virtual void getRenderLayer(void);
    virtual void getRenderLayer(Block const&, BlockSource&, BlockPos const&);
    virtual void getExtraRenderLayers(void);
    virtual void getLight(Block const&);
    virtual void getLightEmission(Block const&);
    virtual void getEmissiveBrightness(Block const&);
    virtual void getMapColor(BlockSource&, BlockPos const&, Block const&);
    virtual void _onHitByActivatingAttack(BlockSource&, BlockPos const&, Actor*);
    virtual void entityInside(BlockSource&, BlockPos const&, Actor&);
    int getVariant(Block* blk) {
        using getVariant = int(*)(BlockLegacy*, Block*);
        static getVariant getVariantFunc = reinterpret_cast<getVariant>(SigScan("48 83 ec ? 48 8b 4a ? 48 8b 05 ? ? ? ? 48 89 44 24 ? 48 85 c9 74 ? 44 0f b7 42 ? 48 8d 54 24 ? e8 ? ? ? ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc cc cc 48 89 5c 24 ? 48 89 6c 24 ? 56"));//dead
        return getVariantFunc(this, blk);
    }
    inline bool equalToBlockName(std::string block) {
        auto text = this->name.c_str();
        if (strcmp(text, block.c_str()) == NULL)
            return true;
        else
            return false;
    }

    inline bool containsString(std::string string) {
        auto text = this->name.c_str();
        return (strstr(text, string.c_str()) != NULL);
    }

    inline bool IsAir() {
        return id == 0;
    }

    inline bool isSolidBlock() {
        return this->isSolid;
    }

    inline bool isOre() {
        return containsString("ore");
    }

    inline bool isFullBlock() {
        return !this->isStemBlock() && !this->isFenceBlock() && !this->isFenceGateBlock() &&
            !this->isThinFenceBlock() && !this->isRailBlock() && !this->isButtonBlock() && !this->isLeverBlock() && !this->isCandleCakeBlock() &&
            !this->isWallBlock() && !this->isStairBlock() && !this->isSlabBlock() && !this->isDoorBlock();
    }
};

class Block {
public:
	BUILD_ACCESS(BlockLegacy*, blockLegacy, 0x30);
};

class BlockSourceListener {
};
class Bounds {

};
class ActorBlockSyncMessage {

};

class BlockSource
{
public:
	Block* getBlock(vec3 pos)
	{
		__int64 v4 = *(__int64*)this;
		int v6[6]; // [rsp+20h] [rbp-18h] BYREF

		v6[0] = (int)pos.x;
		v6[1] = (int)pos.y;
		v6[2] = (int)pos.z;
		return (Block*)(*(__int64(__fastcall**)(BlockSource*, int*))(v4 + 0x10))(this, v6);
	}
    float getSeenPercent(const vec3& pos, const AABB& target) {
        using getSeenPercent_t = float(__fastcall*)(BlockSource*, const vec3&, const AABB&);
        static getSeenPercent_t seenPercent = reinterpret_cast<getSeenPercent_t>(SigScan("40 55 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24"));  // 0x22FE020
        return seenPercent(this, pos, target);
    }
};

class Material {
public:
	BUILD_ACCESS(int, type, 0x0);
	BUILD_ACCESS(bool, isFlammable, 0x4);
	BUILD_ACCESS(bool, isNeverBuildable, 0x5);
	BUILD_ACCESS(bool, isLiquid, 0x6);
	BUILD_ACCESS(bool, isBlockingMotion, 0xC);
	BUILD_ACCESS(bool, isSuperHot, 0xF);
};