#pragma once
#include "ServerTCPListenerInterface.h"
class WebServer : public ServerTCPListenerInterFace
{
public:
	WebServer(const char* ipAddress, int port) :
		ServerTCPListenerInterFace(ipAddress, port)
	{

	}
protected:
	virtual void onClientConnectiFromOnServer(int clientSocket, const char* msg, int length);
	virtual void onClientDisconnectionFromServer(int clientSocket);
	virtual void onMSGReceived(int clientSocket, const char* msg, int length);
}; 
