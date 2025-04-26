#include "UserManage.h"
#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <iostream>

void UserManage::addUser_to_CSV(const std::string& name, const std::string& id, const std::string& password, const std::string& type){
    std::fstream fout("all_users_data.csv", std::ios::out | std::ios::app);
    if (fout.is_open()) {
        fout << name << "," << id << "," << password << "," << type << '\n';
        fout.close();
        std::cout << "New user has been added.\n";
    } else {
        std::cerr << "Could not open file to add user.\n";
    }
}

