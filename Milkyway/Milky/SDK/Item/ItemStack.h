#pragma once
#include "../SDK.h"
#include <string>
class Block;
class ItemInstance;
class ItemStack;
class RenderPrarams;
class CompoundTag;
class BlockSource;
class Container;
class BlockPos;

class ItemStackBase {
public:
    BUILD_ACCESS(uintptr_t**, vtable, 0x0);
    BUILD_ACCESS(short, id, 0xA2);
    BUILD_ACCESS(class CompoundTag*, userData, 0x10);
    BUILD_ACCESS(int, armorItemType, 0x244);
    BUILD_ACCESS(int, protectionAmount, 0x25C);
public:
    uintptr_t** vtable2;
    class Item** item;
    void* compoundTag;
    class Block* blockPtr;
    short auxValue;
    int8_t amount;
private:
    char pad_0x1B[0x60];
};
class ItemStack : public ItemStackBase {
public:
    bool hasCustomHoverName() {
    //48 89 5C 24 ?? 57 48 83 EC ?? 48 8B D9 48 8B 49 ?? 48 85 C9 0F 84 F0
        static uintptr_t func = SigScan("48 89 5C 24 ?? 57 48 83 EC ?? 48 8B D9 48 8B 49 ?? 48 85 C9 0F 84 F0");
        static auto _ItemStackBase_getName = (bool(__fastcall*)(ItemStack*))func;
        return _ItemStackBase_getName(this);
    }
    std::string getCustomName() {
        std::string name = "";
        static uintptr_t func = SigScan("48 89 5C 24 ?? 55 56 57 48 83 EC ?? 48 8B FA 48 8B D9 48 89 54");
        static auto _ItemStackBase_getName = (std::string * (__fastcall*)(ItemStack*, std::string*))func;
        _ItemStackBase_getName(this, &name);
        return name;
    }
};

class Item {
public:
    //std::string getNameId()
    //{
    //	return *(std::string*)((uintptr_t)(this + 0x1) + 0x290);
    //}

    //uint16_t maxStackSize;
    //std::string name;

 //     void setIsGlint(Item* _this, bool a2) {
    //	  *((BYTE*)_this + 0x14A) = (BYTE)(a2) | (*((BYTE*)_this + 0x14A) & 0xFE);

    //}
    //bool isBlock(void) {
    //	using isBlock = bool(*)(Item*);
    //	static isBlock check = reinterpret_cast<isBlock>(MCM::FindSignature(xorstr_("48 83 EC 28 48 8B 49 08 48 85 C9 74 ?? 48 83 39")));
    //	return check(this);
    //}
    //__int64 getAttackDamage() {
    //	return *((unsigned int*)this + 0x120);
    //}
    ////__int64 getArmorValue() {
    ////	return *((unsigned int*)this + 0x120);
    ////}
    //__int64 getId()
    //{
    //	return *((unsigned __int16*)this + 0x23);
    //}

