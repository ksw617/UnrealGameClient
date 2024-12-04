// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/PacketSession.h"
#include "NetworkRecv.h"
#include "NetworkSend.h"
#include "ServerPacketHandler.h"

PacketSession::PacketSession(FSocket* _Socket) : Socket(_Socket)
{
	//초기화
	ServerPacketHandler::Init();
	
}

PacketSession::~PacketSession()
{
	//연결끊기
	Disconnect();
}

void PacketSession::Run()
{
	RecvThread = MakeShared<NetworkRecv>(Socket, AsShared());
	SendThread = MakeShared<NetworkSend>(Socket, AsShared());
}


void PacketSession::HandleRecvPackets()
{
	while (true)
	{
		TArray<uint8> Packet; 
		if (!RecvPacketQueue.Dequeue(OUT Packet))
			break;

		TSharedPtr<PacketSession> MySession = AsShared();
		ServerPacketHandler::HandlePacket(MySession, Packet.GetData(), Packet.Num());
	}
}

void PacketSession::SendPacket(TSharedPtr<class SendBuffer> SendBuffer)
{
	SendPacketQueue.Enqueue(SendBuffer);
	
}


void PacketSession::Disconnect()
{
	if (RecvThread)
	{
		RecvThread->Destroy();
		RecvThread = nullptr;
	}

	if (SendThread)
	{
		SendThread->Destroy();
		SendThread = nullptr;
	}
}
