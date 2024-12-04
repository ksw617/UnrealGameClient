// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/ServerPacketHandler.h"

ServerPacketHandler::PacketFunc ServerPacketHandler::packetHandlers[UINT16_MAX];


void ServerPacketHandler::Init()
{
	for (int i = 0; i < UINT16_MAX; i++)
	{
		packetHandlers[i] = Handle_INVALID;
	}

	//Recv
	packetHandlers[S_LOGIN] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_Login>(Handle_S_LOGIN, session, buffer, len); };

	packetHandlers[S_REGISTER] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_Register>(Handle_S_REGISTER, session, buffer, len); 	};

	packetHandlers[S_ENTERGAME] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_EnterGame>(Handle_S_ENTERGAME, session, buffer, len); };

	packetHandlers[S_ENTERROOM] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_EnterRoom>(Handle_S_ENTERROOM, session, buffer, len); };

	packetHandlers[S_ENTERNEWBIE] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_EnterNewbie>(Handle_S_ENTERNEWBIE, session, buffer, len); };

	packetHandlers[S_CHAT] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_Chat>(Handle_S_CHAT, session, buffer, len); };
}

bool ServerPacketHandler::HandlePacket(TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
{

	PacketHeader* header = (PacketHeader*)buffer;
	return packetHandlers[header->Id](session, buffer, len);
}


bool Handle_INVALID(TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
{

	return false;
}

bool Handle_S_LOGIN(TSharedPtr<PacketSession>& session, Protocol::S_Login& packet)
{
	return false;
}

bool Handle_S_REGISTER(TSharedPtr<PacketSession>& session, Protocol::S_Register& packet)
{
	return false;
}

bool Handle_S_ENTERGAME(TSharedPtr<PacketSession>& session, Protocol::S_EnterGame& packet)
{
	return false;
}

bool Handle_S_ENTERROOM(TSharedPtr<PacketSession>& session, Protocol::S_EnterRoom& packet)
{
	return false;
}

bool Handle_S_ENTERNEWBIE(TSharedPtr<PacketSession>& session, Protocol::S_EnterNewbie& packet)
{
	return false;
}

bool Handle_S_CHAT(TSharedPtr<PacketSession>& session, Protocol::S_Chat& packet)
{
	return false;
}