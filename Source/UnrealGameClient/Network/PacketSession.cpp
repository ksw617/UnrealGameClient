// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/PacketSession.h"
#include "NetworkRecv.h"
#include "NetworkSend.h"

PacketSession::PacketSession(FSocket* _Socket) : Socket(_Socket)
{
}

PacketSession::~PacketSession()
{
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

		//Todo
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
