#pragma once
#include "../Hooks.h"

namespace RenderCtxHook {
	class SetupAndRender : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		SetupAndRender() : Hook("RenderCtx::setupAndRender") {};
		static void handle(ScreenView* _this, MinecraftUIRenderContext mCtx);
		bool Initialize() override {
			uintptr_t address = SigScan("448 8B C4 48 89 58 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 B8 FD FF FF 48 81 EC ?? ?? ?? ?? 0F 29 70 B8 0F 29 78 A8 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C");
			return CreateHook(funcPtr, address, handle);
		}
	};
}