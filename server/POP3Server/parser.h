#pragma once

#include <iostream>
#include <string>
#include <sstream>


class Parser
{
public:
	Parser();
	~Parser();

    bool parseUserCommand(const std::string& command, std::string& username, std::string& password);

private:

};
