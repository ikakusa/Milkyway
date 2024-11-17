#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace TrialManagerHook {
	class IsTrial : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		IsTrial() : Hook(xorstr_("TrialManager::isTrial")) {};
		static bool handle(__int64 _this, __int64 a2);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5c 24 ? 48 89 74 24 ? 57 48 83 ec ? 48 8b 41 ? 48 85 c0 0f 84 ? ? ? ? 80 38 ? 0f 84 ? ? ? ? 48 8b 41 ? 48 85 c0 74 ? f0 ff 40 ? 48 8b 41 ? 48 89 44 24 ? 48 8b 59 ? 48 89 5c 24 ? 48 8b 49 ? 48 89 4c 24 ? 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 0f b6 f0 48 85 db 74 ? bf ? ? ? ? 8b cf f0 0f c1 4b ? 83 f9 ? 75 ? 48 8b 13 48 8b cb 48 8b 02 ff 15 ? ? ? ? f0 0f c1 7b ? 83 ff ? 75 ? 48 8b 03 48 8b cb 48 8b 40 ? ff 15 ? ? ? ? 40 0f b6 c6 48 8b 5c 24 ? 48 8b 74 24 ? 48 83 c4 ? 5f c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc 48 89 5c 24 ? 48 89 74 24 ? 48 89 7c 24");
			return CreateHook(funcPtr, address, handle);
		}
	};
}