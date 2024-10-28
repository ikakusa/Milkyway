#pragma once
#include <windows.h>
#include <string>
#include <Math/Math.h>

class ItemStack;
class Actor;
class ContainerRemovedListener;
class CompoundTag;
class Container {
public:
    // new vTable
    virtual ~Container();
    virtual void init(void);
    virtual void addContentChangeListener(class ContainerContentChangeListener*);
    virtual void removeContentChangeListener(ContainerContentChangeListener*);
    virtual void addRemovedListener(class ContainerRemovedListener*);
    virtual void removeRemovedListener(ContainerRemovedListener*);
    virtual void Function5();
    virtual class ItemStack* getItem(int);
    virtual bool hasRoomForItem(ItemStack const&);
    virtual void addItem(ItemStack&);
    virtual void addItemWithForceBalance(ItemStack&);
    virtual void addItemToFirstEmptySlot(ItemStack const&);
    virtual int Function8();
    virtual void setItemWithForceBalance(int, ItemStack const&, bool);
    virtual void removeItem(int, int);
    virtual void removeAllItems(void);
    virtual void removeAllItemsWithForceBalance(void);
    virtual void containerRemoved(void);
    virtual void dropSlotContent(class BlockSource&, vec3 const&, bool, int);
    virtual void dropContents(BlockSource&, vec3 const&, bool);
    virtual void getContainerSize(void);
    virtual void getMaxStackSize(void);
    virtual void startOpen(class Actor&);
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
    virtual void readAdditionalSaveData(class CompoundTag const&);
    virtual void addAdditionalSaveData(CompoundTag&);
    virtual void initializeContainerContents(class BlockSource&);
    virtual bool isEmpty(void);
    virtual bool isSlotDisabled(int);

};

class SimpleContainer : public Container {};