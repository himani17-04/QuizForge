#include "../include/User.h"
#include <iostream>

using namespace std;

// Default constructor
User::User()
{
    userId = 0;
    username = "";
    password = "";
    fullName = "";
}

// Parameterized constructor
User::User(int id, string name, string pass, string nameOfUser)
{
    userId = id;
    username = name;
    password = pass;
    fullName = nameOfUser;
}

// Setters

void User::setUserId(int id)
{
    userId = id;
}

void User::setUsername(string name)
{
    username = name;
}

void User::setPassword(string pass)
{
    password = pass;
}

void User::setFullName(string name)
{
    fullName = name;
}

// Getters

int User::getUserId() const
{
    return userId;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

string User::getFullName() const
{
    return fullName;
}

// Display user information

void User::displayUser() const
{
    cout << "\n----------------------------------------\n";
    cout << "User ID   : " << userId << "\n";
    cout << "Username  : " << username << "\n";
    cout << "Full Name : " << fullName << "\n";
    cout << "----------------------------------------\n";
}

// Validate password

bool User::validatePassword(string pass) const
{
    return password == pass;
}