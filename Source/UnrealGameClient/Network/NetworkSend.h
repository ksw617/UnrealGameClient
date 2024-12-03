// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkHelper.h"

/**
 * 
 */
class UNREALGAMECLIENT_API NetworkSend : public NetworkHelper 
{
public:
	NetworkSend(FSocket* _Socket, TSharedPtr<PacketSession> _Session);
	~NetworkSend();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
public:
	void Destroy(); //스레드 중지 할 목적으로
private:

	bool SendPacket(TSharedPtr<class SendBuffer> SendBuffer);
	bool SendDesiredBytes(const uint8* Buffer, int32 Size);
};
