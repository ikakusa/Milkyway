#include "MouseDevice.h"

void MouseDeviceHook::feed::handle(__int64 mouseDevice, char buttonId, char isDown, __int16 x, __int16 y, __int16 dx, __int16 dy, bool forcemotionlesspointer) {
	static auto oFunc = funcPtr->GetFastcall<void, __int64, char, char, __int16, __int16, __int16, __int16, bool>();
	if (!moduleMgr.isInitialized()) return oFunc(mouseDevice, buttonId, isDown, x, y, dx, dy, forcemotionlesspointer);
	if (ImGui::GetCurrentContext() != nullptr) {
		ImGuiIO& io = ImGui::GetIO();

		io.MousePos = ImVec2(x, y);
		g_Data.mousePos = { x, y };

		auto clickgui = moduleMgr.get<ClickGui>();

		g_Data.leftClick = false;
		g_Data.rightClick = false;
		g_Data.midClick = false;

		switch (buttonId)
		{
		case 1: //LMB
			io.MouseDown[0] = isDown;
			g_Data.isLeftClickDown = isDown;
			g_Data.leftClick = true;
			break;
		case 2: //RMB
			io.MouseDown[1] = isDown;
			g_Data.isRightClickDown = isDown;
			g_Data.rightClick = true;
			break;
		case 3: { //MMB
			io.MouseDown[2] = isDown;
			if (isDown == 1) {
				moduleMgr.onMiddleClick();
			}
			g_Data.midClick = true;
			g_Data.isMidClickDown = isDown;
			break;
		}
		case 4:
			io.MouseWheel = isDown < 0 ? -0.5f : 0.5f;
			if (isDown < 0 && clickgui->catRect.y + 25.f < clickgui->guiRect.w - 50.f)
				clickgui->yCatOff += 25.f;
			else if (isDown > 0 && clickgui->catRect.w - 25.f > clickgui->guiRect.y + 150.f)
				clickgui->yCatOff -= 25.f;
			break;
		}

		if (clickgui->isEnabled())
			return;
	}
	return oFunc(mouseDevice, buttonId, isDown, x, y, dx, dy, forcemotionlesspointer);
}