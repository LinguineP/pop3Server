#include "server.h"




//static inits 
bool SrvAuto::breakFlag = false;
bool SrvAuto::connectedFlag = false;







//srv_idle
void SrvAuto::Srv_Idle_Cl_Connection_Request(){
    printf("idle\n");



    if (listen(m_Socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error in listening for connections.\n" << std::endl;
        closesocket(m_Socket);
        WSACleanup();
        return ;
    }

    std::cout << "Server is listening for incoming connections...\n" << std::endl;

    // Accept a connection
    m_cliSocket = accept(m_Socket,NULL , NULL);

    msg.sendPOP3SrvReady(m_cliSocket);

    Srv_AUTHORISATION_HANDLE_MSG();


    
    return;
}


void SrvAuto::Srv_AUTHORISATION_HANDLE_MSG()
{
    printf("authorisation");
    Sleep(1000);
    Srv_TRANSACTION_HANDLE_MSG();

    

    return;
}
	//Srv_AUTHORISATION
bool SrvAuto::Srv_AUTHORISATION_User_Pass_Check(){
	return true;
}

bool SrvAuto::Srv_AUTHORISATION_User_allowed_check(){
	return true;

}
void SrvAuto::Srv_AUTHORISATION_Response(){
    
}

//Srv_Transaction
void SrvAuto::Srv_TRANSACTION_HANDLE_MSG(){

    Srv_TRANSACTION_MSG_QUIT();

    return;
}

void	SrvAuto::Srv_TRANSACTION_MSG_STAT(){

}

void	SrvAuto::Srv_TRANSACTION_MSG_LIST(){

}
void	SrvAuto::Srv_TRANSACTION_MSG_RETR(){

}
void	SrvAuto::Srv_TRANSACTION_MSG_DELE(){

}
void	SrvAuto::Srv_TRANSACTION_MSG_QUIT(){
    return;
}
//SRV_Disconecting
void	SrvAuto::Srv_DISCONECTING_Procedure(){

}



SrvAuto::SrvAuto()
{
   
}

SrvAuto::~SrvAuto()
{
}

void SrvAuto::Initialize()
{
    printf("initialize");
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return ;
    }

    // Create a socket
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Socket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return ;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(69420);


    if (bind(m_Socket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        closesocket(m_Socket);
        WSACleanup();
        return ;
    }


    while (!breakFlag) {

        Srv_Idle_Cl_Connection_Request();
        
    
    
    
    
    }

   
    closesocket(m_Socket);
    WSACleanup();

}
	