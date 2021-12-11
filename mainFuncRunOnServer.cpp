#include "MultiClientListenerInterface.h"

//using namespace std;

void main() 
{
	setlocale(LC_ALL, "Russian");	
	MultiClientChat temp("0.0.0.0", 30000);
	if (temp.initializeListenerSocket() != 0) 
	{
		return;
	}
	temp.runListenerSocket();

	system("pause");

}