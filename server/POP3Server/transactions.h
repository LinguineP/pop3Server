#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "msgModule.h"


class TransactionalRequest {
public:

	enum transctionalRequestType { STAT, LIST, RETR, DELE, QUIT, unsupported };
private:
	
	std::string m_sender;
	int m_target_id;

	transctionalRequestType m_currentType;
	MesssageSender m_msg;
	SOCKET m_cliSock;


	void Srv_TRANSACTION_MSG_STAT();
	void Srv_TRANSACTION_MSG_LIST();
	void Srv_TRANSACTION_MSG_RETR();
	void Srv_TRANSACTION_MSG_DELE();


public:
	
	TransactionalRequest();
	TransactionalRequest(SOCKET cliSock,std::string username,std::string request);
	~TransactionalRequest();

	transctionalRequestType getRequestType() {
		return m_currentType;
	}


	void respondToTransaction();



};