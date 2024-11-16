#include "ReachDisplay.h"

void ReachDisplay::onEnable() {
}

void ReachDisplay::onDisable() {
}

void ReachDisplay::onImGuiRender(ImDrawList* d) {
	auto guidata = g_Data.getGuiData();
	auto lp = g_Data.getLocalPlayer();

	if (guidata && lp) {
		std::string str = StringUtils::combine("Reach: ", g_Data.reachStr);
		float fontsize = fontSize;
		vec2 windowSize = guidata->windowSizeReal;
		float width = ImGuiUtils::getTextWidth(fontsize, str);
		float height = ImGuiUtils::getTextHeight(fontsize, str);

		vec2 mousePos = g_Data.mousePos;

		if (vec4(posX, posY, posX + width + 10.f, posY + height + 10.f).contains(&g_Data.mousePos) && g_Data.isLeftClickDown) {
			isDragging = g_Data.isLeftClickDown;
		}

		if (!g_Data.isLeftClickDown) {
			isDragging = false;
		}

		vec4 pos = vec4(posX, posY, posX + width + 10.f, posY + height + 10.f);

		if (guidata->windowSizeReal.x <= pos.z) posX -= 1.f;
		if (-1.f >= pos.x) posX += 1.f;
		if (guidata->windowSizeReal.y <= pos.w) posY -= 1.f;
		if (-1.f >= pos.y) posY += 1.f;

		if (isDragging) {
			posX = mousePos.x;
			posY = mousePos.y;
		}

		ImGuiUtils::fillRect(pos, UIColor(0, 0, 0, 100));
		ImGuiUtils::drawText(str, UIColor(255, 255, 255), vec2(pos.x + 5.f, pos.y + 5.f), fontsize);
	}
}