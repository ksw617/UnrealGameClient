// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkRecv.h"

NetworkRecv::NetworkRecv()
{
}

NetworkRecv::NetworkRecv(FSocket* socket)
{
}

NetworkRecv::~NetworkRecv()
{
}

bool NetworkRecv::Init()
{
	return false;
}

uint32 NetworkRecv::Run()
{
	return uint32();
}

void NetworkRecv::Exit()
{
}

bool NetworkRecv::RecvDesiredBytes(uint8* REsults, int32 size)
{
	return false;
}
