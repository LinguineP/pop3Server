#include "dbAdapter.h"



dbAdapter dbHelper(dbPath);


//callbacks
int dbAdapter::callbackCount(void* data, int argc, char** argv, char** colNames) {
    int* result = static_cast<int*>(data);
    *result = atoi(argv[0]);
    return 0;
}

int dbAdapter::callbackMailInfo(void* data, int argc, char** argv, char** colNames)
{
    auto* mailList = static_cast<std::vector<Mail> *>(data);

    if (argc == 2) {
 
        int userMailId = atoi(argv[0]);
        int MsgSize = atoi(argv[1]);

        mailList->emplace_back(userMailId,MsgSize);
    }

    return 0;
}



int dbAdapter::callbackBannedStatus(void* data, int argc, char** argv, char** colNames) {
    int* bannedStatus = static_cast<int*>(data);
    *bannedStatus = atoi(argv[0]);
    return 0;
}

int dbAdapter::callbackSumContentsSize(void* data, int argc, char** argv, char** colNames) {
    int* totalContentsSize = static_cast<int*>(data);
    *totalContentsSize = atoi(argv[0]);
    return 0;
}

int dbAdapter::callbackRowCount(void* data, int argc, char** argv, char** colNames) {
    int* rowCount = static_cast<int*>(data);
    *rowCount = atoi(argv[0]);
    return 0;
}

int dbAdapter::callbackMailContents(void* data, int argc, char** argv, char** colNames) {
    auto* mailContents = static_cast<std::string*>(data);

    if (argc == 1 && argv[0]) {
        *mailContents = argv[0];
    }

    return 0;
}

int dbAdapter::callbackUpdateForDeletion(void* data, int argc, char** argv, char** colNames) {
    int* result = static_cast<int*>(data);
    *result = atoi(argv[0]);
    return 0;
}


//contr destr
dbAdapter::dbAdapter(const char* dbPath) {
    if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
        std::cerr << "Error opening SQLite database." << std::endl;
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
}

 dbAdapter::~dbAdapter() {
    sqlite3_close(db);
}


 //exposed methods

//returns true if user auth is ok
bool dbAdapter::isLoginValid(std::string email, std::string password) {
    std::string sql = "SELECT COUNT(*) FROM users WHERE email = '" + std::string(email) + "' AND password = '" + std::string(password) + "';";

    int result;
    if (sqlite3_exec(db, sql.c_str(), callbackCount, &result, nullptr) != SQLITE_OK) {
        std::cerr << "Error checking login validity." << std::endl;
        exit(EXIT_FAILURE);
    }

    return result > 0;
}


//returns true if user is banned
bool dbAdapter::isBanned(std::string email) {
    std::string sql = "SELECT banned FROM users WHERE email = '" + std::string(email) + "';";

    int bannedStatus = -1;  // Initialize to a value that indicates an error

    if (sqlite3_exec(db, sql.c_str(), callbackBannedStatus, &bannedStatus, nullptr) != SQLITE_OK) {
        std::cerr << "Error checking banned status." << std::endl;
        exit(EXIT_FAILURE);
    }

    return (bannedStatus != 0);
}

int dbAdapter::countRowsByEmail(std::string email) {
    std::string sql = "SELECT COUNT(*) FROM MAILS WHERE email = '" + email + "';";

    int rowCount = 0;

    if (sqlite3_exec(db, sql.c_str(), callbackRowCount, &rowCount, nullptr) != SQLITE_OK) {
        std::cerr << "Error counting rows." << std::endl;
        exit(EXIT_FAILURE);
    }

   

    return rowCount;
}


int dbAdapter::sumContentsSize(const std::string& email) {
   

    std::string sql = "SELECT IFNULL(SUM(contents_size), 0) FROM MAILS WHERE email = '" + std::string(email) + "';";

    int totalContentsSize = 0;

    if (sqlite3_exec(db, sql.c_str(), callbackSumContentsSize, &totalContentsSize, nullptr) != SQLITE_OK) {
        std::cerr << "Error summing contents_size." << std::endl;
        exit(EXIT_FAILURE);
    }

    

    return totalContentsSize;
}



std::vector<Mail> dbAdapter::getMailInfoByEmail(std::string email) {
    std::vector<Mail> mailInfoList;

    std::string sql = "SELECT users_mail_id, contents_size FROM MAILS WHERE email = '" + std::string(email) + "';";

    if (sqlite3_exec(db, sql.c_str(), callbackMailInfo, &mailInfoList, nullptr) != SQLITE_OK) {
        std::cerr << "Error retrieving mail information." << std::endl;
        exit(EXIT_FAILURE);
    }

    return mailInfoList;
}

bool dbAdapter::getMailContents(int usersMailId, std::string email, std::string& mailContents)
{
    std::string sql = "SELECT mail_contents FROM MAILS WHERE users_mail_id = " + std::to_string(usersMailId) +
        " AND email = '" + std::string(email) + "' AND for_deletion = 0 LIMIT 1;";

    if (sqlite3_exec(db, sql.c_str(), callbackMailContents, &mailContents, nullptr) != SQLITE_OK) {
        std::cerr << "Error retrieving mail contents." << std::endl;
        return false;
    }

    return !mailContents.empty(); // Return true if mail contents are not empty
}

bool dbAdapter::switchForDeletion(int usersMailId, std::string email)
{

    std::string sql = "UPDATE MAILS SET for_deletion = 1 WHERE users_mail_id = " + std::to_string(usersMailId) +
        " AND email = '" + email + "' AND for_deletion = 0;";

    int result;
    char *errmsg;
    if (sqlite3_exec(db, sql.c_str(), callbackUpdateForDeletion, &result, &errmsg) != SQLITE_OK) {
        std::cerr << "Error updating for_deletion." <<errmsg<< std::endl;
        exit(EXIT_FAILURE);
    }

    return (result == 1); // Return true if exactly one row was updated (for_deletion was switched)
}

void dbAdapter::deleteForDeletionRows(std::string email){

    std::string sql = "DELETE FROM MAILS WHERE email = '" + email +
        "' AND for_deletion = 1;";
    char* errmsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
        std::cerr << "Error deleting rows with for_deletion set to 1." <<errmsg << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "\n~ Deleted mails marked for deletion ~"<< std::endl;
}