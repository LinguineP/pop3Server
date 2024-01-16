#pragma once



#include "userModel.h"

#include "msgModule.h"




#pragma comment(lib, "Ws2_32.lib")

class SrvAuto {
	
	

	//session info
	int currentUsrId;
	User currentUser;
	MesssageSender msg;
	
	
	// FSM States
	enum	SrvStates {	Srv_IDLE, 
						Srv_AUTHORIZATION, 
						Srv_TRANSACTION,
						Srv_DISCONECTING};

	//Srv_Idle
	void	Srv_Idle_Cl_Connection_Request();
	//Srv_AUTHORISATION
	void	Srv_AUTHORISATION_HANDLE_MSG();
	bool	Srv_AUTHORISATION_User_Pass_Check();
	bool	Srv_AUTHORISATION_User_allowed_check();
	void	Srv_AUTHORISATION_Response();
	//Srv_Transaction
	void	Srv_TRANSACTION_HANDLE_MSG();
	void	Srv_TRANSACTION_MSG_STAT();
	void	Srv_TRANSACTION_MSG_LIST();
	void	Srv_TRANSACTION_MSG_RETR();
	void	Srv_TRANSACTION_MSG_DELE();
	void	Srv_TRANSACTION_MSG_QUIT();
	//SRV_Disconecting
	void Srv_DISCONECTING_Procedure();



	

		
public:
	SrvAuto();
	~SrvAuto();
	
	static bool connectedFlag;
	static bool breakFlag;
	


	void Initialize();

protected:
	
	
	SOCKET m_Socket;
	SOCKET m_cliSocket;
	HANDLE m_hThread;
	DWORD m_nThreadID;
};