    virtual ~Item();
    virtual void initServer(/*Json::Value&, SemVersion const&, bool, Experiments const&*/);
    virtual void tearDown(void);
    virtual void setDescriptionId(std::string const&);
    virtual void getDescriptionId(void);
    virtual void getMaxUseDuration(ItemStack const*);
    virtual bool isMusicDisk(void);
    virtual void executeEvent(class ItemStackBase&, std::string const&, class RenderParams&);
    virtual bool isComponentBased(void);
    virtual bool isHumanoidArmor(void);
    virtual bool isBlockPlanterItem(void);
    virtual bool isBucket(void);
    virtual bool isCandle(void);
    virtual bool isDamageable(void);
    virtual bool isDyeable(void);
    virtual bool isDye(void);
    virtual void getItemColor(void);
    virtual bool isFertilizer(void);
    virtual bool isFood(void);
    virtual bool isThrowable(void);
    virtual bool isUseable(void);
    virtual bool isTrimAllowed(void);
    virtual void getComponent(class HashedString const&);
    virtual void getFood(void);
    virtual void setMaxDamage(int);
    virtual void setMaxUseDuration(int);
    virtual void buildNetworkTag(void);
    virtual void initializeFromNetwork(CompoundTag const&);
    virtual void validateFromNetwork(CompoundTag const&);
    virtual void getBlockShape(void);
    virtual bool canBeDepleted(void);
    virtual bool canDestroySpecial(Block const&);
    virtual void getLevelDataForAuxValue(int);
    virtual bool isStackedByData(void);
    virtual uint64_t getMaxDamage(void);
    virtual void getAttackDamage(void);
    virtual void getAttackDamageBonus(class Actor const&, float);
    virtual bool isHandEquipped(void);
    virtual bool isGlint(ItemStackBase const&);
    virtual bool isPattern(void);
    virtual void getPatternIndex(void);
    virtual void showsDurabilityInCreative(void);
    virtual bool isWearableThroughLootTable(CompoundTag const*);
    virtual bool canDestroyInCreative(void);
    virtual bool isDestructive(int);
    virtual bool isLiquidClipItem(int);
    virtual void shouldInteractionWithBlockBypassLiquid(Block const&);
    virtual void requiresInteract(void);
    virtual void appendFormattedHovertext(ItemStackBase const&, class Level&, std::string&, bool);
    virtual bool isValidRepairItem(ItemStackBase const&, ItemStackBase const&, class BaseGameVersion const&);
    virtual void getEnchantSlot(void);
    virtual int getEnchantValue(void);
    virtual int getArmorValue(void);
    virtual float getToughnessValue(void);
    virtual void getBreakSound(void);
    virtual bool isComplex(void);
    virtual bool isValidAuxValue(int);
    virtual void getDamageChance(int);
    virtual void getViewDamping(void);
    virtual void uniqueAuxValues(void);
    virtual bool isActorPlacerItem(void);
    virtual bool isMultiColorTinted(ItemStack const&);
    virtual void getColor(CompoundTag const*, class ItemDescriptor const&);
    virtual bool hasCustomColor(ItemStackBase const&);
    virtual bool hasCustomColor(CompoundTag const*);
    virtual void setColor(ItemStackBase&, rgb const&); // (mce::color)
    virtual void getBaseColor(ItemStack const&);
    virtual void getSecondaryColor(ItemStack const&);
    virtual void getActorIdentifier(ItemStack const&);
    virtual void buildIdAux(short, CompoundTag const*);
    virtual bool canUseOnSimTick(void);
    virtual void use(ItemStack&, class Actor&);
    virtual void createProjectileActor(BlockSource&, ItemStack const&, vec3 const&, vec3 const&);
    virtual void dispense(BlockSource&, Container&, int, vec3 const&, unsigned char);
    virtual void useTimeDepleted(ItemStack&, Level*, Actor*);
    virtual void releaseUsing(ItemStack&, Actor*, int);
    virtual float getDestroySpeed(ItemStack*, Block const&);
    virtual void hurtActor(ItemStack&, Actor&, Actor&);
    virtual void hitActor(ItemStack&, Actor&, Actor&);
    virtual void hitBlock(ItemStack&, Block const&, BlockPos const&, Actor&);
    virtual void mineBlock(ItemStack&, Block const&, int, int, int, Actor*);
    virtual void buildDescriptionName(ItemStackBase const&);
    virtual void buildDescriptionId(ItemDescriptor const&, CompoundTag const*);
    virtual void buildEffectDescriptionName(ItemStackBase const&);
    virtual void readUserData(ItemStackBase&, __int64&, class ReadOnlyBinaryStream&);
    virtual void writeUserData(ItemStackBase const&, __int64&);
    virtual void getMaxStackSize(ItemDescriptor const&);
    virtual void inventoryTick(ItemStack&, Level&, Actor&, int, bool);
    virtual void refreshedInContainer(ItemStackBase const&, Level&);
    virtual void getCooldownType(void);
    virtual void getCooldownTime(void);
    virtual void fixupCommon(ItemStackBase&);
    virtual void fixupCommon(ItemStackBase&, Level&);
    virtual void getInHandUpdateType(Actor const&, class ItemInstance const&, ItemInstance const&, bool, bool);
    virtual void validFishInteraction(int);
    virtual void enchantProjectile(ItemStackBase const&, Actor&);
    virtual void getEquipLocation(void);
    virtual void getEquipSound(void);
    virtual void shouldSendInteractionGameEvents(void);
    virtual void useInterruptedByAttacking(void);
    virtual bool hasSameRelevantUserData(ItemStackBase const&, ItemStackBase const&);
    virtual void initClient(/*Json::Value&, SemVersion const&, bool, Experiments const&*/);
    virtual void setIconInfo(std::string const&, int);
    virtual void getIconInfo(ItemStackBase const&, int, bool);
    virtual void getInteractText(Actor const&);
    virtual void getAnimationFrameFor(Actor*, bool, ItemStack const*, bool);
    virtual bool isEmissive(int);
    virtual void getLightEmission(int);
    virtual void getIconYOffset(void);
    virtual bool canBeCharged(void);
    virtual void playSoundIncrementally(ItemStack const&, Actor&);
    virtual void getFurnaceXPmultiplier(class ItemStackBase const&);
    virtual void getAuxValuesDescription(void);
    virtual void calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&);
    virtual void _checkUseOnPermissions(Actor&, ItemStackBase&, unsigned char const&, BlockPos const&);
    virtual void _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&);
    virtual void _shouldAutoCalculatePlacePos(void);
    virtual void _useOn(ItemStack&, Actor&, BlockPos, unsigned char, vec3 const&);
