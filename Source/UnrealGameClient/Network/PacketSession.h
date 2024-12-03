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
	TSharedPtr<class RecvWorker> RecvWorkerThread;
public:
	PacketSession(class FSocket* Socket);
	~PacketSession();
public:
	void Run();
	void Disconnect();
};
