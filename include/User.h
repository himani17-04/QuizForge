#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
private:
    int userId;
    string username;
    string password;
    string fullName;

public:
    // Default constructor
    User();

    // Parameterized constructor
    User(int id, string name, string pass, string fullName);

    // Setters
    void setUserId(int id);
    void setUsername(string name);
    void setPassword(string pass);
    void setFullName(string name);

    // Getters
    int getUserId() const;
    string getUsername() const;
    string getPassword() const;
    string getFullName() const;

    // Display user information
    void displayUser() const;

    // Validate login password
    bool validatePassword(string pass) const;
};

#endif