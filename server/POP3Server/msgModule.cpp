

#include <string>
#include <iostream>
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
