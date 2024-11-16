#include "FontHook.h"

void FontHook::drawTransformed::handle(__int64 font, ScreenContext* screenCtx, std::string* txt, float x, float y, Color color, float angle, float s, bool centered, float maxWidth, bool shadow) {
	static auto oFunc = funcPtr->GetFastcall<void, __int64, ScreenContext*, std::string*, float, float, Color, float, float, bool, float, bool> ();
	*txt = "Milkyway!";
	color = Color(129, 101, 194);
	return oFunc(font, screenCtx, txt, x, y, color, angle, s, centered, maxWidth, shadow);
}
