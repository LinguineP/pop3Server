#include "msgModule.h"


MesssageSender::MesssageSender()
{
}

MesssageSender::~MesssageSender()
{
}

void MesssageSender::sendPOP3SrvReady(SOCKET clientSocket)
{

    std::string okMessage = "+OK POP3 server ready\r\n";

    int result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);

    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send +OK message. Error code: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent +OK message successfully." << std::endl;
    }

}



void MesssageSender::setUser(std::string usr)
{
    m_user = usr;
}

void MesssageSender::sendMaildropReady(SOCKET clientSocket)
{

    std::string okMessage = "+OK maildrop locked and ready\r\n";

    int result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);

    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send +OK message. Error code: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent +OK message successfully." << std::endl;
    }

}

void MesssageSender::StatResponse(SOCKET clientSocket)
{
    //here there should be a dbAdapter function that returns all this
    int msg_number = dbHelper.countRowsByEmail(m_user);
    int agregate_len = dbHelper.sumContentsSize(m_user);

    std::string okMessage = "+OK "+ std::to_string(msg_number)+" "+ std::to_string(agregate_len) + "\r\n";


    int result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);

    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send +OK message. Error code: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent +OK message successfully." << std::endl;
    }

}


void MesssageSender::ListResponse(SOCKET clientSocket)
{

    int msg_number = dbHelper.countRowsByEmail(m_user);
    int agregate_len = dbHelper.sumContentsSize(m_user);

    std::string okMessage = "+OK " + std::to_string(msg_number) + " " + std::to_string(agregate_len) + "\r\n";


    int result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);

   
    //here there should be a db adapter function that returns a vector of message id s and their lens formated as a string
    std::vector<Mail> message_list = dbHelper.getMailInfoByEmail(m_user);

    for (Mail message : message_list) {
  
        char buffer[10];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
        }

        std::string msgToSend = std::to_string(message.getUserMailId()) + " " + std::to_string(message.getMsgSize()) + "\r\n";
        
        int result = send(clientSocket, msgToSend.c_str(), msgToSend.length(), 0);
    }

    

    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send +OK message. Error code: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent +OK message successfully." << std::endl;
    }

}


void MesssageSender::RetrResponse(SOCKET clientSocket, int target)
{


    int result;

    

   
    //also get msg size and send it via ok
    
    //here there should be a db adapter function that returns a message  then we should encrypt it and send it

   

    

    std::string mail_text;
    if (dbHelper.getMailContents(target, m_user, mail_text)) {

        int len = mail_text.length();

        std::string okMessage = "+OK "+std::to_string(len) + " octets \r\n";

        result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);

        char buffer[10];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
        }

        std::string msgToSend = mail_text + "\r\n";

        result = send(clientSocket, msgToSend.c_str(), msgToSend.length(), 0);

       

    }
    else {
    
        std::string errMessage = "-ERR no such message\r\n";
    

        result = send(clientSocket, errMessage.c_str(), errMessage.length(), 0);
    }
    

    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send +OK message. Error code: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent +OK message successfully." << std::endl;
    }

}


void MesssageSender::DeleResponse(SOCKET clientSocket,int target)
{
    int result;
    
    if (dbHelper.switchForDeletion(target, m_user)) {

        std::string okMessage = "+OK msg deleted\r\n";
        result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);
    }
    else {

        std::string errMessage = "-ERR message " + std::to_string(target) + " already deleted\r\n";
        result = send(clientSocket, errMessage.c_str(), errMessage.length(), 0);
    }
    

    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send +OK message. Error code: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent +OK message successfully." << std::endl;
    }

}


void MesssageSender::ErrUnsuported(SOCKET clientSocket) {

}


void MesssageSender::QuitResponse(SOCKET clientSocket) {

    std::string okMessage = "+OK POP3 Srv goodbye\r\n";


    int result = send(clientSocket, okMessage.c_str(), okMessage.length(), 0);
}


std::string MesssageSender::receiveMessage(SOCKET clientSocket){

    const int bufferSize = 4096; 
    char buffer[bufferSize];
    std::string receivedMessage;

    int bytesRead;
    do {
        bytesRead = recv(clientSocket, buffer, bufferSize, 0);
        if (bytesRead > 0) {
            receivedMessage.append(buffer, bytesRead);
        }
        else if (bytesRead == 0) {
            // Connection closed by the peer
            break;
        }
        else {
            std::cerr << "Error in recv. Error code: " << WSAGetLastError() << std::endl;
            break;
        }
    } while (bytesRead == bufferSize); 
    std::cout << receivedMessage << std::endl;
    return receivedMessage;
}

void MesssageSender::sendMessage(std::string& data, SOCKET clientSocket)
{

    const char* buffer = data.c_str();
    int dataLength = data.length();

    // Send the length of the string first
    int result = send(clientSocket, reinterpret_cast<const char*>(&dataLength), sizeof(int), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send data length" << std::endl;
        return ;
    }

    // Send the actual string data
    result = send(clientSocket, buffer, dataLength, 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send data" << std::endl;
        return;
    }

    return;

}
