#include "ImGuiUtils.h"

float ImGuiUtils::defaultSize = 22.f;

ImGuiIO ImGuiUtils::GetIO() { return ImGui::GetIO(); };
float ImGuiUtils::getDeltaTime() { return GetIO().DeltaTime; };
std::string ImGuiUtils::searchQuery = "";

vec2 ImGuiUtils::getScreenResolution() { return vec2(g_Data.getGuiData()->widthReal, g_Data.getGuiData()->heightReal); }

float ImGuiUtils::getScale() {
	vec2 windowsize = getScreenResolution(), basesize = getDisplaySize();
	return std::min(windowsize.x / basesize.x, windowsize.y / basesize.y);
}

float ImGuiUtils::getTextHeight(float textSize, std::string text, const ImFont* font) {
	if (font) return floor(font->CalcTextSizeA(defaultSize * textSize * getScale(), FLT_MAX, -1, text.c_str()).y);
	return floor(ImGui::GetFont()->CalcTextSizeA(defaultSize * textSize * getScale(), FLT_MAX, -1, text.c_str()).y);
}
float ImGuiUtils::getTextWidth(float textSize, std::string text, const ImFont* font) {
	if (font) return floor(font->CalcTextSizeA(defaultSize * textSize * getScale(), FLT_MAX, -1, text.c_str()).x);
	return floor(ImGui::GetFont()->CalcTextSizeA(defaultSize * textSize * getScale(), FLT_MAX, -1, text.c_str()).x);
}


void ImGuiUtils::setDrawList(ImDrawList* d) {
	drawList = d;
}

vec2 ImGuiUtils::getDisplaySize() {
	RECT drect;
	const HWND h = GetDesktopWindow();
	GetClientRect(h, &drect);
	return vec2((float)drect.right, (float)drect.bottom);
}

void ImGuiUtils::drawTextGlow(vec2 pos, const std::string& text, UIColor col, const float& size, const float& thickness, const vec2& offset, ImDrawFlags flags, int segments) {
	float textSize = size * getScale();
	float glowSize = std::fmax(textSize / 2.f, 1.0f);
	for (char c : text) {
		ImVec2 charSize = ImVec2(ImGuiUtils::getTextWidth(textSize, std::string("O", c)), ImGuiUtils::getTextHeight(textSize, std::string("O", c).c_str()));
		drawList->AddShadowCircle(ImVec2(pos.x + (charSize.x / 2), pos.y + (charSize.y)), glowSize, col.toImColor(), thickness, ImVec2(offset.x, offset.y), flags, segments * 2);
		pos.x += charSize.x;
	}
}

void ImGuiUtils::drawText(const std::string& text, UIColor color, vec2 pos, float fontSize, bool hasShadow) {
	auto io = ImGui::GetIO();
	if (hasShadow) {
		drawList->AddText(nullptr, fontSize * defaultSize * getScale(), vec2(pos.x + 2.f * getScale(), pos.y + 2.f * getScale()).toImVec2(), UIColor(20, 20, 20).toImColor(), text.c_str());
	}
	drawList->AddText(nullptr, fontSize * defaultSize * getScale(), pos.toImVec2(), color.toImColor(), text.c_str());
}

void ImGuiUtils::fillCircle(vec2 center, float radius, UIColor color, float alpha, int segments) {
	if (!ImGui::GetCurrentContext())
		return;

	drawList->AddCircleFilled(ImVec2(center.x, center.y), radius, color.toImColor(), segments);
}

void ImGuiUtils::fillRect(vec4 rect, UIColor color, float round, ImDrawFlags flags) {
	auto io = ImGui::GetIO();
	drawList->AddRectFilled(ImVec2(rect.x, rect.y), ImVec2(rect.z, rect.w), color.toImColor(), round, flags);
}

void ImGuiUtils::UpdateTextBoxText(std::string& text, int key_code) {
	static bool isAllSelected;

	if (!g_Data.isKeyDown(VK_CONTROL) && ((key_code == VK_OEM_2) || (key_code == 0x20) || (key_code >= 0x60 && key_code <= 0x6D) || (key_code >= 0x30 && key_code <= 0x5A))) {
		if (text.length() >= 40) return;
		if (g_Data.isKeyDown(VK_SHIFT)) {
			switch (key_code)
			{
			case 0x31: {
				text.append("!");
				return;
			}
			case 0x32: {
				text.append("\"");
				return;
			}
			case 0x33: {
				text.append("#");
				return;
			}
			case 0x34: {
				text.append("$");
				return;
			}
			case 0x35: {
				text.append("%");
				return;
			}
			case 0x36: {
				text.append("&");
				return;
			}
			case 0x37: {
				text.append("'");
				return;
			}
			case 0x38: {
				text.append("(");
				return;
			}
			case 0x39: {
				text.append(")");
				return;
			}
			case VK_OEM_2: {
				text.append("?");
				return;
			}
			default:
				break;
			}
		}
		text.push_back(!g_Data.isKeyDown(0x10) ? std::tolower((char)key_code, std::locale()) : (char)key_code);
	}
	else if (key_code == 8 && !text.empty()) {
		text.pop_back();
	}

	if (!g_Data.isKeyDown(VK_CONTROL)) {
		if (isAllSelected) {
			text.clear();
			isAllSelected = false;
		}
	}

	if (key_code == 0x2E && !text.empty()) {
		text.clear();
	}
	if (g_Data.isKeyDown(VK_CONTROL)) {
		switch (key_code) {
		case 'V': {
			if (OpenClipboard(NULL)) {
				HANDLE clip;
				std::string r;
				clip = GetClipboardData(CF_TEXT);
				if (!clip) return;
				char* pntchr = (char*)clip;

				while (*pntchr != 0) {
					r += *pntchr;
					pntchr++;
				}
				r = r.substr(0, 40);
				int num = 40;
				int cur = r.length();
				while (cur + text.length() >= 40 && num != 0 && cur != 0) {
					r = r.substr(0, num);
					num--;
					cur--;
				}
				text.append(r);
				text = text.substr(0, 40);
				CloseClipboard();
			}
			break;
		}
		case 'A': {
			isAllSelected = true;
			break;
		}
		default: {
			break;
		}
		}
	}
}

bool ImGuiUtils::isinRect(vec4 rect, vec2 pos) {
	if (rect.contains(&pos)) return true;
	return false;
}