#pragma once



#include "userModel.h"
#include "parser.h"
#include "dbAdapter.h"
#include "msgModule.h"
#include "transactions.h"


extern dbAdapter dbHelper;



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

	
	//Srv_Transaction
	void	Srv_TRANSACTION_HANDLE_MSG();
	
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
