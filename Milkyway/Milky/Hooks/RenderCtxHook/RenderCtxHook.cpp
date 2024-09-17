#include "RenderCtxHook.h"

void RenderCtxHook::SetupAndRender::handle(ScreenView* _this, MinecraftUIRenderContext mCtx) {
	static auto oFunc = funcPtr->GetFastcall<void, ScreenView*, MinecraftUIRenderContext>();
	return oFunc(_this, mCtx);
}