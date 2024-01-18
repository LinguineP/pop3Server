#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>


#include "cliMsgModule.h"



class Test {



public:
	//all functionalities ok test
	void test1();
	//unable to login banned email address
	void test2();
	//unable to login wrong password
	void test3();
	//unsuccsessfull retr and dele
	void test4();




};