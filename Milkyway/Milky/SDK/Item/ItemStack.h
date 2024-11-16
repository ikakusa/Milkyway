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
public:
    uint16_t getDamageValue(CompoundTag* compoundTag) {
        using getDamageVal = uint16_t(*)(ItemStackBase*);
        static getDamageVal func = reinterpret_cast<getDamageVal>(SigScan("40 53 48 83 EC ?? 48 8B 51 ?? 33 DB 48 85"));
        return func(this);
    }
    uint64_t getMaxDamage() {
        if (*(uintptr_t*)this + 0x118LL) {
            return (*(uint64_t(__fastcall**)(ItemStackBase*))(*(uintptr_t*)this + 0x118LL))(this);
        }
        return 0;
    }
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
    ItemStack* getItem(int slot) {
        return CallVFunc<7, ItemStack*, int>(this, slot);
    }
};

class PlayerInventoryProxy {
public:
    BUILD_ACCESS(uintptr_t**, vTable, 0x0)
    BUILD_ACCESS(int, selectedHotbarSlot, 0x0010);

    Inventory* getInventory() {
        return reinterpret_cast<Inventory*>(this + 0x0C0);
    };

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
            ItemStack* item = getInventory()->getItem(i);
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
            ItemStack* item = getInventory()->getItem(i);
            items.push_back(item);
        }
        return items;
    }


    ItemStack* getSelectedItem()
    {
        return getInventory()->getItem(selectedHotbarSlot);
    }

    ItemStack* GetItemAtSlot(int slot)
    {
        if (getInventory() != nullptr)
            return getInventory()->getItem(slot);
        return nullptr;
    }
};