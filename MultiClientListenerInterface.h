#pragma once
#include "ServerTCPListenerInterface.h"
class MultiClientChat: public ServerTCPListenerInterFace
{
public:
	MultiClientChat(const char* ipAddress, int port) :
		ServerTCPListenerInterFace(ipAddress, port) 
	{

	}
protected:
	virtual void onClientConnectiFromOnServer(int clientSocket);
	virtual void onClientDisconnectionFromServer(int clientSocket);
	virtual void onMSGReceived(int clientSocket, const char* msg, int length);
};