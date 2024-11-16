#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace FreeLibsAndExitHook {
	class Exit : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		Exit() : Hook(xorstr_("FreeLibrariesAndExit")) {};
		static void handle(HMODULE mod, DWORD code);
		bool Initialize() override {
			uintptr_t address = (uintptr_t)FreeLibraryAndExitThread;
			return CreateHook(funcPtr, address, handle);
		}
	};
}