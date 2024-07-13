#pragma once
#include "../include/Database.hpp"
#include <iostream>

Database::Database(): conn(nullptr), host("localhost"), user("root"), password(""), dbname("chess"), port(0) {
    connect();
}

Database::~Database() {
    if (conn != nullptr) {
        mysql_close(conn);
    }
}

bool Database::connect() {
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "Failed to initialize MariaDB connection." << std::endl;
        return false;
    }

    if (mysql_real_connect(conn, host, user, password, dbname, port, nullptr, 0) == nullptr) {
        std::cerr << "Failed to connect to database: Error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        conn = nullptr;
        return false;
    }

    std::cout << "Connected to MariaDB database successfully." << std::endl;
    return true;
}

bool Database::Register(const std::string& player1, const std::string& player1_password,
                        const std::string& player2, const std::string& player2_password) {
    if (conn == nullptr) {
        std::cerr << "Not connected to database. Cannot register users." << std::endl;
        return false;
    }

    // Check if either player1 or player2 already exists
    std::string checkQuery = "SELECT id FROM users WHERE player1 = '" + player1 +
                             "' OR player2 = '" + player1 +
                             "' OR player1 = '" + player2 +
                             "' OR player2 = '" + player2 + "'";

    if (mysql_query(conn, checkQuery.c_str()) != 0) {
        std::cerr << "Username check query execution error: " << mysql_error(conn) << std::endl;
        return false;
    }

    MYSQL_RES* checkResult = mysql_store_result(conn);
    if (checkResult == nullptr) {
        std::cerr << "No result set after username check query." << std::endl;
        return false;
    }

    if (mysql_num_rows(checkResult) > 1) {
        std::cerr << "One or both usernames already exist" << std::endl;
        mysql_free_result(checkResult);
        return false;
    }

    mysql_free_result(checkResult);

    // If we get here, neither username exists, so we can insert the new users
    std::string insertQuery = "INSERT INTO users (player1, player1_password, player2, player2_password) VALUES ('"
                              + player1 + "', '" + player1_password + "', '"
                              + player2 + "', '" + player2_password + "')";

    if (mysql_query(conn, insertQuery.c_str()) != 0) {
        std::cerr << "User registration query execution error: " << mysql_error(conn) << std::endl;
        return false;
    }

    std::cout << "Users registered successfully." << std::endl;
    return true;
}


bool Database::Login(const std::string& player1,const std::string& player1_password,const std::string& player2,
const std::string& player2_password) {
    
    if (conn == nullptr) {
        std::cerr << "Not connected to database. Cannot authenticate." << std::endl;
        return false;
    }

    // Check if both players exist and their passwords match
    std::string query = "SELECT id FROM users WHERE "
                        "(player1 = '" + player1 + "' AND player1_password = '" + player1_password + "' AND "
                        "player2 = '" + player2 + "' AND player2_password = '" + player2_password + "')";

    if (mysql_query(conn, query.c_str()) != 0) {
        std::cerr << "Query execution error: " << mysql_error(conn) << std::endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == nullptr) {
        std::cerr << "No result set after authentication query." << std::endl;
        return false;
    }

    bool authenticated = (mysql_num_rows(result) == 1);
    mysql_free_result(result);

    if (authenticated) {
        std::cout << "Login successful." << std::endl;
    } else {
        std::cout << "Login failed. Invalid credentials." << std::endl;
    }

    return authenticated;
}
