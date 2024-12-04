// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"
#include "Network/PacketSession.h"  // Ãß°¡


void UNetworkGameInstance::ConnectToServer()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	FIPv4Address Ip;
	FIPv4Address::Parse(IpAddress, Ip);


	TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	InternetAddr->SetIp(Ip.Value);	
	InternetAddr->SetPort(Port);	

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect to Server")));

	bool Connected = Socket->Connect(*InternetAddr);

	if (Connected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Connection Success")));

		ServerSession = MakeShared<PacketSession>(Socket);

		ServerSession->Run();

	}
	else
	{  	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Failed")));

	}
}

void UNetworkGameInstance::DisconnectServer()
{
	if (Socket)
	{
		ISocketSubsystem::Get()->DestroySocket(Socket);
		Socket = nullptr; 

	}
}

void UNetworkGameInstance::HandleRecvPackets()
{

	if (Socket == nullptr || ServerSession == nullptr)
		return;

	ServerSession->HandleRecvPackets();
}

void UNetworkGameInstance::SendPacket(TSharedPtr<class SendBuffer> SendBuffer)
{
	if (Socket == nullptr || ServerSession == nullptr)
		return;

	ServerSession->SendPacket(SendBuffer);
}
