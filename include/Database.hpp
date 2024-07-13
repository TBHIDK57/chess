#pragma once

#include <mariadb/mysql.h>
#include <string>

class Database {
private:
    MYSQL* conn;
    const char* host;
    const char* user;
    const char* password;
    const char* dbname;
    unsigned int port;

public:
    Database();
    ~Database();

    bool connect();
    bool Register(const std::string& player1,const std::string& player2, const std::string& player1_password, const std::string& player2_password);
    bool Login(const std::string& player1,const std::string& player2, const std::string& player1_password, const std::string& player2_password);
};


