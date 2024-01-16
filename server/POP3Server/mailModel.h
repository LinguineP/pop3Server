#pragma once

#include <iostream>
#include <string>

class Mail{
	
	int mailId;
	std::string subject;
	std::string message;
	bool opened;
public:
	Mail(int id,std::string subject,std::string content){
		mailId=id;
		subject=subject;
		message=content;
		opened=true;
	}








};