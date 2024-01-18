#pragma once

#include <iostream>
#include <string>

class Mail {

    int mailId;
    int user_mail_id;
    std::string owner;
    std::string message;
    int opened;
    int forDeletion;
    int msgSize;
public:
    Mail();
    Mail(int newMailId, int newUserMailId, const std::string& newOwner,
        const std::string& newMessage, int newOpened, int newForDeletion,int newMsgSize)
        : mailId(newMailId),
        user_mail_id(newUserMailId),
        owner(newOwner),
        message(newMessage),
        opened(newOpened),
        forDeletion(newForDeletion),
        msgSize(newMsgSize)
    {}


    Mail(int newUserMailId, int newMsgSize): 
        user_mail_id(newUserMailId),
        msgSize(newMsgSize){}


   

    Mail(const Mail& other)
        : mailId(other.mailId),
        user_mail_id(other.user_mail_id),
        owner(other.owner),
        message(other.message),
        opened(other.opened),
        forDeletion(other.forDeletion) ,
        msgSize(other.msgSize)
    {}

    ~Mail() {};

    // Getters
    int getMailId() const {
        return mailId;
    }
    
    int getMsgSize() const {
        return msgSize;
    }


    int getUserMailId() const {
        return user_mail_id;
    }

    std::string getOwner() const {
        return owner;
    }

    std::string getMessage() const {
        return message;
    }

    int getOpened() const {
        return opened;
    }

    int getForDeletion() const {
        return forDeletion;
    }

    // Setters
    void setMailId(int newMailId) {
        mailId = newMailId;
    }

    void setUserMailId(int newUserMailId) {
        user_mail_id = newUserMailId;
    }

    void setOwner(const std::string& newOwner) {
        owner = newOwner;
    }

    void setMessage(const std::string& newMessage) {
        message = newMessage;
    }

    void setOpened(int newOpened) {
        opened = newOpened;
    }

    void setMsgSize(int newMsgSize) {
        opened = newMsgSize;
    }

    void setForDeletion(int newForDeletion) {
        forDeletion = newForDeletion;
    }






};