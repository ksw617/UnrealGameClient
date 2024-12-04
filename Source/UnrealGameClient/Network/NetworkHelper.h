// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


//��Ʈ��ũ ��ſ��� �ʿ��� ��Ŷ ����� ���� �ϴ� ����ü
struct UNREALGAMECLIENT_API FPacketHeader
{
	uint16 PacketSize;	// ��Ŷ�� ũ��
	uint16 PacketID;	// ��Ŷ�� ���� �ĺ���

	//Default �����ڴ� ��Ŷ ũ��� id�� 0���� �ʱ�ȭ
	FPacketHeader() : PacketSize(0), PacketID(0) {}

	//������ ȣ��ɶ� �Ű��������� ũ��� id�� �ʱ�ȭ
	FPacketHeader(uint16 Size, uint16 ID) : PacketSize(Size), PacketID(ID) {}

	//��Ŷ ����� ���� �����ϱ� ���� << ������ �����ε�
	friend FArchive& operator<<(FArchive& Archive, FPacketHeader& Header)
	{
		Archive << Header.PacketSize;
		Archive << Header.PacketID;
		return Archive;
	}
};


class UNREALGAMECLIENT_API NetworkHelper : public FRunnable
{
protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	class FSocket* Socket = nullptr;
	TWeakPtr<class PacketSession> Session;

};
