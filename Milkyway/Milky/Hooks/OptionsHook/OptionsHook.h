#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace OptionsHook {
	class getGamma : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		getGamma() : Hook("Options::getGamma") {};
		static float handle(__int64 _this);
		bool Initialize() override {
			uintptr_t address = SigScan("48 83 ec ? 80 b9 ? ? ? ? ? 48 8d 54 24 ? 48 8b 01 48 8b 40 ? 74 ? 41 b8 ? ? ? ? ff 15 ? ? ? ? 48 8b 10 48 85 d2 74 ? 48 8b 42 ? 48 8b 88 ? ? ? ? 48 85 c9 74 ? e8 ? ? ? ? 48 83 c4 ? c3 f3 0f 10 42 ? 48 83 c4 ? c3 41 b8 ? ? ? ? ff 15 ? ? ? ? 48 8b 10 48 85 d2 75 ? e8 ? ? ? ? cc e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc cc cc cc cc 48 89 5c 24");
			return CreateHook(funcPtr, address, handle);
		}
	};
}