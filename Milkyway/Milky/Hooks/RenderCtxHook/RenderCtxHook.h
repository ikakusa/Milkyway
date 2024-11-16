#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace RenderCtxHook {
	class onFocusGained : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		onFocusGained() : Hook("ScreenView::onFocusGained") {};
		static void handle(ScreenView* _this);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 6C 24 ?? 56 57 41 54 41 56 41 57 48 81 EC ?? ?? ?? ?? 0F 29 74 24 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48");
			return CreateHook(funcPtr, address, handle);
		}
	};
	class setupAndRender : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		setupAndRender() : Hook("ScreenView::setupAndRender") {};
		static void handle(ScreenView* _this, MinecraftUIRenderContext* mCtx);
		bool Initialize() override {
			uintptr_t address = SigScan("48 8B C4 48 89 58 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD FF FF 48 81 EC ?? ?? ?? ?? 0F 29 70 B8 0F 29 78 A8 48");
			return CreateHook(funcPtr, address, handle);
		}
	};
	class drawImage : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		drawImage() : Hook("MinecraftUIRenderContext::drawImage") {};
		static void handle(MinecraftUIRenderContext* mCtx, TexturePtr* texture, vec2* pos, vec2* size, vec2* uv, vec2* uvSize, int degree);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 54 41 56 41 57 48 8B EC 48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 F8 4D 8B F9 4D 8B F0 4C");
			return CreateHook(funcPtr, address, handle);
		}
	};
}