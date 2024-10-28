#pragma once
#include <MemUtils.h>
#include <Math/Math.h>
#include <glm/glm.hpp>

class HoverTextRenderer {
public:
	BUILD_ACCESS(std::string, filteredContent, 0x7);
	BUILD_ACCESS(std::string, content, 0x3);
	BUILD_ACCESS(vec2, offsetPosition, 0x58);
	BUILD_ACCESS(vec2, cursorPosition, 0x50);
	BUILD_ACCESS(vec2, boxDimensionPosition, 0x60);
};

class NinePatchLayer {
public:
	uintptr_t** vtable;
	std::byte padding[48];
	std::string FilteredContent;
	glm::tvec2<float> CursorPosition;
	glm::tvec2<float> Offset;
};