#pragma once


#include <windows.h>
#include <vector>
#include <chrono>
#include <string>
#include <iostream>

#include "dbAdapter.h";


extern dbAdapter dbHelper;

class MesssageSender {
	std::string m_user;

public:

	MesssageSender();
	~MesssageSender();

	void setUser(std::string usr);

	void sendPOP3SrvReady(SOCKET clientSocket);
	void sendMaildropReady(SOCKET clientSocket);
	void StatResponse(SOCKET clientSocket);
	void ListResponse(SOCKET clientSocket);
	void RetrResponse(SOCKET clientSocket, int target);
	void DeleResponse(SOCKET clientSocket, int target);
	void ErrUnsuported(SOCKET clientSocket);
	void QuitResponse(SOCKET clientSocket);

	//generics

	std::string receiveMessage(SOCKET clientSocket);
	void sendMessage(std::string& data, SOCKET clientSocket);

	

};