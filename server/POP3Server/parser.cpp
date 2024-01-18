#include "parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

bool Parser::parseUserCommand(const std::string& command, std::string& username, std::string& password) {
    std::istringstream iss(command);
    std::string commandType;

    // Read the first word (command type)
    if (!(iss >> commandType)) {
        std::cerr << "Failed to read command type." << std::endl;
        return false;
    }

    // Check if the command type is "USER"
    if (commandType != "USER") {
        std::cerr << "Invalid command type. Expected 'USER'." << std::endl;
        return false;
    }

    // Read the username and password
    if (!(iss >> username >> password)) {
        std::cerr << "Failed to read username and password." << std::endl;
        return false;
    }

    // Output for testing (you can remove this in your actual application)
    std::cout << "Received username: " << username << std::endl;
    std::cout << "Received password: " << password << std::endl;

    return true;
}


