#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <fstream>
#include <iostream>

class UserManage
{

public:
    void addUser_to_CSV(const std::string& name, const std::string& id, const std::string& password, const std::string& type);
};


#endif