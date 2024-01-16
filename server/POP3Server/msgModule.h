#pragma once


#include <windows.h>



class MesssageSender {


public:

	MesssageSender();
	~MesssageSender();
	void sendPOP3SrvReady(SOCKET clientSocket);



};