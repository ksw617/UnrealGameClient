// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALGAMECLIENT_API PacketSession  : public TSharedFromThis<PacketSession>
{
public:
	FSocket* Socket;
	TQueue<TArray<uint8>> RecvPacketQueue;
	TQueue<TSharedPtr<class SendBuffer>> SendPacketQueue;
	TSharedPtr<class NetworkRecv> RecvThread;
	TSharedPtr<class NetworkSend> SendThread;
public:
	PacketSession(class FSocket* Socket);
	~PacketSession();
public:
	void Run();
	void Disconnect();
public:
	UFUNCTION(BlueprintCallable)
	void HandleRecvPackets();
	void SendPacket(TSharedPtr<class SendBuffer> SendBuffer);

};
