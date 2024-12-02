// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"

//���� ����
void UNetworkGameInstance::ConnectToServer()
{
	//TCP ��Ʈ�� "Client Socket" �̸����� ���� ����
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	//���ڿ��� �� IP �ּҸ� �Ľ��Ͽ� FIPv4Address ��ü�� ��ȯ
	FIPv4Address Ip;
	FIPv4Address::Parse(IpAddress, Ip);

	//���ͳ� �ּ� ���� �� ����
	TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	InternetAddr->SetIp(Ip.Value);	// IP �ּ� ����
	InternetAddr->SetPort(Port);	// ��Ʈ ��ȣ ����

	//ȭ�鿡 ���� ���� �õ� �޼��� ���
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect to Server")));

	//������ ���� �õ�
	bool Connected = Socket->Connect(*InternetAddr);

	if (Connected)
	{
		//ȭ�鿡 ���� ���� ���� �޼��� ���
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Connection Success")));

	}
	else
	{  	//ȭ�鿡 ���� ���� ���� �޼��� ���
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Failed")));

	}
}

void UNetworkGameInstance::DisconnectServer()
{
	//���࿡ ���Ͽ� ���� �ִٸ�
	if (Socket)
	{
		//���� ���� �ý����� ���� ������ ������ �ı��ϰ� ���� ����
		ISocketSubsystem::Get()->DestroySocket(Socket);
		Socket = nullptr; //���� �����͸� null�� �����Ͽ� �� �̻� ��� ����

	}
}