public:
    BUILD_ACCESS(std::string, name, 0xD0);
    BUILD_ACCESS(uint16_t, id, 0xA2);
    BUILD_ACCESS(HashedString, rawname, 0xC8);
    BUILD_ACCESS(std::string, namespaceId, 0xF8);

    bool IsSword() {
        return name.find("_sword") != std::string::npos;
    }

    bool IsPickaxe() {
        return name.find("_pickaxe") != std::string::npos;
    }

    bool IsAxe() {
        return name.find("_axe") != std::string::npos;
    }

    bool IsShovel() {
        return name.find("_shovel") != std::string::npos;
    }

    bool IsPotion() {
        return name.find("potion") != std::string::npos;
    }

    uint16_t getDamageValue(CompoundTag* compoundTag) {
        using getDamageVal = uint16_t(*)(Item*, CompoundTag*);
        static getDamageVal func = reinterpret_cast<getDamageVal>(SigScan("48 89 5C 24 08 57 48 83 EC 30 48 8B DA 48 85"));
        return func(this, compoundTag);
    }
};

class ContainerContentChangeListener;
class ContainerRemovedListener;
class CompoundTag;
class SemVersion;
class ListTag;

class Inventory
{
public:
    BUILD_ACCESS(uintptr_t**, vTable, 0x0);
    virtual ~Inventory();
    virtual void init(void);
    virtual void addContentChangeListener(ContainerContentChangeListener*);
    virtual void removeContentChangeListener(ContainerContentChangeListener*);
    virtual void addRemovedListener(class ContainerRemovedListener*);
    virtual void removeRemovedListener(ContainerRemovedListener*);
    virtual void Function5();
    virtual ItemStack* getItem(int);
    virtual bool hasRoomForItem(ItemStack const&);
    virtual void addItem(ItemStack&);
    virtual void addItemWithForceBalance(ItemStack&);
    virtual void addItemToFirstEmptySlot(ItemStack const&);
    virtual void setItem(int, ItemStack const&);
    virtual void setItemWithForceBalance(int, ItemStack const&, bool);
    virtual void removeItem(int, int);
    virtual void removeAllItems(void);
    virtual void removeAllItemsWithForceBalance(void);
    virtual void containerRemoved(void);
    virtual void dropSlotContent(class BlockSource&, struct Vec3 const&, bool, int);
    virtual void dropContents(class BlockSource&, struct Vec3 const&, bool);
    virtual int getContainerSize(void);
    virtual void getMaxStackSize(void);
    virtual void startOpen(Actor&);
    virtual void stopOpen(Actor&);
    virtual void getSlotCopies(void);
    virtual void getSlots(void);
    virtual void getEmptySlotsCount(void);
    virtual void getItemCount(ItemStack const&);
    virtual void findFirstSlotForItem(ItemStack const&);
    virtual bool canPushInItem(int, int, ItemStack const&);
    virtual bool canPullOutItem(int, int, ItemStack const&);
    virtual void setContainerChanged(int);
    virtual void setContainerMoved(void);
    virtual void setCustomName(std::string const&);
    virtual bool hasCustomName(void);
    virtual void readAdditionalSaveData(CompoundTag const&);
    virtual void addAdditionalSaveData(CompoundTag&);
    virtual void initializeContainerContents(BlockSource&);
    virtual bool isEmpty(void);
    virtual bool isSlotDisabled(int);
    virtual void add(ItemStack&);
    virtual bool canAdd(ItemStack const&);
    virtual void clearSlot(int);
    virtual void clearInventory(int);
    virtual void load(class ListTag const&, class SemVersion const&, class Level&);
    virtual int getFirstEmptySlot(void);
    virtual void setContainerSize(int);

    void dropSlot(int slot);
    void swapSlots(int from, int to);
    void equipArmor(int slot);
    void startUsingItem(int slot);
    void releaseUsingItem(int slot);
};

class PlayerInventoryProxy {
public:
    BUILD_ACCESS(uintptr_t**, vTable, 0x0)
        BUILD_ACCESS(int, selectedHotbarSlot, 0x0010);
    BUILD_ACCESS(Inventory*, inventory, 0x0C0);

    ItemStack* getFirstItemSlot() {
        std::vector<ItemStack*> items = getInventoryItems();
        if (!items.empty()) return items[0];
        return nullptr;
    }

    std::vector<int> GetSwords(bool hotbarOnly = true)
    {
        std::vector<int> slots;
        for (int i = 0; i < 36; i++)
        {
            ItemStack* item = inventory->getItem(i);
            if (!item)
                continue;
            if (!item->item)
                continue;
            Item* itemPtr = *item->item;
            if (!item->item)
                continue;
            if (hotbarOnly && i > 8)
                continue;
            if (itemPtr->name.find("_sword") != std::string::npos)
            {
                slots.push_back(i);
            }
        }

        return slots;
    }

    std::vector<ItemStack*> getInventoryItems()
    {
        std::vector<ItemStack*> items;
        for (int i = 0; i < 36; i++)
        {
            ItemStack* item = inventory->getItem(i);
            items.push_back(item);
        }
        return items;
    }


    ItemStack* getSelectedItem()
    {
        return inventory->getItem(selectedHotbarSlot);
    }

    ItemStack* GetItemAtSlot(int slot)
    {
        if (inventory != nullptr)
            return inventory->getItem(slot);
        return nullptr;
    }
};