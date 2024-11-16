#include "OptionsHook.h"

float OptionsHook::getGamma::handle(__int64 _this) {
	static auto oFunc = funcPtr->GetFastcall<float, __int64>();
	if (moduleMgr.isInitialized() && moduleMgr.get<Brightness>()->isEnabled()) {
		return 20.0f;
	}
	return oFunc(_this);
}