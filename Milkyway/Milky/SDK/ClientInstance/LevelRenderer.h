#pragma once
#include <MemUtils.h>
class LevelRendererPlayer {
public:
	BUILD_ACCESS(vec3, cameraPos, 0x620);
};
class LevelRenderer {
public:
	LevelRendererPlayer* getLevelRendererPlayer() {
		return *reinterpret_cast<LevelRendererPlayer**>((uintptr_t)(this) + 0x318);
	}
};