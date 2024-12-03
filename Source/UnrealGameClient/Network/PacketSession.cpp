// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/PacketSession.h"
#include "NetworkRecv.h"

PacketSession::PacketSession(FSocket* _Socket) : Socket(_Socket)
{
}

PacketSession::~PacketSession()
{
}

void PacketSession::Run()
{
	//≥ª≤® ¡÷º“ ≥—∞‹¡‹
	RecvWorkerThread = MakeShared<RecvWorker>(Socket, AsShared());
}

void PacketSession::Disconnect()
{
}
