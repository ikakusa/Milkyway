#include "Notification.h"
#include "../Modules/ModuleManager.h"

Notify notify = Notify();

void Notify::drawNotifications(ImDrawList* d) {
	int index = 0;
	auto io = ImGui::GetIO();
	auto guidata = g_Data.getGuiData();

	if (guidata && moduleMgr.isInitialized() && moduleMgr.get<NotificationMod>() && moduleMgr.get<NotificationMod>()->isEnabled()) {
		vec2 windowSize = guidata->windowSizeReal;
		
		static auto height = 70.f;
		auto xPos = windowSize.x;
		auto yPos = windowSize.y - height - 20.f;
		float sped = 6.8f * io.DeltaTime;

		for (auto& n : notifs) {
			if (!n) continue;
			float textHeight = ImGuiUtils::getTextHeight(1.3f, n->message);
			float length = std::fmax(ImGuiUtils::getTextWidth(1.3f, n->message), ImGuiUtils::getTextWidth(1.3f, n->title));
			xPos = windowSize.x - length - 40.f;
			
			if (!n->init) {
				n->pos.x = windowSize.x + 100.f;
				n->pos.y = yPos;
				n->init = true;
			}

			n->duration -= io.DeltaTime;
			n->pos.y = animate(yPos, n->pos.y, sped);

			if (n->duration <= 0.2f) {
				n->pos.x = animate(windowSize.x + 100.f, n->pos.x, sped);
			}
			else {
				n->pos.x = animate(xPos, n->pos.x, sped);
			}
			if (n->duration <= 0.f) {
				delete notifs[index];
				notifs.erase(notifs.begin() + index);
				continue;
			}
			
			ImGuiUtils::fillRect(vec4(n->pos.x - 50.f, n->pos.y - textHeight, n->pos.x + length + 10.f, n->pos.y + textHeight * 2.f), UIColor(30, 30, 30), 10.f, ImDrawFlags_RoundCornersAll);
			ImGuiUtils::fillRect(vec4(n->pos.x - 50.f, n->pos.y - textHeight, n->pos.x - 42.f, n->pos.y), UIColor(221, 34, 34), 10.f, ImDrawFlags_RoundCornersTopLeft);
			ImGuiUtils::fillRect(vec4(n->pos.x - 50.f, n->pos.y, n->pos.x - 42.f, n->pos.y + textHeight * 2.f), UIColor(221, 34, 34), 10.f, ImDrawFlags_RoundCornersBottomLeft);
			ImGuiUtils::drawText(n->message, UIColor(255, 255, 255), vec2(n->pos.x - 10.f, n->pos.y), 1.3f);

			yPos -= textHeight * 2 + 30.f;
			index++;
		}
	}
}