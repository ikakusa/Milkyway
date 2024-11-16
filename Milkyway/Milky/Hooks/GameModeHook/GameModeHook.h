#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace GameModeHook {
	class getPickRange : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		getPickRange() : Hook("GameMode::getPickRange") {};
		static float handle(GameMode* gm, __int64 inputMode, bool isVR);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 57 48 83 EC ?? 45 84");
			return CreateHook(funcPtr, address, handle);
		}
	};

	class startDestroyBlock : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		startDestroyBlock() : Hook("GameMode::startDestroyBlock") {};
		static bool handle(GameMode* gm, vec3i blockPos, int face);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 ?? 45 0F B6 E8 4C 8B E2 4C");
			return CreateHook(funcPtr, address, handle);
		}
	};

	class attack : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		attack() : Hook("GameMode::attack") {};
		static void handle(GameMode* gm, Actor* ent);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 A0 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 ?? 48 8B F2 48 8B F9 45 33 F6 4C 89 75 F0 48");
			return CreateHook(funcPtr, address, handle);
		}
	};
}