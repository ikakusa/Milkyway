#pragma once

#include <MemUtils.h>
#include "StateVectorComponent.h"
#include "ActorRotationComponent.h"
#include "../MobEffect/MobEffect.h"
#include "RuntimeIDComponent.h"
#include "../Item/Container.h"
#include <entt/entt.hpp>
#include "../mce/mce.h"
#include "../McJson/McJson.h"

class PlayerListEntry {
public:
    BUILD_ACCESS(std::string, name, 0x18);
    BUILD_ACCESS(std::string, xuid, 0x38);
};

class MobEffectInstance;
class Level;
class ItemStack;

enum class EntityId : std::uint32_t {};

template<>
struct entt::internal::entt_traits<EntityId> {
    using value_type = EntityId;

    using entity_type = std::uint32_t;
    using version_type = std::uint16_t;

    static constexpr entity_type entity_mask = 0x3FFFF;
    static constexpr entity_type version_mask = 0x7FF;
};
struct BlockMovementSlowdownMultiplierComponent {
    vec3 blockMovementSlowdownMultiplier;
};
class EntityRegistry;
class EntityContext {
public:
    EntityRegistry* mRegistry;
    entt::basic_registry<EntityId>* registry;
    EntityId entityId;

    template <typename T>
    T* getComponent() {
        return const_cast<T*>(registry->try_get<T>(entityId));
    }
};

class MCJson::Value;
class SerializedSkin {
public:
    BUILD_ACCESS(std::string, id, 0x0);
    BUILD_ACCESS(std::string, geoType, 0x90);
    BUILD_ACCESS(mce::Image, imageData, 0xA0);
    BUILD_ACCESS(int32_t, skinWidth, 0xA4);
    BUILD_ACCESS(int32_t, skinHeight, 0xA8);
    BUILD_ACCESS(uint8_t*, skinBytes, 0xB0);
    BUILD_ACCESS(MCJson::Value, geometryData, 0x118);
};

struct ActorEquipmentComponent {
    class SimpleContianer* mOffhandContainer;
    class SimpleContainer* mArmorContainer;
};
class Actor;
class ActorDamageSource {
public:
    BUILD_ACCESS(uintptr_t**, vtable, 0x0);
    BUILD_ACCESS(BYTE, cause, 0x8);
};

class ActorDamageByActorSource : public ActorDamageSource {
public:
    BUILD_ACCESS(bool, isCreative, 0x18);
    BUILD_ACCESS(int, entityTypeid, 0x28);
    BUILD_ACCESS(std::string, nametag, 0x30);
};

class Actor {
public:
    template<typename RetType>
    RetType getComponent(uintptr_t address) {
        auto func = reinterpret_cast<RetType(*)(__int64*, int*)>((void*)address);
        __int64* a1 = *(__int64**)((__int64)this + 0x10);
        int a2 = *(DWORD*)((__int64)this + 0x18);
        return func(a1, &a2);
    }
public:
    BUILD_ACCESS(StateVectorComponent*, state, 0x270);
    BUILD_ACCESS(AABB*, aabb, 0x298);
    BUILD_ACCESS(struct AABB, noPtrAabb, 0x298);
    BUILD_ACCESS(Level*, level, 0x230);
    BUILD_ACCESS(EntityContext, entityCtx, 0x08);
    BUILD_ACCESS(EntityContext*, entityCtxPtr, 0x08);
    BUILD_ACCESS(ActorRotationComponent*, rotationComponent, 0x28);
    BUILD_ACCESS(__int64, forEntityTypeID1, 0x10);
    BUILD_ACCESS(int*, forEntityTypeID2, 0x18);
    BUILD_ACCESS(ItemStack*, selectedItem, 0x628);

    float getTicksPerSecond() {
        if (this != nullptr) {
            vec3 targetPos = getStateVector()->Position;
            vec3 targetPosOld = getStateVector()->PrevPosition;
            float hVel = sqrtf(((targetPos.x - targetPosOld.x) * (targetPos.x - targetPosOld.x)) + ((targetPos.z - targetPosOld.z) * (targetPos.z - targetPosOld.z)));
            return hVel;
        }
        return 0.f;
    }

    float getBlocksPerSecond();

