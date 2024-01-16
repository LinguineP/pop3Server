#include "mailModel.h"
#include <vector>

class User{
private:
	int userID;
	std::string emailAddr;
	std::string password;
	std::vector<Mail> usersEmails;
	
	

public: 
    User();

	User(int id,std::string mailAddr,std::string pass){
		userID=id;
		emailAddr=mailAddr;
		password=pass;
	};
	~User();


	int getUserID() const {
        return userID;
    }

    void setUserID(int id) {
        userID = id;
    }

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

    // Getter and Setter for usersEmails
    const std::vector<Mail>& getUsersEmails() const {
        return usersEmails;
    }

    void setUsersEmails(const std::vector<Mail>& emails) {
        usersEmails = emails;
    }

};