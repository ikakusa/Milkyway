#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace MouseDeviceHook {
	class feed : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		feed() : Hook(xorstr_("MouseDevice::feed")) {};
		static void handle(__int64 mouseDevice, char buttonId, char isDown, __int16 x, __int16 y, __int16 dx, __int16 dy, bool forcemotionlesspointer);
		bool Initialize() override {
			uintptr_t address = SigScan("48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 83 EC ?? 44 0F");
			return CreateHook(funcPtr, address, handle);
		}
	};
}