    RuntimeIDComponent* getRuntimeIDComponent() {
        static uintptr_t address = SigScan("4C 8B 41 ? 4C 8B C9 48 8B 41 ? 4C 8B 51 ? 49 2B C0 48 C1 F8 ? 48 FF C8 25 ? ? ? ? 49 8B 0C C0 48 83 F9 ? 74 ? 0F 1F 84 00 ? ? ? ? 48 C1 E1 ? 42 81 7C 11 ? ? ? ? ? 4A 8D 04 11 74 ? 48 8B 08 48 83 F9 ? 75 ? 49 8B 41 ? 49 3B 41 ? 74 ? 4C 8B 40 ? 4D 85 C0 74 ? 8B 02 4D 8B 50 ? 44 8B C8 49 8B 48 ? 41 81 E1 ? ? ? ? 49 2B CA 49 C1 E9 ? 48 C1 F9 ? 8B D0 4C 3B C9 73 ? 4B 8B 0C CA 48 85 C9 74 ? 81 E2 ? ? ? ? 4C 8D 0C 91 4D 85 C9 74 ? 41 8B 09 25 ? ? ? ? 33 C1 3D ? ? ? ? 73 ? 49 8B 40 ? 8B D1 81 E2 ? ? ? ? 8B CA 48 C1 E9 ? 83 E2 ? 48 8B 04 C8 48 8D 04 D0 C3 33 C0 C3 CC 40 53");
        return getComponent<RuntimeIDComponent*>(address);
    }

    bool isOnGround() {
        static uintptr_t address = SigScan("4C 8B 41 ?? 41 BB A3 99 E2 C3 48 8B 41 ?? 4C 8B D1 4C 8B 49 ?? 49 2B C0 48 C1 F8 ?? 48 FF C8 49 23 C3 49 8B 04 C0 48 83 F8 FF 74 1C 0F 1F 40 00 48 C1 E0 ?? 46 39 5C 08 ?? 4A 8D 0C 08 74 0D 48 8B 01 48 83 F8 FF 75 E8 49 8B 4A ?? 49 3B 4A ?? 74 58 48 8B 49 ?? 48 85 C9 74 4F 4C 8B 49 ?? 8B 02 8B D0 48 8B 49 ?? 81 E2 ?? ?? ?? ?? 49 2B C9 44 8B C2 49 C1 E8 ?? 48 C1 F9 ?? 4C 3B C1 73 2A 4B 8B 0C C1 48 85 C9 74 21 81 E2 ?? ?? ?? ?? 4C 8D 04 91 4D 85 C0 74 12 25 00 00 FC FF 41 33 00 3D ?? ?? ?? ?? 73 03 B0 ?? C3 32 C0 C3");
        return getComponent<bool>(address);
    }

    void jumpFromGround() {
        static uintptr_t address = SigScan("40 53 48 83 EC ?? 48 8B DA BA 71 F0 CF 0D E8 ?? ?? ?? ?? 8B 0B 4C 8B D0 44 8B C1 41 81 E0 ?? ?? ?? ?? 41 8B C0 4D 8B 4A ?? 49 8B 52 ?? 49 2B D1 48 C1 E8 ?? 48 C1 FA ?? 48 3B C2 73 29 49 8B 04 C1 48 85 C0 74 20 41 81 E0 ?? ?? ?? ?? 4A 8D 14 80 48 85 D2 74 10 8B C1 25 00 00 FC FF 33 02 3D ?? ?? ?? ?? 72 22 89 4C 24 ?? 4C 8D 44 24 ?? 49 8B CA 48 C7 44 24 ?? ?? ?? ?? ?? 45 33 C9 48 8D 54 24 ?? E8 ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 48 83 C4 ?? 5B C3");
        return getComponent<void>(address);
    }
    
    ItemStack* getEquippedTotem() {
        return CallVFunc<85, ItemStack*>(this);
    }

    class SimpleContainer* getArmorContainer() {
        return entityCtx.getComponent<ActorEquipmentComponent>()->mArmorContainer;
    }

    class ItemStack* getArmor(int slot) {
        return getArmorContainer()->getItem(slot);
    }

    bool getStatusFlag(__int64 val) {
        return CallVFunc<0, bool, __int64>(this, val);
    }

    bool isSprinting() {
        return CallVFunc<0, bool, __int64>(this, 3i64);
       // return (**(__int64(__fastcall***)(Actor*, __int64))this)(this, 3i64);
    }

    unsigned int getItemUseDuration() {
       return *((unsigned int*)this + 732);
    }

    bool canAttack(Actor* ent, bool booooool) {
        return CallVFunc<53, bool>(this, ent, booooool);
    };

    bool isValidTarget(Actor* ent) {
        return CallVFunc<55, bool>(this, ent);
    };

    void setSprinting(bool sprint) {
        CallVFunc<153, void>(this, sprint);
    }

    bool isInvisible() {
        return CallVFunc<33, bool>(this);
    };

    bool canShowNametag() {
        return CallVFunc<35, bool>(this);
    };

    bool isImmobile() {
        return CallVFunc<43, bool>(this);
    };

    void resetBlockMovementSlowdownMultiplier() {
        CallVFunc<75, void>(this);
    }

