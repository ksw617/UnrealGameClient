// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkHelper.h"

NetworkHelper::NetworkHelper()
{
	//Network Thrad라는 이름으로 이 객체를 실행할 새 스레드 생성
	Thread = FRunnableThread::Create(this, TEXT("Network Thread"));
}

NetworkHelper::~NetworkHelper()
{
}

bool NetworkHelper::Init()
{
	//초기화 되었다고 메세지를 화면에 출력
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Network Thread Init")));
	return true;
}

uint32 NetworkHelper::Run()
{
	while (Running) // Running이 true인 동안 반복 실행
	{
		//Todo 로직 구현

	}
	return 0;// 스레드 종료시 반환 값
}

void NetworkHelper::Exit()
{
	//todo
}
