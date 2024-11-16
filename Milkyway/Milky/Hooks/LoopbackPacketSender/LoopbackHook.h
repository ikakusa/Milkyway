#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace LoopbackHook {
	class sendToServer : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		sendToServer() : Hook("LoopbackPacketSender::sendToServer") {};
		static void handle(LoopbackPacketSender* loopback, Packet* packet);
		static void textreceivehandle(void* packetHandlerDispatcher, void* networkIdentifier, void* netEventCallback, const std::shared_ptr<Packet>& packet);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 0F B6 41");

			return CreateHook(funcPtr, address, handle);
		}
	};
}