// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SendBuffer.h"
#include "PacketSession.h"
#include "Protocol/Protocol.pb.h"
/**
 * 
 */
enum : uint16
{
	C_LOGIN = 1000,
	S_LOGIN = 1001,
	C_REGISTER = 1002,
	S_REGISTER = 1003,
	C_ENTERGAME = 1004,
	S_ENTERGAME = 1005,
	C_ENTERROOM = 1006,
	S_ENTERROOM = 1007,
	S_ENTERNEWBIE = 1008,
	C_CHAT = 1009,
	S_CHAT = 1010,
};

bool Handle_INVALID(TSharedPtr<PacketSession>& session, BYTE* buffer, int len);

bool Handle_S_LOGIN(TSharedPtr<PacketSession>& session, Protocol::S_Login& packet);
bool Handle_S_REGISTER(TSharedPtr<PacketSession>& session, Protocol::S_Register& packet);
bool Handle_S_ENTERGAME(TSharedPtr<PacketSession>& session, Protocol::S_EnterGame& packet);
bool Handle_S_ENTERROOM(TSharedPtr<PacketSession>& session, Protocol::S_EnterRoom& packet);
bool Handle_S_ENTERNEWBIE(TSharedPtr<PacketSession>& session, Protocol::S_EnterNewbie& packet);
bool Handle_S_CHAT(TSharedPtr<PacketSession>& session, Protocol::S_Chat& packet);


class ServerPacketHandler : public PacketHandler
{		
protected:
	using PacketFunc = std::function<bool(TSharedPtr<PacketSession>&, BYTE*, int)>;
	static PacketFunc packetHandlers[UINT16_MAX];
public:
	static void Init();
	static bool HandlePacket(TSharedPtr<PacketSession>& session, BYTE* buffer, int len);
public:
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_Login& packet) { return MakeSendBuffer(packet, C_LOGIN); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_Register& packet) { return MakeSendBuffer(packet, C_REGISTER); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_EnterGame& packet) { return MakeSendBuffer(packet, C_ENTERGAME); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_EnterRoom& packet) { return MakeSendBuffer(packet, C_ENTERROOM); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_Chat& packet) { return MakeSendBuffer(packet, C_CHAT); }

protected:
    template<typename PacketType, typename ProcessFunc>
    static bool HandlePacket(ProcessFunc func, TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
    {
        PacketType packet;
        packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

        return func(session, packet);
    }
protected:
    template<typename T>
    static TSharedPtr<SendBuffer> MakeSendBuffer(T& packet, uint16 id)
    {
        uint16 dataSize = static_cast<uint16>(packet.ByteSizeLong());
        uint16 packetSize = dataSize + sizeof(PacketHeader);   //dataSize + 4byte

        TSharedPtr<SendBuffer> sendBuffer = MakeShared<SendBuffer>(packetSize);
        PacketHeader* buffer = reinterpret_cast<PacketHeader*>(sendBuffer->GetBuffer());
        buffer->Size = packetSize;
        buffer->Id = id;  // 1

		packet.SerializeToArray(&buffer[1], dataSize);
		sendBuffer->Close(packetSize);


        return sendBuffer;
    }

};
