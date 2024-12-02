// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALGAMECLIENT_API NetworkHelper : public FRunnable
{
protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;

	//����
	FSocket* Socket;
	//Packet Sesssion�� weak_ptr�� ��� �ֱ�
	TWeakPtr<class PacketSession> Session;

public:
	NetworkHelper();
	~NetworkHelper();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
};
