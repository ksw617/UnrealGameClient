// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBuffer.h"



SendBuffer::SendBuffer(uint32 BufferSize)
{
	//���� ũ�� ����
	Buffer.SetNum(BufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* Data, uint32 Len)
{
	//������ ����
	memcpy(Buffer.GetData(), Data, Len);
	WriteSize = Len;
}

void SendBuffer::Close(uint32 UsedSize)
{
	//������ ����� ũ�� ������Ʈ
	WriteSize = UsedSize;
}
