#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace ActorHook {
	namespace LocalPlayerHook {
		class NormalTick : public Hook {
		private:
			static inline std::unique_ptr<FuncHook> funcPtr;
		public:
			NormalTick() : Hook("LocalPlayer::normalTick") {}
			static void handle(Actor* lp);
			bool Initialize() override {
				uintptr_t address = SigScan("48 8B C4 48 89 58 ?? 48 89 70 ?? 48 89 78 ?? 55 41 54 41 55 41 56 41 57 48 8D A8 88 FB FF FF 48 81 EC ?? ?? ?? ?? 0F 29 70 C8 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 8B F1 45");
				return CreateHook(funcPtr, address, handle);
			}
		};
	}
	namespace MobHook {
		class getCurrentSwingDurationHook : public Hook {
		private:
			static inline std::unique_ptr<FuncHook> funcPtr;
		public:
			getCurrentSwingDurationHook() : Hook("Mob::getCurrentSwingDuration") {}
			static int handle(Actor* ent);
			bool Initialize() override {
				uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 6C 24 ?? 56 57 41 56 48 83 EC ?? 8B 41 ?? 48 8D 54 24 ?? 48 8B 35");
				return CreateHook(funcPtr, address, handle);
			}
		};
	}
}