#ifndef UserHeader_H
#define UserHeader_H
#include <iostream>
#include <string>
#include "courses.h"
using namespace std;

class User // parent class for professor and student
{
private:
    string username, password, role;

protected:
    User()
    {

    }
    User(string username, string password, string role)
    {
        this->username = username;
        this->password = password;
        this->role = role;
    }

    string getUserName()
    {
        return this->username;
    }
};
#endif