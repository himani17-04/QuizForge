#ifndef ADMIN_H
#define ADMIN_H

#include <string>

using namespace std;

class Admin
{
private:
    int adminId;
    string username;
    string password;

public:
    // Default constructor
    Admin();

    // Parameterized constructor
    Admin(int id, string name, string pass);

    // Setters
    void setAdminId(int id);
    void setUsername(string name);
    void setPassword(string pass);

    // Getters
    int getAdminId() const;
    string getUsername() const;
    string getPassword() const;

    // Validate admin login
    bool validateLogin(string name, string pass) const;

    // Display admin information
    void displayAdmin() const;
};

#endif