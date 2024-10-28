#include "GameMode.h"
#include "../../GameData.h"

bool GameMode::tryPlace(vec3i blockBelow) {
	BlockSource* region = g_Data.getClientInstance()->getRegion();
	Block* block = region->getBlock(blockBelow.toVec3t());
	BlockLegacy* blockLegacy = (block->blockLegacy);
	if (!blockLegacy->isSolid) {
		vec3i blok(blockBelow);

		// Find neighbour
		static std::vector<vec3i*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3i(0, -1, 0));
			checklist.push_back(new vec3i(0, 1, 0));

			checklist.push_back(new vec3i(0, 0, -1));
			checklist.push_back(new vec3i(0, 0, 1));

			checklist.push_back(new vec3i(-1, 0, 0));
			checklist.push_back(new vec3i(1, 0, 0));
		}

		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3i calc = blok.sub(*current);
			bool Y = !region->getBlock(calc.toVec3t())->blockLegacy->isSolid;
			if (region->getBlock(calc.toVec3t())->blockLegacy->isSolid) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate) {
			this->buildBlock(&blok, i, false);
			return true;
		}
	}
	return false;
}