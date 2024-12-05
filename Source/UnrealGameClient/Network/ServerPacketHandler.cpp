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
		{  return HandlePacket<Protocol::S_LOGIN>(Handle_S_LOGIN, session, buffer, len); };

	packetHandlers[S_ENTER_GAME] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_ENTER_GAME>(Handle_S_ENTER_GAME, session, buffer, len); 	};

	packetHandlers[S_SPAWN] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_SPAWN>(Handle_S_SPAWN, session, buffer, len); };

	packetHandlers[S_DESPAWN] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_DESPAWN>(Handle_S_DESPAWN, session, buffer, len); };

	packetHandlers[S_MOVE] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::S_MOVE>(Handle_S_MOVE, session, buffer, len); };
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

bool Handle_S_LOGIN(TSharedPtr<PacketSession>& session, Protocol::S_LOGIN& packet)
{


	if (packet.success())
	{
		
		Protocol::C_ENTER_GAME sendPacket;
		sendPacket.set_playerid(1);

		TSharedPtr<SendBuffer> SendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
		session->SendPacket(SendBuffer);
	}

	return true;
}

bool Handle_S_ENTER_GAME(TSharedPtr<PacketSession>& session, Protocol::S_ENTER_GAME& packet)
{
	return false;
}

bool Handle_S_SPAWN(TSharedPtr<PacketSession>& session, Protocol::S_SPAWN& packet)
{
	return false;
}

bool Handle_S_DESPAWN(TSharedPtr<PacketSession>& session, Protocol::S_DESPAWN& packet)
{
	return false;
}

bool Handle_S_MOVE(TSharedPtr<PacketSession>& session, Protocol::S_MOVE& packet)
{
	return false;
}
