// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkHelper.h"

NetworkHelper::NetworkHelper()
{
	//Network Thrad��� �̸����� �� ��ü�� ������ �� ������ ����
	Thread = FRunnableThread::Create(this, TEXT("Network Thread"));
}

NetworkHelper::~NetworkHelper()
{
}

bool NetworkHelper::Init()
{
	//�ʱ�ȭ �Ǿ��ٰ� �޼����� ȭ�鿡 ���
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Network Thread Init")));
	return true;
}

uint32 NetworkHelper::Run()
{
	while (Running) // Running�� true�� ���� �ݺ� ����
	{
		//Todo ���� ����

	}
	return 0;// ������ ����� ��ȯ ��
}

void NetworkHelper::Exit()
{
	//todo
}
