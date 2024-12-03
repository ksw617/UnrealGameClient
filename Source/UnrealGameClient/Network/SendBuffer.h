// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

struct PacketHeader
{
	uint16 Size; //Å©±â
	uint16 Id;   //id

};

class UNREALGAMECLIENT_API SendBuffer
{
public:
	TArray<BYTE> Buffer;
	uint32 WriteSize = 0;
public:
	SendBuffer(uint32 BufferSize);
	~SendBuffer();
public:
	BYTE* GetBuffer() { return Buffer.GetData(); }
	int32 GetWriteSize() const { return WriteSize; }
	int32 Capacity() const { return static_cast<uint32>(Buffer.Num()); }
public:
	void CopyData(void* Data, uint32 Len);
	void Close(uint32 UsedSize);
};
