#include "CPS.h"

void CPS::onEnable() {
}

void CPS::onDisable() {
}

void CPS::onImGuiRender(ImDrawList* d) {
	auto guidata = g_Data.getGuiData();
	auto lp = g_Data.getLocalPlayer();

	if (guidata) {
		std::string str = StringUtils::combine(std::to_string(g_Data.cpsLeft), " | ", std::to_string(g_Data.cpsRight));
		float fontsize = fontSize;
		vec2 windowSize = guidata->windowSizeReal;
		float width = 55.f * fontsize;
		float height = ImGuiUtils::getTextHeight(fontsize, str);
		vec2 mousePos = g_Data.mousePos;

		if (vec4(posX, posY, posX + width + 10.f, posY + height + 10.f).contains(&g_Data.mousePos) && g_Data.isLeftClickDown && (g_Data.dragModule == "" || g_Data.dragModule == this->getModuleName())) {
			isDragging = g_Data.isLeftClickDown;
			g_Data.dragModule = this->getModuleName();
		}

		if (!g_Data.isLeftClickDown) {
			isDragging = false;
			g_Data.dragModule = "";
		}

		vec4 pos = vec4(posX, posY, posX + width + 10.f, posY + height + 10.f);
		d->PushClipRect(ImVec2(pos.x, pos.y), ImVec2(pos.z, pos.w), true);
		
		if (guidata->windowSizeReal.x <= pos.z) posX -= 1.f;
		if (-1.f >= pos.x) posX += 1.f;
		if (guidata->windowSizeReal.y <= pos.w) posY -= 1.f;
		if (-1.f >= pos.y) posY += 1.f;

		if (moduleMgr.get<HUDEditor>()->isEnabled() || moduleMgr.get<ClickGui>()->isEnabled()) {
			ImGuiUtils::fillRect(pos, UIColor(200, 200, 200, 100));

			if (isDragging) {
				posX = mousePos.x;
				posY = mousePos.y;
			}
		}
		if (lp) {
			ImGuiUtils::fillRect(pos, UIColor(0, 0, 0, 100));
			ImGuiUtils::drawText(str, UIColor(255, 255, 255), vec2(pos.x + 13.5f, pos.y + 5.f), fontsize);
		}
		d->PopClipRect();
	}
}