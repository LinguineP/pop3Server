#pragma once


#include <iostream>
#include <sqlite3.h>
#include <vector>


#include "mailModel.h"

static const char* dbPath = "pop3DB.db";



class dbAdapter {
private:
    sqlite3* db;

    static int callbackCount(void* data, int argc, char** argv, char** colNames);

    static int callbackMailInfo(void* data, int argc, char** argv, char** colNames);

    static int callbackBannedStatus(void* data, int argc, char** argv, char** colNames);

    static int callbackSumContentsSize(void* data, int argc, char** argv, char** colNames);

    static int callbackRowCount(void* data, int argc, char** argv, char** colNames);

    static int callbackMailContents(void* data, int argc, char** argv, char** colNames);

    static int callbackUpdateForDeletion(void* data, int argc, char** argv, char** colNames);


public:
    dbAdapter(const char* dbPath);

    ~dbAdapter();

    bool isLoginValid(std::string email, std::string password);

    int sumContentsSize(const std::string& email);

    bool isBanned(std::string email);

    int countRowsByEmail(std::string email);

    std::vector<Mail> getMailInfoByEmail(std::string email);

    bool getMailContents(int usersMailId, std::string email, std::string& mailContents);

    bool switchForDeletion(int usersMailId, std::string email);
    void deleteForDeletionRows(std::string email);
};


 extern dbAdapter dbHelper;