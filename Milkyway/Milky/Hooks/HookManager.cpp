#include "HookManager.h"
#include "../Logger/Logger.h"
void HookManager::initHooks() {
	hooks.push_back(new TrialManagerHook::IsTrial());
	hooks.push_back(new CommandHook::ValidRange());
	hooks.push_back(new RenderCtxHook::setupAndRender());
	hooks.push_back(new RenderCtxHook::onFocusGained());
	hooks.push_back(new FreeLibsAndExitHook::Exit());
	hooks.push_back(new ClientInstanceHook::Update());
	hooks.push_back(new KeyboardHook::Feed());
	hooks.push_back(new ActorHook::LocalPlayerHook::NormalTick());
	hooks.push_back(new ActorHook::MobHook::getCurrentSwingDurationHook());
	hooks.push_back(new ConnectionReqHook::create());
	hooks.push_back(new GameModeHook::getPickRange());
	hooks.push_back(new GameModeHook::startDestroyBlock());
	hooks.push_back(new GameModeHook::attack());
	hooks.push_back(new LoopbackHook::sendToServer());
	hooks.push_back(new FontHook::drawTransformed());
	hooks.push_back(new RenderCtxHook::drawImage());
	hooks.push_back(new OptionsHook::getGamma());
	hooks.push_back(new ItemHook::appendFormattedHoverText());
	hooks.push_back(new ClientInstanceHook::MinecraftHook::update());
	hooks.push_back(new MouseDeviceHook::feed());
	
	for (auto hook : hooks) {
		if (hook->Initialize()) {
			writelog("%s has been initialized", hook->name.c_str());
		}
		MH_EnableHook(MH_ALL_HOOKS);
	}
	DXHook::setupDXHook();
	writelog("fix that old piano");
}