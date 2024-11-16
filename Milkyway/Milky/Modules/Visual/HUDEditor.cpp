#include "HUDEditor.h"

void HUDEditor::setPosition() {
	if (g_Data.getGuiData()) {
		vec2 mousePos = g_Data.mousePos;
		vec2 windowSizeReal = g_Data.getGuiData()->windowSizeReal;
		vec2 windowSize = g_Data.getGuiData()->windowSize;
		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mul(windowSize);

		for (HUD* hud : huds) {
			if (g_Data.isLeftClickDown && hud->rect->contains(&mousePos)) {
				*hud->pos = hud->pos->add(mousePos);
			}
		}
	}
}