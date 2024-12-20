// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkHelper.h"

/**
 * 
 */
class UNREALGAMECLIENT_API NetworkRecv : public NetworkHelper
{
public:
	NetworkRecv(FSocket* _Socket, TSharedPtr<class PacketSession> _Session);
	~NetworkRecv();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
public:
	void Destroy(); //스레드 중지 할 목적으로
private:

	bool RecvPacket(TArray<uint8>& OutPacket);
	bool RecvDesiredBytes(uint8* REsults, int32 size);

};
