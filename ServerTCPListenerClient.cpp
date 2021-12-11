#include "ServerTCPListenerInterface.h"

int ServerTCPListenerInterFace::initializeListenerSocket() 
{
	WSADATA serverWSData;
	WORD versionData = MAKEWORD(2, 2);
	int serverDataStartUp = WSAStartup(versionData, &serverWSData);
	// ѕровер€ем чек валид на инициализацию
	if (serverDataStartUp != 0)
	{
		return serverDataStartUp;
	}
	// —оздаем наш сокет 
	s_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	// ѕровер€ем чек валид на создание сокета
	if (s_ServerSocket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}
	sockaddr_in objOfAddres;
	objOfAddres.sin_family = AF_INET;
	objOfAddres.sin_port = htons(s_ServerPort);
	inet_pton(AF_INET, s_ipAddressServer, &objOfAddres.sin_addr);


	if (bind(s_ServerSocket, (sockaddr*)&objOfAddres, sizeof(objOfAddres)) == SOCKET_ERROR) 
	{
		return WSAGetLastError();
	}
	if (listen(s_ServerSocket, SOMAXCONN) == SOCKET_ERROR) 
	{
		return WSAGetLastError();
	}

	FD_ZERO(&s_ServerMain);
	FD_SET(s_ServerSocket, &s_ServerMain);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
int ServerTCPListenerInterFace::runListenerSocket() 
{
	bool runningServer = true;
	while (runningServer)
	{
		fd_set copyMain = s_ServerMain;
		// переменна€ дл€ хранени€ и просмотра тех, кто к нам подключилс€
		int countOfConnectionsSocker = select(0, &copyMain, nullptr, nullptr, nullptr);
		// перебираем все их в цикле
		for (int i = 0; i < countOfConnectionsSocker; i++)
		{
			SOCKET newSock = copyMain.fd_array[i];
			if (newSock == s_ServerSocket)
			{
				SOCKET newClientConnection = accept(s_ServerSocket, nullptr, nullptr);
				FD_SET(newClientConnection, &s_ServerMain);
				onClientConnectiFromOnServer(newClientConnection);
			}
			else
			{
				char buffer[6096];
				ZeroMemory(buffer, 6096);

				int byteIn = recv(newSock, buffer, 6000, 0);
				if (byteIn <= 0)
				{
					// убираем клиента из очереди
					onClientDisconnectionFromServer(newSock);
					closesocket(newSock);
					FD_CLR(newSock, &s_ServerMain);
				}
				else
				{
					onMSGReceived(newSock, buffer, byteIn);
					//if (buffer[0] == '\\') // команда на закрываение сервера
					{
						/*string commandLine = string(buffer, byteIn);
						if (commandLine == "\\quit") // если команда выхода
						{
							runningServer = false;
							break;
						}
						*/					}
					/*for (int i = 0; i < s_ServerMain.fd_count; i++)
					{
						SOCKET outSocket = s_ServerMain.fd_array[i];
						if (outSocket != s_ServerSocket && outSocket != newSock)
						{
							ostringstream newIOSServer;
							newIOSServer << "SOCKET #" << newSock << ": " << buffer << "\r\n";
							string outMSG = newIOSServer.str();

							send(outSocket, outMSG.c_str(), outMSG.size() + 1, 0);
							
						}
					}
			*/
			}
			}
		}

	}
	// удал€ем сокет из набора дескрипторов и закр≥ваем порт прослушки 
	FD_CLR(s_ServerSocket, &s_ServerMain);
	closesocket(s_ServerSocket);

	// —мс дл€ клиентов о закрытие сервера 
	//string goodByeMSG = "—ервер ложитьс€ спать!\n";
	while (s_ServerMain.fd_count > 0)
	{
		SOCKET sockNew = s_ServerMain.fd_array[0]; // получаем нмоера сокета
		//send(sockNew, goodByeMSG.c_str(), goodByeMSG.size() + 1, 0);
		FD_CLR(sockNew, &s_ServerMain);
		closesocket(sockNew);
	}
	WSACleanup();
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////
void ServerTCPListenerInterFace::sendMSGToClient(int clientSocket, const char* msg, int length) 
{
	send(clientSocket, msg, length, 0);
}
/////////////////////////////////////////////////////////////////////////////////
void ServerTCPListenerInterFace::notificationToClientServer(int sendingClient, const char* msg, int length) 
{
	for (int i = 0; i < s_ServerMain.fd_count; i++)
	{
		SOCKET outSocket = s_ServerMain.fd_array[i];
		if (outSocket != s_ServerSocket && outSocket != sendingClient)
		{
			sendMSGToClient(outSocket, msg, length);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////
void ServerTCPListenerInterFace::onClientConnectiFromOnServer(int clientSocket)
{

}
/////////////////////////////////////////////////////////////////////////////////
void ServerTCPListenerInterFace::onClientDisconnectionFromServer(int clientSocket)
{

}
/////////////////////////////////////////////////////////////////////////////////
void ServerTCPListenerInterFace::onMSGReceived(int clientSocket, const char* msg, int length)
{

}