    __int64 setOffhandSlot(ItemStack* item) {
        return CallVFunc<84, __int64>(this, item);
    }

    ItemStack* getOffhandSlot() {
        using getOffhandSlot = ItemStack*(__fastcall*)(Actor*, EntityContext);
        static getOffhandSlot getOff = reinterpret_cast<getOffhandSlot>(SigScan("40 53 48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 8B DA 0F 57 C0 0F 11 44 24 ?? 4C"));
        return getOff(this, this->entityCtx);
    }

    bool isAlive() {
        return *((BYTE*)this + 0x2E1) == 0;
    };

    Level* getLevel()
    {
        return *reinterpret_cast<Level**>(reinterpret_cast<__int64>(this) + 0x230);
    }

    void swing() {
        return CallVFunc<117, void>(this);
    }

    std::vector<MobEffectInstance, std::allocator<MobEffectInstance>>* getAllEffects() {
        using getAllEffect = std::vector<MobEffectInstance, std::allocator<MobEffectInstance>>*(*)(Actor*);
        static getAllEffect getAll = reinterpret_cast<getAllEffect>(SigScan("E8 ?? ?? ?? ?? 4C 8B F0 48 89 45 B0 49 8B 0F"));
        return getAll(this);
    }

    vec3 getPosition() {
        const struct vec3 result = *(vec3*)*((__int64*)this + 0x290);
        return result;
    }

    void* setPosition(vec3 pos) {
        using SetPos_t = vec3 * (__fastcall*)(Actor*, vec3*, const char*);
        static  SetPos_t setpos = reinterpret_cast<SetPos_t>(SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 48 8B DA 48 8B F9 48 8B CB"));
        return setpos(this, &pos, 0);
    }

    StateVectorComponent* getStateVector() {
        return *(StateVectorComponent**)((__int64)this + 0x290);
    };

     void lerpMotion(vec3* a2) {
         getStateVector()->Velocity.x = a2->x;
         getStateVector()->Velocity.y = a2->y;
         getStateVector()->Velocity.z = a2->z;
     }

    std::string* getNametag() {
        uintptr_t sig = NULL;
        using name = std::string* (__thiscall*)(Actor*);
        static name namef = reinterpret_cast<name>(SigScan("48 83 EC ?? 48 8B 81 ?? ?? ?? ?? 48 85 C0 74 3B 48 8B 08 BA ?? ?? ?? ?? 48 8B 40 ?? 48 2B C1 48 C1 F8 ?? 66 3B D0 73 17"));

        return namef(this);
    }

    int getEntityTypeID() {
        static uintptr_t address = SigScan("4C 8B 41 ?? 4C 8B D1 48 8B 41 ?? 4C 8B 49 ?? 49 2B C0 8B 12 48 C1 F8 ?? 48 FF C8 25 14 AD");//1.20.8x
        return (unsigned int)*getComponent<__int64*>(address);
    }

    bool canOpenContainerScreen() {
        using canOpenContainer = bool(*)(Actor*);
        static canOpenContainer canOpenFunc = reinterpret_cast<canOpenContainer>(SigScan("40 53 48 83 EC 20 48 83 B9 50 07"));//1.20.8x
        return canOpenFunc(this);
    }

    bool hasEffect(MobEffect* effect) {
        using hasEffect = bool(*)(Actor*, MobEffect*);
        static hasEffect hasEffectFunc = reinterpret_cast<hasEffect>(SigScan("40 53 48 83 EC ?? 8B 41 ?? 8B 5A ?? 48 8D 54 24 ?? 48 8B 49 ?? 89 44 24 ?? E8 ?? ?? ?? ?? 48 85 C0 74 37"));//1.20.8x
        if (hasEffectFunc) return hasEffectFunc(this, effect);
        return false;
    }

    MobEffectInstance* getEffect(MobEffect* effect) {
        using getEffectMe = MobEffectInstance*(*)(Actor*, MobEffect*);
        static getEffectMe getEffectFunc = reinterpret_cast<getEffectMe>(SigScan("40 53 48 83 EC ?? 8B 41 ?? 8B 5A ?? 48 8D 54 24 ?? 48 8B 49 ?? 89 44 24 ?? E8 ?? ?? ?? ?? 48 85 C0 74 34"));//1.20.8x
        if (getEffectFunc) return getEffectFunc(this, effect);
        return nullptr;
    }

    vec2* getRotationPrev()
    {
        __int64 v1 = *((__int64*)this + 84);
        return (vec2*)(v1 + 8);
    }
    vec2* getRotation()
    {
        __int64 v1 = *((__int64*)this + 84);
        return (vec2*)(v1);
    }

};
