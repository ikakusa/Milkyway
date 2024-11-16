#include "ItemHook.h"

void ItemHook::appendFormattedHoverText::handle(Item* _this, ItemStackBase* stack, Level* level, std::string* hovertext, bool showCategory) {
	static auto oFunc = funcPtr->GetFastcall<void, Item*, ItemStackBase*, Level*, std::string*, bool>();
	oFunc(_this, stack, level, hovertext, showCategory);

	if (!moduleMgr.isInitialized()) return;

	auto hover = moduleMgr.get<BetterHoverText>();

	if (hover->isEnabled()) {
		int index = 0;
		int enchantCount = 0;

		if (hover->hideEnchants) {
			std::istringstream iss(*hovertext);
			std::string line;
			std::ostringstream oss;


			for (std::string line2; std::getline(iss, line);) {
				bool found = false;
				if (index != 0) {
					for (std::string enchant : hover->enchantIDs) {
						std::transform(line.begin(), line.end(), line.begin(), ::tolower);
						if (line.find(enchant) != std::string::npos) {
							enchantCount++;
							found = true;
						}
					}
				}
				if (!found) {
					oss << line << "\n";
				}
				found = false;
				index++;
			}

			if (enchantCount > 0) {
				*hovertext = oss.str();
				hovertext->append(fmt::format("{}7{} {}{}r", "\xc2\xa7", enchantCount, enchantCount == 1 ? "Enchant" : "Enchants", "\xc2\xa7"));
			}
		}

		auto item = *stack->item;

		std::string rawName = std::string(item->rawname.c_str());

		if (rawName.find("shulker_box") != std::string::npos) {
			if (hover->debug) hovertext->append(fmt::format("\n{}7{}:{} {}r", "\xc2\xa7", item->namespaceId, rawName, "\xc2\xa7"));
			return;
		}

		if (hover->debug) hovertext->append(fmt::format("\n{}7{}:{} ({}){}r", "\xc2\xa7", item->namespaceId, rawName, item->id, "\xc2\xa7"));
	}
}