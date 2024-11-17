#include "LoopbackHook.h"

void LoopbackHook::sendToServer::handle(LoopbackPacketSender* loopback, Packet* packet) {
	static auto oFunc = funcPtr->GetFastcall<void, LoopbackPacketSender*, Packet*>();
	if (!moduleMgr.isInitialized()) return oFunc(loopback, packet);

	if (packet->isInstanceOf<TextPacket>()) {
		auto pkt = (TextPacket*)packet;
		if (pkt->Message._Starts_with(".")) {
			return;
		}
	}
	return oFunc(loopback, packet);
}

void LoopbackHook::sendToServer::textreceivehandle(void* packetHandlerDispatcher, void* networkIdentifier, void* netEventCallback, const std::shared_ptr<Packet>& packet) {
	static auto oFunc = funcPtr->GetFastcall<void, void*, void*, void*, const std::shared_ptr<Packet>&>();
	auto packetPtr = packet;

	return oFunc(packetHandlerDispatcher, networkIdentifier, netEventCallback, packet);
}

__int64 LoopbackHook::PacketHandlerDispatcherInstanceHook::HandleTextPacket::handle(__int64* _this, void* networkIdentifer, __int64* netEventCallback, Packet** packet) {
	static auto oFunc = funcPtr->GetFastcall<__int64, __int64*, const void*, __int64*, Packet**>();
	auto rq = moduleMgr.get<AutoRequeue>();
	auto gg = moduleMgr.get<AutoGG>();
	auto packetPtr = *packet;
	auto* pkt = reinterpret_cast<TextPacket*>(packetPtr);
	if (!pkt->Message.empty()) {
		if (rq->isEnabled() && pkt->Message.find("Game OVER!") != std::string::npos && pkt->Message.length() < 31) {
			CommandRequestPacket packet;
			packet.command = std::string("/q sky");
			g_Data.getClientInstance()->loopbackSender->sendToServer(&packet);
		}
	}
	return oFunc(_this, networkIdentifer, netEventCallback, packet);
}

__int64 LoopbackHook::PacketHandlerDispatcherInstanceHook::HandleSetTitlePacket::handle(__int64* _this, void* networkIdentifer, __int64* netEventCallback, Packet** packet) {
	static auto oFunc = funcPtr->GetFastcall<__int64, __int64*, const void*, __int64*, Packet**>();
	auto rq = moduleMgr.get<AutoRequeue>();
	auto gg = moduleMgr.get<AutoGG>();
	auto packetPtr = *packet;
	auto* pkt = reinterpret_cast<SetTitlePacket*>(packetPtr);
	if (!pkt->text.empty()) {
		if (rq->isEnabled() && pkt->text.find("You died!") != std::string::npos && pkt->text.length() < 20) {
			CommandRequestPacket packet;
			packet.command = std::string("/q sky");
			g_Data.getClientInstance()->loopbackSender->sendToServer(&packet);
		}
	}
	return oFunc(_this, networkIdentifer, netEventCallback, packet);
}