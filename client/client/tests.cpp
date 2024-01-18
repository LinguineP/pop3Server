#include "tests.h"




#pragma comment(lib, "ws2_32.lib")


#pragma warning(disable : 4996)


static msgHandler msg;

void Test::test1()
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with your server's IP address
    serverAddress.sin_port = htons(69420); // Replace with your server's POP3 port

    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    // Receive the initial message from the server
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        // Check if the received message is "+OK POP3 server ready"
        if (strstr(buffer, "+OK POP3 server ready") != nullptr) {

            std::string usr = "vpavle021@gmail.com";
            std::string pass = "password";

            msg.USERmsg(clientSocket, usr, pass);
            // Receive and display the response
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "Received: " << buffer << std::endl;
            }
        }
    }


    msg.STATmsg(clientSocket);

    msg.LISTmsg(clientSocket);


    msg.RETRmsg(clientSocket, 3);

    msg.DELEmsg(clientSocket, 2);

    msg.QUITmsg(clientSocket);


    std::cout << "-----------------------------------------------------------------" << std::endl;

    // Close the connection
    closesocket(clientSocket);

    // Cleanup Winsock
    WSACleanup();

    return;
}

void Test::test2()
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with your server's IP address
    serverAddress.sin_port = htons(69420); // Replace with your server's POP3 port

    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    // Receive the initial message from the server
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        // Check if the received message is "+OK POP3 server ready"
        if (strstr(buffer, "+OK POP3 server ready") != nullptr) {

            std::string usr = "jeffE@yahoo.com";
            std::string pass = "12345678";

            msg.USERmsg(clientSocket, usr, pass);
            // Receive and display the response
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "Received: " << buffer << std::endl;
            }
        }
    }




    std::cout <<"------------------------------------------------------------------------------" << std::endl;

    // Close the connection
    closesocket(clientSocket);

    // Cleanup Winsock
    WSACleanup();
    return;
}

void Test::test3()
{

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with your server's IP address
    serverAddress.sin_port = htons(69420); // Replace with your server's POP3 port

    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    // Receive the initial message from the server
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        // Check if the received message is "+OK POP3 server ready"
        if (strstr(buffer, "+OK POP3 server ready") != nullptr) {

            std::string usr = "vpavle021@gmail.com";
            std::string pass = "digity";

            msg.USERmsg(clientSocket, usr, pass);
            // Receive and display the response
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "Received: " << buffer << std::endl;
            }
        }
    }



    std::cout << "-----------------------------------------------------------------" << std::endl;

    // Close the connection
    closesocket(clientSocket);

    // Cleanup Winsock
    WSACleanup();

    return;
}

void Test::test4()
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with your server's IP address
    serverAddress.sin_port = htons(69420); // Replace with your server's POP3 port

    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    // Receive the initial message from the server
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        // Check if the received message is "+OK POP3 server ready"
        if (strstr(buffer, "+OK POP3 server ready") != nullptr) {

            std::string usr = "vpavle021@gmail.com";
            std::string pass = "password";

            msg.USERmsg(clientSocket, usr, pass);
            // Receive and display the response
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "Received: " << buffer << std::endl;
            }
        }
    }


    msg.STATmsg(clientSocket);

    msg.LISTmsg(clientSocket);


    msg.RETRmsg(clientSocket, 555);

    msg.DELEmsg(clientSocket, 555);

    msg.QUITmsg(clientSocket);


    std::cout << "-----------------------------------------------------------------" << std::endl;

    // Close the connection
    closesocket(clientSocket);

    // Cleanup Winsock
    WSACleanup();
    return;
}
