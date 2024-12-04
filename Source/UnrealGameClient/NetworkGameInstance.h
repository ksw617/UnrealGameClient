// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetworkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAMECLIENT_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	class FSocket* Socket = nullptr;
	FString IpAddress = TEXT("127.0.0.1");
	int16 Port = 27015;
	TSharedPtr<class PacketSession> ServerSession;
public:
	UFUNCTION(BlueprintCallable)
	void ConnectToServer();
	UFUNCTION(BlueprintCallable)
	void DisconnectServer();
	UFUNCTION(BlueprintCallable)
	void HandleRecvPackets();

	void SendPacket(TSharedPtr<class SendBuffer> SendBuffer);

};
