#include "ModuleManager.h"

bool ModuleManager::Initialize() {
	{
		add<HUDEditor>();
		add<ReachDisplay>();
		add<Brightness>();
		add<BetterHoverText>();
		add<NotificationMod>();
		add<ClickGui>();
		add<AutoGG>();
		add<AutoRequeue>();
		add<CPS>();
	}

	initialized = true;
	loadConfig();
	return true;
}

ModuleManager moduleMgr = ModuleManager();