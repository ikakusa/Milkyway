#pragma once

enum class MobEffectID : int {
    EMPTY = 0,
    SPEED = 1,
    SLOWNESS = 2,
    HASTE = 3,
    MINING_FATIGUE = 4,
    STRENGTH = 5,
    INSTANT_HEALTH = 6,
    INSTANT_DAMAGE = 7,
    JUMP_BOOST = 8,
    NAUSEA = 9,
    REGENERATION = 10,
    RESISTANCE = 11,
    FIRE_RESISTANCE = 12,
    WATER_BREATHING = 13,
    INVISIBILITY = 14,
    BLINDNESS = 15,
    NIGHT_VISION = 16,
    HUNGER = 17,
    WEAKNESS = 18,
    POISON = 19,
    WITHER = 20,
    HEALTH_BOOST = 21,
    ABSORPTION = 22,
    SATURATION = 23,
    LEVITATION = 24,
    FATAL_POISON = 25,
    CONDUIT_POWER = 26,
    SLOW_FALLING = 27,
    BAD_OMEN = 28,
    VILLAGE_HERO = 29,
    DARKNESS = 30,
    TRIAL_OMEN = 31,
    WIND_CHARGED = 32,
    WEAVING = 33,
    OOZING = 34,
    INFESTED = 35,
    RAID_OMEN = 36,
};

class MobEffect {
public:
    static MobEffect* getEffectByName(std::string name) {
        using getByName = MobEffect * (*)(std::string*);
        static getByName geteffect = reinterpret_cast<getByName>(SigScan("48 83 EC ?? 48 83 79 ?? ?? 4C 8B C1 4C 8B 51 ?? 48 8B D1 72 03 48 8B 11 33 C9 49 B9 25 23 22 84 E4 9C F2 CB 4D 85 D2 74 2A 49 BB B3 01 00 00 00 01 00 00 0F 1F 40 00 66 0F 1F 84 00 00 00 00 00 0F B6 04 11 48 FF C1 4C 33 C8 4D 0F AF CB 49 3B CA 72 ED 48 8D 54 24 ?? E8 ?? ?? ?? ?? 48 8B 48 ?? 48 8B 05 ?? ?? ?? ?? 48 85 C9 48 0F 45 C1 48 3B 05 ?? ?? ?? ?? 74 09 48"));
        if (geteffect) return geteffect(&name);
        return nullptr;
    }
};

class MobEffectInstance {
public:
    BUILD_ACCESS(int, amplifier, 0x14);
    BUILD_ACCESS(int, duration, 0x4);
public:
	std::string* getDisplayName() {
        std::string result = "";
		using getDisplayName = std::string(*)(MobEffectInstance*, std::string*);
		static getDisplayName getName = reinterpret_cast<getDisplayName>(SigScan("48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 F0 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 00 48 8B F2 4C 8B E1 48"));
		getName(this, &result);
		return &result;
	}
    
    //Color* getAverageColorValue() {
    //    Color result;
    //    using getAverageColor = Color*(*)(Color*, std::vector<MobEffectInstance*>);
    //    static getAverageColor getColor= reinterpret_cast<getAverageColor>(findSig(xorstr_("40 53 48 83 EC ?? 4C 8B 52 ?? 4C 8B D9")));
    //    getColor(&result, z);
    //    return &result;
    //}
};