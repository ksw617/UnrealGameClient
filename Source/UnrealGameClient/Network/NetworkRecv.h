// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkHelper.h"

/**
 * 
 */
class UNREALGAMECLIENT_API NetworkRecv : public NetworkHelper
{
public:
	//생성자 호출될때 PacketSession 주소 넣어줌
	NetworkRecv(FSocket* _Socket, TSharedPtr<class PacketSession> _Session);
	~NetworkRecv();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
private:

	bool RecvPacket(TArray<uint8>& OutPacket);
	bool RecvDesiredBytes(uint8* REsults, int32 size);

};
