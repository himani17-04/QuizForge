#include "../include/Admin.h"
#include <iostream>

using namespace std;

// Default constructor
Admin::Admin()
{
    adminId = 0;
    username = "";
    password = "";
}

// Parameterized constructor
Admin::Admin(int id, string name, string pass)
{
    adminId = id;
    username = name;
    password = pass;
}

// Setters

void Admin::setAdminId(int id)
{
    adminId = id;
}

void Admin::setUsername(string name)
{
    username = name;
}

void Admin::setPassword(string pass)
{
    password = pass;
}

// Getters

int Admin::getAdminId() const
{
    return adminId;
}

string Admin::getUsername() const
{
    return username;
}

string Admin::getPassword() const
{
    return password;
}

// Validate admin login

bool Admin::validateLogin(string name, string pass) const
{
    return username == name && password == pass;
}

// Display admin information

void Admin::displayAdmin() const
{
    cout << "\n----------------------------------------\n";
    cout << "Admin ID  : " << adminId << "\n";
    cout << "Username  : " << username << "\n";
    cout << "----------------------------------------\n";
}