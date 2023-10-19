#pragma once

#include "../IRC.hpp"
#include "User.hpp"

class AllClient
{

private:
    User _tabUser[MAX_USERS];

public:
    AllClient();
    ~AllClient();
    AllClient(AllClient const &src);
    AllClient operator=(AllClient const &assigment);
    void addUser(const User user);
    User getTabUser(int i);

};