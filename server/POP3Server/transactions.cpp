#include "transactions.h"




TransactionalRequest::TransactionalRequest()
{
}

TransactionalRequest::TransactionalRequest(SOCKET cliSock,std::string username, std::string request) {

	m_sender = username;
	m_msg.setUser(username);

	std::istringstream iss(request);
	std::string command;

	m_cliSock = cliSock;

	// Assuming the command is a string followed by an integer
	iss >> command;


	iss >> m_target_id;


	if (command == "STAT") {
		// Handle STAT command
		m_currentType = STAT;
	}
	else if (command == "LIST") {
		// Handle LIST command
		m_currentType = LIST;
	}
	else if (command == "RETR") {
		// Handle RETR command
		m_currentType = RETR;
	}
	else if (command == "DELE") {
		// Handle DELE command
		m_currentType = DELE;
	}
	else if (command == "QUIT") {
		// Handle QUIT command
		m_currentType = QUIT;
	}
	else  {
		// Handle unsupported command
		m_currentType = unsupported;
	}

}


TransactionalRequest::~TransactionalRequest() {
}


void TransactionalRequest::Srv_TRANSACTION_MSG_STAT()
{
	m_msg.StatResponse(m_cliSock);

}

void TransactionalRequest::Srv_TRANSACTION_MSG_LIST()
{
	m_msg.ListResponse(m_cliSock);
}

void TransactionalRequest::Srv_TRANSACTION_MSG_RETR()
{
	m_msg.RetrResponse(m_cliSock, m_target_id);
}

void TransactionalRequest::Srv_TRANSACTION_MSG_DELE()
{
	m_msg.DeleResponse(m_cliSock, m_target_id);
}



void TransactionalRequest::respondToTransaction()
{

	switch (m_currentType) {
	case STAT:
		Srv_TRANSACTION_MSG_STAT();
		break;
	case LIST:
		Srv_TRANSACTION_MSG_LIST();
		break;
	case RETR:
		Srv_TRANSACTION_MSG_RETR();
		break;
	case DELE:
		Srv_TRANSACTION_MSG_DELE();
		break;
	default:
		printf("default case");
	};
	

}






