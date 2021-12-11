#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

class ServerTCPListenerInterFace
{
public:
	ServerTCPListenerInterFace(const char* ipAddressServer, int ServerPort) :
		s_ipAddressServer(ipAddressServer), s_ServerPort(ServerPort) {}
	int initializeListenerSocket();
	int runListenerSocket();

protected:
	virtual void onClientConnectiFromOnServer(int clientSocket);
	virtual void onClientDisconnectionFromServer(int clientSocket);
	virtual void onMSGReceived(int clientSocket, const char* msg, int length);
	void sendMSGToClient(int clientSocket, const char* msg, int length);
	void notificationToClientServer(int sendingClient, const char* msg, int length);

private:
	const char* s_ipAddressServer; // IP адрес сервера
	int s_ServerPort; // порт сервера
	int s_ServerSocket; // FD для прослушивания сокета
	fd_set s_ServerMain;
};