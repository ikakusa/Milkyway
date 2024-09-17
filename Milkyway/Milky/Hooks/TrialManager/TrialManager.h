#pragma once
#include "../Hooks.h"

namespace TrialManagerHook {
	class IsTrial : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		IsTrial() : Hook(xorstr_("TrialManager::isTrial")) {};
		static bool handle(__int64 _this);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5c 24 ? 57 48 83 ec ? 48 8b d1 48 8b 41 ? 48 85 c0 74 ? 48 83 38 ? 74 ? 48 8b 41 ? 48 85 c0 74 ? f0 ff 40 ? 48 8b 49 ? 48 89 4c 24 ? 48 8b 5a ? 48 89 5c 24 ? 48 8b 09 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 0f b6 f8 48 85 db 74 ? 48 8b cb e8 ? ? ? ? 40 0f b6 c7 48 8b 5c 24 ? 48 83 c4 ? 5f c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc cc cc 48 89 5c 24 ? 48 89 74 24 ? 48 89 7c 24");
			return CreateHook(funcPtr, address, handle);
		}
	};
}