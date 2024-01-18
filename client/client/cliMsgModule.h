#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "vigenere.h"

class msgHandler {

	std::string StrFromNetwork(SOCKET cliSock);

	

public: 
	void USERmsg(SOCKET cliSock,std::string username,std::string password);

	void QUITmsg(SOCKET cliSock);

	void recvOneliner(SOCKET cliSock);

	void recvTransmision(SOCKET cliSock,int expected);

	void STATmsg(SOCKET cliSock);

	void LISTmsg(SOCKET cliSock);


	void RETRmsg(SOCKET cliSock,int msgId);

	void DELEmsg(SOCKET cliSock, int msgId);

};