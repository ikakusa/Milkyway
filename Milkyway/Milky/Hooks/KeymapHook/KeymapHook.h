#pragma once
#include "../Hooks.h"

namespace KeyboardHook {
	class Feed : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		Feed() : Hook("Keyboard::feed") {};
		static void handle(unsigned char key, bool isDown);
		bool Initialize() override {
			void* address = (void*)findSig("48 83 ec ? 0f b6 c1 4c 8d 05");
			return CreateHook(funcPtr, address, handle);
		}
	};
}