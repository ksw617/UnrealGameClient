// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkSend.h"
#include "SendBuffer.h"
#include "PacketSession.h"
#include "Sockets.h"

NetworkSend::NetworkSend(FSocket* _Socket, TSharedPtr<PacketSession> _Session)
{
    Socket = _Socket;
    Session = _Session;
    Thread = FRunnableThread::Create(this, TEXT("Send Thread"));

}

NetworkSend::~NetworkSend()
{
}

bool NetworkSend::Init()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Send Thread Init")));
    return true;
}

uint32 NetworkSend::Run()
{
    while (Running)
    {
        TSharedPtr<SendBuffer> SendBuffer;

        if (TSharedPtr<PacketSession> S = Session.Pin())
        {
            if (S->SendPacketQueue.Dequeue(OUT SendBuffer))
            {
                SendPacket(SendBuffer);
            }

        }

    }
    
    return 0;
}

void NetworkSend::Exit()
{
}

void NetworkSend::Destroy()
{
    Running = false;
}

bool NetworkSend::SendPacket(TSharedPtr<class SendBuffer> SendBuffer)
{
    if (SendDesiredBytes(SendBuffer->GetBuffer(), SendBuffer->GetWriteSize()) == false)
        return false;

    return true;
    
}

bool NetworkSend::SendDesiredBytes(const uint8* Buffer, int32 Size)
{
    while (Size > 0)
    {
        int32 BytesSend = 0;
        if (Socket->Send(Buffer, Size, BytesSend) == false)
            return false;

        Size -= BytesSend;
        Buffer += BytesSend;

    }
 
    return true;
}
