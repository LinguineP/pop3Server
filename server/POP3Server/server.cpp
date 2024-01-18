#include "server.h"




//static inits 
bool SrvAuto::breakFlag = false;
bool SrvAuto::connectedFlag = false;


//srv_idle
void SrvAuto::Srv_Idle_Cl_Connection_Request(){
    printf("\n<idle>\n\n");



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
    printf("\n\n<authorisation>\n\n");
    Sleep(1000);

    Parser p;
    

    std::string password;
    std::string username;

    std::string usr_msg=msg.receiveMessage(m_cliSocket);


    p.parseUserCommand(usr_msg, username, password);

    if (dbHelper.isBanned(username)) {
        Srv_DISCONECTING_Procedure();
            return;
    }
    

    if (dbHelper.isLoginValid(username,password)) {
        currentUser.setEmailAddr(username);
        msg.sendMaildropReady(m_cliSocket);
        Srv_TRANSACTION_HANDLE_MSG();
    }
   

    Srv_DISCONECTING_Procedure();
    return;
}


//Srv_Transaction
void SrvAuto::Srv_TRANSACTION_HANDLE_MSG(){
    printf("\n<transaction>\n\n");

    while (1) {

        std::string trans_msg = msg.receiveMessage(m_cliSocket);

        TransactionalRequest transaction(m_cliSocket, currentUser.getEmailAddr(), trans_msg);

        if (transaction.getRequestType() == transaction.QUIT) {
            Srv_TRANSACTION_MSG_QUIT();
            break;
        }
        else if (transaction.getRequestType() == transaction.unsupported) {
            msg.ErrUnsuported(m_cliSocket);
            continue;

        }

        transaction.respondToTransaction();
    }


    

    return;
}


void SrvAuto::Srv_TRANSACTION_MSG_QUIT(){
    msg.QuitResponse(m_cliSocket);
    return;
}
//SRV_Disconecting
void	SrvAuto::Srv_DISCONECTING_Procedure(){
    printf("\n<disconnecting>\n\n");
    dbHelper.deleteForDeletionRows(currentUser.getEmailAddr());
    std::cout << "------------------------------------------------------------------\n";
    
    return;
}



SrvAuto::SrvAuto()
{
   
}

SrvAuto::~SrvAuto()
{
}

void SrvAuto::Initialize()
{
    printf("initializing server\n_________________________________________________________________\n");
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
	