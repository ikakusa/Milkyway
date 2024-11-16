#include "RenderCtxHook.h"

void RenderCtxHook::onFocusGained::handle(ScreenView* _this) {
	static auto oFunc = funcPtr->GetFastcall<void, ScreenView*>();
	return oFunc(_this);
}

void RenderCtxHook::setupAndRender::handle(ScreenView* _this, MinecraftUIRenderContext* mCtx) {
	static auto oFunc = funcPtr->GetFastcall<void, ScreenView*, MinecraftUIRenderContext*>();
	//std::stringstream ss;
	//ss << std::hex << (*(UINT64*)mCtx - getBaseAddress());
	//writelog("%s", ss.str().c_str());
	return oFunc(_this, mCtx);
}

void RenderCtxHook::drawImage::handle(MinecraftUIRenderContext* mCtx, TexturePtr* texture, vec2* pos, vec2* size, vec2* uv, vec2* uvSize, int degree) {
	static auto oFunc = funcPtr->GetFastcall<void, MinecraftUIRenderContext*, TexturePtr*, vec2*, vec2*, vec2*, vec2*, int>();
	if (strcmp(texture->getFilePath().c_str(), "textures/ui/selected_hotbar_slot") == 0) {
		static float lerpedPos = pos->x;
		lerpedPos = animate(pos->x, lerpedPos, 10.f * g_Data.deltatime);
		pos->x = lerpedPos;
	}
	return oFunc(mCtx, texture, pos, size, uv, uvSize, degree);
}