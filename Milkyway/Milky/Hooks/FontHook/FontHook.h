#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace FontHook {
	class drawTransformed : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		drawTransformed() : Hook(xorstr_("Font::drawTransformed")) {};
		static void handle(__int64 font, ScreenContext* screenCtx, std::string* txt, float x, float y, Color color, float angle, float s, bool centered, float maxWidth, bool shadow);
		bool Initialize() override {
			uintptr_t address = SigScan("48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 81 EC ?? ?? ?? ?? 0F 29 70 C8 0F 29 78 B8 44 0F 29 40 A8 44 0F 29 48 98 44 0F 29 50 88 44 0F 29 98 78 FF FF FF 44 0F 28");
			return CreateHook(funcPtr, address, handle);
		}
	};
}