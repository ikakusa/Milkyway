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

	auto rq = moduleMgr.get<AutoRequeue>();
	auto gg = moduleMgr.get<AutoGG>();
	writelog("%s", "aaa");
	return oFunc(packetHandlerDispatcher, networkIdentifier, netEventCallback, packet);

	auto* pkt = reinterpret_cast<TextPacket*>(packetPtr.get());
	if (rq->isEnabled() && pkt->Message == "§c§l» §r§c§lGame OVER!") {
		CommandRequestPacket packet;
		packet.command = "/q sky";
		g_Data.getClientInstance()->loopbackSender->sendToServer(&packet);
	}
	if (gg->isEnabled() && pkt->Message == "§c§l» §r§c§lGame OVER!") {
		TextPacket tp;
		tp.Message = "GG";
		tp.Type = TextPacketType::Chat;
		g_Data.getClientInstance()->loopbackSender->sendToServer(&tp);
	}
	return oFunc(packetHandlerDispatcher, networkIdentifier, netEventCallback, packet);
}