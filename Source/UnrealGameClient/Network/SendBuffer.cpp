// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBuffer.h"



SendBuffer::SendBuffer(uint32 BufferSize)
{
	//버퍼 크기 설정
	Buffer.SetNum(BufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* Data, uint32 Len)
{
	//데이터 복사
	memcpy(Buffer.GetData(), Data, Len);
	WriteSize = Len;
}

void SendBuffer::Close(uint32 UsedSize)
{
	//실제로 사용한 크기 업데이트
	WriteSize = UsedSize;
}
