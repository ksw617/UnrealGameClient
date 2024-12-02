// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkHelper.h"

/**
 * 
 */
class UNREALGAMECLIENT_API NetworkRecv : public NetworkHelper
{
public:
	NetworkRecv(FSocket* socket);
	~NetworkRecv();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
private:
	//������ ũ���� ������ ����, ���ŵ� �����ʹ� Result�� ����
	bool RecvDesiredBytes(uint8* REsults, int32 size);

};
