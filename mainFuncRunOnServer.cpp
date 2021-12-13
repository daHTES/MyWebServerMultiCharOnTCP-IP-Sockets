#include "WebServerInterface.h"



void main() 
{
	setlocale(LC_ALL, "Russian");	
	WebServer objWebServer("0.0.0.0", 8080);
	if (objWebServer.initializeListenerSocket() != 0)
	{
		return; 
	}
	objWebServer.runListenerSocket();

	system("pause");

}