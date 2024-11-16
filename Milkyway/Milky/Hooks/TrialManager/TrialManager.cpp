#include "TrialManager.h"

bool TrialManagerHook::IsTrial::handle(__int64 _this) {
	static auto oFunc = funcPtr->GetFastcall<bool, __int64>();
	return oFunc(_this);
}
