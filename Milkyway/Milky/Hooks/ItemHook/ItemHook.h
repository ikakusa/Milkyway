#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace ItemHook {
	class appendFormattedHoverText : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		appendFormattedHoverText() : Hook("Item::appendFormattedHoverText") {};
		static void handle(Item* _this, ItemStackBase* stack, Level* level, std::string* hovertext, bool showCategory);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D0 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 ?? 49 8B F1 4D 8B E0");
			return CreateHook(funcPtr, address, handle);
		}
	};
}