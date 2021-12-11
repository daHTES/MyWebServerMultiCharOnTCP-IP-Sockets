#include "MultiClientListenerInterface.h"
#include <string.h>


void MultiClientChat::onClientConnectiFromOnServer(int clientSocket) 
{
	std::string welcomeMSGFromServer = "����� ���������� �� ������\\��� ��������!\n";
	sendMSGToClient(clientSocket, welcomeMSGFromServer.c_str(), welcomeMSGFromServer.size() + 1);

}
void MultiClientChat::onClientDisconnectionFromServer(int clientSocket) 
{
	
}
void MultiClientChat::onMSGReceived(int clientSocket, const char* msg, int length) 
{
	notificationToClientServer(clientSocket, msg, length);
}