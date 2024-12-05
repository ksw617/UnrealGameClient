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
	C_ENTER_GAME = 1004,
	S_ENTER_GAME = 1005,
	S_SPAWN = 1006,
	S_DESPAWN = 1007,
	C_LOGOUT = 1008,
	C_MOVE = 1009,
	S_MOVE = 1010,
};

bool Handle_INVALID(TSharedPtr<PacketSession>& session, BYTE* buffer, int len);

bool Handle_S_LOGIN(TSharedPtr<PacketSession>& session, Protocol::S_LOGIN& packet);
bool Handle_S_ENTER_GAME(TSharedPtr<PacketSession>& session, Protocol::S_ENTER_GAME& packet);
bool Handle_S_SPAWN(TSharedPtr<PacketSession>& session, Protocol::S_SPAWN& packet);
bool Handle_S_DESPAWN(TSharedPtr<PacketSession>& session, Protocol::S_DESPAWN& packet);
bool Handle_S_MOVE(TSharedPtr<PacketSession>& session, Protocol::S_MOVE& packet);


class ServerPacketHandler : public PacketHandler
{		
protected:
	using PacketFunc = std::function<bool(TSharedPtr<PacketSession>&, BYTE*, int)>;
	static PacketFunc packetHandlers[UINT16_MAX];
public:
	static void Init();
	static bool HandlePacket(TSharedPtr<PacketSession>& session, BYTE* buffer, int len);
public:
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_LOGIN& packet) { return MakeSendBuffer(packet, C_LOGIN); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_ENTER_GAME& packet) { return MakeSendBuffer(packet, C_ENTER_GAME); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_LOGOUT& packet) { return MakeSendBuffer(packet, C_LOGOUT); }
	static TSharedPtr<SendBuffer> MakeSendBuffer(Protocol::C_MOVE& packet) { return MakeSendBuffer(packet, C_MOVE); }

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
