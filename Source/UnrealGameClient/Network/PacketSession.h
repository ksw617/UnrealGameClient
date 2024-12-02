// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALGAMECLIENT_API PacketSession
{
public:
	class Fsocket* Socket;
public:
	PacketSession();
	~PacketSession();
public:
	void Run();
	void Disconnect();
};
