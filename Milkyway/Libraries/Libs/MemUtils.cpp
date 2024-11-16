#include "MemUtils.h"
#include <Psapi.h>

#include "../../Milky/Logger/Logger.h"
void MemoryUtils::init() {
	MH_Initialize();
	isInitialized = true;
}

void MemoryUtils::restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
uintptr_t MemoryUtils::findSig(const char* szSignature) {
	const char* szModule = "Minecraft.windows.exe";
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
	static const auto rangeStart = (uintptr_t)GetModuleHandleA(szModule);
	static MODULEINFO miModInfo;
	static bool init = false;
	if (!init) {
		init = true;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	}
	static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;
	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;
	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pattern)
			return firstMatch;
		while (*(PBYTE)pattern == ' ')
			pattern++;
		if (!*pattern)
			return firstMatch;
		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}
		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
			if (!firstMatch)
				firstMatch = pCur;
			if (!pattern[2] || !pattern[1])
				return firstMatch;
			pattern += 2;
		}
		else {
			pattern = szSignature;
			firstMatch = 0;
		}
	}

	const char* sig = szSignature;
	writelog("dead");
	return 0u;
} 