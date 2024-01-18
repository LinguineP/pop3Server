#include "mailModel.h"
#include <vector>

class User{
private:
	std::string emailAddr;
	std::string password;
	
	
public: 
    User();

	
	~User();


	

    // Getter and Setter for emailAddr
    const std::string& getEmailAddr() const {
        return emailAddr;
    }

    void setEmailAddr(const std::string& email) {
        emailAddr = email;
    }

    // Getter and Setter for password
    const std::string& getPassword() const {
        return password;
    }

    void setPassword(const std::string& pass) {
        password = pass;
    }

  

};