#include "TrialManager.h"

bool TrialManagerHook::IsTrial::handle(__int64 _this, __int64 a2) {
	static auto oFunc = funcPtr->GetFastcall<bool, __int64, __int64>();
	return false;
	return oFunc(_this, a2);
}
