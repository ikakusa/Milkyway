#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace ClientInstanceHook {
	class Update : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		Update() : Hook("ClientInstance::update") {};
		static void handle(ClientInstance* _this, bool isInitFinished);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 48 89 7C 24 ?? 55 41 54 41 55 41 56 41 57 48 8D AC 24 C0 FA FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44");
			return CreateHook(funcPtr, address, handle);
		}
	};

	namespace MinecraftHook {
		class update : public Hook {
		private:
			static inline std::unique_ptr<FuncHook> funcPtr;
		public:
			update() : Hook("MinecraftGame::update") {};
			static void handle(MinecraftGame* _this);
			bool Initialize() override {
				uintptr_t address = SigScan("48 8B C4 48 89 58 ?? 48 89 70 ?? 48 89 78 ?? 55 41 54 41 55 41 56 41 57 48 8D A8 68 F7 FF FF 48 81 EC ?? ?? ?? ?? 0F 29 70 C8 0F");
				return CreateHook(funcPtr, address, handle);
			}
		};
	}
}