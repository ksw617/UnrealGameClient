// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


//네트워크 통신에서 필요한 패킷 헤더를 정의 하는 구조체
struct UNREALGAMECLIENT_API FPacketHeader
{
	uint16 PacketSize;	// 패킷의 크기
	uint16 PacketID;	// 패킷의 고유 식별자

	//Default 생성자는 패킷 크기와 id가 0으로 초기화
	FPacketHeader() : PacketSize(0), PacketID(0) {}

	//생성자 호출될때 매개변수값을 크기와 id에 초기화
	FPacketHeader(uint16 Size, uint16 ID) : PacketSize(Size), PacketID(ID) {}

	//패킷 헤더를 쉽게 직렬하기 위해 << 연산자 오버로드
	friend FArchive& operator<<(FArchive& Archive, FPacketHeader& Header)
	{
		Archive << Header.PacketSize;
		Archive << Header.PacketID;
		return Archive;
	}
};


class UNREALGAMECLIENT_API NetworkHelper : public FRunnable
{
protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	class FSocket* Socket = nullptr;
	TWeakPtr<class PacketSession> Session;

};
