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

	namespace PacketHandlerDispatcherInstanceHook {
		class HandleTextPacket : public Hook {
		private:
			static inline std::unique_ptr<FuncHook> funcPtr;
		public:
			HandleTextPacket() : Hook(xorstr_("PacketHandlerDispatcherInstance::handle")) {};
			static __int64 handle(__int64* _this, void* networkIdentifer, __int64* netEventCallback, Packet** packet);
			bool Initialize() override {
				uintptr_t** address = ScanVtable("48 8D 0D ?? ?? ?? ?? 48 89 48 ?? 48 89 07 4C 89 47 ?? E9 AD 0C 00 00", 3);
				return CreateHook(funcPtr, (uintptr_t)address[0][1], handle);
			}
		};
		class HandleSetTitlePacket : public Hook {
		private:
			static inline std::unique_ptr<FuncHook> funcPtr;
		public:
			HandleSetTitlePacket() : Hook(xorstr_("PacketHandlerDispatcherInstance::handle")) {};
			static __int64 handle(__int64* _this, void* networkIdentifer, __int64* netEventCallback, Packet** packet);
			bool Initialize() override {
				uintptr_t** address = ScanVtable("48 8D 15 ?? ?? ?? ?? 48 89 51 ?? 48 89 43 ?? 48 8B C3 48 89 0B 48 8B 5C 24 ?? 48 83 C4 ?? 5F C3 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? ?? 0F 85 ED FE FF FF", 3);
				return CreateHook(funcPtr, (uintptr_t)address[0][1], handle);
			}
		};
	}
}