#include "main.h"









bool gshutdown = false;
int main()
{
	timeBeginPeriod(1);
	networkInit();

	while (!gshutdown)
	{
		
		//network
		netIOProcess();







		AcceptProc();
		DequeProc();



		Update();
		
		DeleteProc();
		
	}

	return 0;
}














