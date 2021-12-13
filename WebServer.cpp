#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include "WebServerInterface.h"
void WebServer::onClientConnectiFromOnServer(int clientSocket, const char* msg, int length)
{

}

void WebServer::onClientDisconnectionFromServer(int clientSocket) 
{

}

void WebServer::onMSGReceived(int clientSocket, const char* msg, int length)
{
	std::istringstream iss(msg);
	std::vector<std::string> parsedMSG((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
	
	std::string contentMSG = "<h2>404 Not Found</h2>";
	std::string documentHTML = "/index.html";


	if (parsedMSG.size() >= 3 && parsedMSG[0] == "GET")
	{
		documentHTML = parsedMSG[1];
		if (documentHTML == "/") 
		{
			documentHTML = "/index.html";
		}
	}

	std::ifstream fStream(".\\mysitenet" + documentHTML);
	if (fStream.good())
	{
			std::string str((std::istreambuf_iterator<char>(fStream)), std::istreambuf_iterator<char>());
			contentMSG = str;
	}
	fStream.close();



	std::ostringstream oss;
	oss << "HTTP/1.1 200 OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << contentMSG.size() << " \r\n";
	oss << "\r\n";
	oss << contentMSG;

	std::string outPut = oss.str();
	int size = outPut.size() + 1;


	sendMSGToClient(clientSocket, outPut.c_str(), size);
}
