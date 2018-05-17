#include "stdafx.h"
#include "CServer.h"
#include "conio.h"
#include "iostream"
int main()
{
	CServer server;
	std::cout << "server start..." << std::endl;
	server.Run();

	_getch();
}