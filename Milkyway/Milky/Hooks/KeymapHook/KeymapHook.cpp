#include "KeymapHook.h"
#include "../../Utils/ImGuiUtils.h"

void KeyboardHook::Feed::handle(unsigned char key, bool isDown) {
	static auto oFunc = funcPtr->GetFastcall<void, unsigned char, bool>();
	if (key) {
		if (!moduleMgr.isInitialized()) return oFunc(key, isDown);
		auto clickgui = moduleMgr.get<ClickGui>();
		if (!clickgui) return oFunc(key, isDown);
		
		g_Data.updateGameData(key, isDown);
		
		if (isDown && clickgui->isEnabled() && ((key == VK_OEM_2) || (key == 0x2E) || (key == 0x08) || (key == 0x20) || (key >= 0x60 && key <= 0x6D) || (key >= 0x30 && key <= 0x5A))) {
			ImGuiUtils::UpdateTextBoxText(ImGuiUtils::searchQuery, key);
			return;
		}
		if (g_Data.getMCGame()->canMove) moduleMgr.onKey(key, isDown);
		return oFunc(key, isDown);
	}
}