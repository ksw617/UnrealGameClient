// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkRecv.h"
#include "Sockets.h"
#include "Serialization/ArrayWriter.h"
#include "PacketSession.h"

NetworkRecv::NetworkRecv(FSocket* _Socket, TSharedPtr<class PacketSession> _Session)
{	  
	//Recv Thread 이름으로 이 객체를 실행할 새 스레드 생성
	Thread = FRunnableThread::Create(this, TEXT("Recv Thread"));
	Socket = _Socket;
	Session = _Session;
}

NetworkRecv::~NetworkRecv()
{
}

bool NetworkRecv::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Recv Thread Init")));
	return true; 
}

uint32 NetworkRecv::Run()
{
	while (Running)	
	{
		TArray<uint8> Packet;
		if (RecvPacket(OUT Packet))
		{
			//Session을 안전하게 들고 옴
			//S 가 Null이라면 Session은 더이상 유효하지 않음
			if (TSharedPtr<PacketSession> S = Session.Pin())
			{
				//Session 수신 패킷 큐에 수신된 패킷 추가
				S->RecvPacketQueue.Dequeue(Packet);

			}
		}

		
	}

	return 0;
}

void NetworkRecv::Exit()
{
}

bool NetworkRecv::RecvPacket(TArray<uint8>& OutPacket)
{

	const int32 HeaderSize = sizeof(FPacketHeader);
	TArray<uint8> HeaderBuffer;
	HeaderBuffer.AddZeroed(HeaderSize);

	if (!RecvDesiredBytes(HeaderBuffer.GetData(), HeaderSize))
		return false;

	FPacketHeader Header;
	{
		FMemoryReader Reader(HeaderBuffer);
		Reader << Header;

		UE_LOG(LogTemp, Log, TEXT("Recv PacketID : %d, PacketSize : %d"), Header.PacketID, Header.PacketSize);
	}

	OutPacket = HeaderBuffer;

	TArray<uint8> PayloadBuffer;
	const int32 payloadSize = Header.PacketSize - HeaderSize;
	if (payloadSize == 0)
		return true;

	OutPacket.AddZeroed(payloadSize);
	
	return RecvDesiredBytes(&OutPacket[HeaderSize], payloadSize);
}


bool NetworkRecv::RecvDesiredBytes(uint8* REsults, int32 Size)
{
	uint32 PendingDataSize;

	if (Socket->HasPendingData(PendingDataSize) == false || PendingDataSize <= 0)
		return false;

	int32 offset = 0;

	while (Size > 0)  
	{
		int32 NumRead = 0;
		Socket->Recv(REsults + offset, Size, OUT NumRead);

		check(NumRead <= Size);

		if (NumRead <= 0)
			return false;

		offset += NumRead;					 
											

		Size -= NumRead;

	}


	return true;
	
}
