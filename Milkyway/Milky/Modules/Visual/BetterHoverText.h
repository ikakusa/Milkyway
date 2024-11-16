#pragma once
#include "../Module.h"

class BetterHoverText : public Module {
public:
	bool debug = false;
	bool hideEnchants = false;
	bool durability = false;
	BetterHoverText() : Module(VK_TAB, Category::RENDER, "BetterHoverText", "Improve hover text") {
		addBool("Debug mode", &debug, false);
		addBool("Hide Enchants", &hideEnchants, false);
	}

	std::vector<std::string> enchantIDs{
	"protection",
	"fire protection",
	"feather falling",
	"blast protection",
	"projectile protection",
	"thorns",
	"respiration",
	"depth strider",
	"aqua affinity",
	"sharpness",
	"smite",
	"bane of arthropods",
	"knockback",
	"fire aspect",
	"looting",
	"efficiency",
	"silk touch",
	"unbreaking",
	"fortune",
	"power",
	"punch",
	"flame",
	"infinity",
	"luck of the sea",
	"lure",
	"frost walker",
	"mending",
	"curse of binding",
	"curse of vanishing",
	"impaling",
	"riptide",
	"loyalty",
	"channeling",
	"multishot",
	"piercing",
	"quick charge",
	"soul speed"
	};
};