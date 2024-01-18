#include "cliMsgModule.h"
#include <vector>
#include <sstream>



std::string msgHandler::StrFromNetwork(SOCKET cliSock)
{
    std::string clr = "clrToSnd";
    send(cliSock, clr.c_str(), clr.length(), 0);
    char buffer[4000];
    int bytesReceived = recv(cliSock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        
    }
    
    

    return std::string(buffer);
}

void msgHandler::USERmsg(SOCKET cliSock, std::string username, std::string password)
{
    std::cout << "___________________USER cmd_________________ " << std::endl;
    std::string userMessage = "USER "+username+" " +password+ "\r\n";
    send(cliSock, userMessage.c_str(), userMessage.length(), 0);
}

void msgHandler::QUITmsg(SOCKET cliSock)
{
    std::cout << "___________________QUIT cmd_________________ " << std::endl;
    std::string quitMessage = "QUIT \r\n";
    send(cliSock, quitMessage.c_str(), quitMessage.length(), 0);
    recvOneliner(cliSock);
}

void msgHandler::recvOneliner(SOCKET cliSock)
{

    char buffer[1024];
    int bytesReceived = recv(cliSock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;

 
    }

}





void msgHandler::recvTransmision(SOCKET cliSock,int expected)
{

    std::vector<std::string> receivedMails;
    for (int i = 0; i < expected; i++)
    {

        receivedMails.push_back(StrFromNetwork(cliSock));
    }
    

    for (std::string mail : receivedMails) {
        std::cout << "UserMailID size | " << mail << std::endl;
    }

    return;
    
}

void msgHandler::STATmsg(SOCKET cliSock)
{
    std::string listMessage = "STAT \r\n";

    std::cout << "___________________STAT cmd_________________ " << std::endl;

    send(cliSock, listMessage.c_str(), listMessage.length(), 0);

    char buffer[1024];
    int bytesReceived = recv(cliSock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';

    }

    std::cout << "Received: " << buffer << std::endl;
}

void msgHandler::LISTmsg(SOCKET cliSock)
{

    std::string listMessage = "LIST \r\n";

    std::cout << "___________________LIST cmd_________________ " << std::endl;
    
    send(cliSock, listMessage.c_str(), listMessage.length(), 0);

    char buffer[1024];
    int bytesReceived = recv(cliSock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        
    }
    
    std::cout << "Received: " << buffer << std::endl;

    std::string msg(buffer);
    std::istringstream iss(msg);
    std::string command;
   
    int transmitionSize=0;
    iss >> command;
    
    
    if (iss >> transmitionSize){
        std::cout << "Mail list:"  << std::endl;
        recvTransmision(cliSock, transmitionSize);
    }

    return;

}

void msgHandler::RETRmsg(SOCKET cliSock,int msgId)
{
    std::string listMessage = "RETR "+std::to_string(msgId) + " \r\n";

    std::cout << "___________________RETR cmd_________________ " << std::endl;

    send(cliSock, listMessage.c_str(), listMessage.length(), 0);

    char buffer[1024];
    int bytesReceived = recv(cliSock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';

    }

    std::cout << "Received: " << buffer << std::endl;

    std::string msg(buffer);
    std::istringstream iss(msg);
    std::string command;

    int transmitionSize = 0;
    iss >> command;

   

    if (command == "+OK") {
        std::cout << std::endl << "##############~mail body is~############# " << std::endl << std::endl;

        std::cout << StrFromNetwork(cliSock)<< std::endl;

        std::cout << std::endl << "#########################################" << std::endl<<std::endl;
    }
}

void msgHandler::DELEmsg(SOCKET cliSock, int msgId)
{

    std::string listMessage = "DELE " + std::to_string(msgId) + " \r\n";

    std::cout << "___________________DELE cmd_________________ " << std::endl;

    send(cliSock, listMessage.c_str(), listMessage.length(), 0);

    char buffer[1024];
    int bytesReceived = recv(cliSock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';

    }

    std::cout << "Received: " << buffer << std::endl;

}








