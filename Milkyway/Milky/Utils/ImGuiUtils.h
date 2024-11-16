#pragma once
#include "../GameData.h"
#include <Libraries.h>

class ImGuiUtils {
public:
	static float defaultSize;

	static ImGuiIO GetIO();
	static std::string searchQuery;

	static float getScale();
	static float getDeltaTime();
	static vec2 getDisplaySize();
	static vec2 getScreenResolution();
	static float getTextWidth(float textSize, std::string text = "", const ImFont* font = nullptr);
	static float getTextHeight(float textSize, std::string text = "", const ImFont* font = nullptr);

	static inline ImDrawList* drawList = nullptr;
	static void setDrawList(ImDrawList* d);
	static void drawTextGlow(vec2 pos, const std::string& text, UIColor col, const float& size = 1.f, const float& thickness = 100.f, const vec2& offset = vec2(0, 0), ImDrawFlags flags = 0, int segments = 12);
	static void drawText(const std::string& text, UIColor color, vec2 textPos, float textSize = 1.f, bool hasShadow = true);
	static void fillRect(vec4 rect, UIColor color, float round = 0.f, ImDrawFlags flags = 0);
	static void UpdateTextBoxText(std::string& text, int key_code);
	static void fillCircle(vec2 center, float radius, UIColor color, float alpha, int segments);
	static bool isinRect(vec4 rect, vec2 pos);
};