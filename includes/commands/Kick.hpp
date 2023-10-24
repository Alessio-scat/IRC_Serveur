#pragma once

#include "../IRC.hpp"
#include "../user/User.hpp"
#include "../Server/ErrorValue.hpp"

class Kick
{
private:
    std::string _user;
    std::string _channel;
    std::string _reason;
public:
    Kick(void);
    Kick(std::string str, User &user);
    Kick(Kick const &src);
    ~Kick();
    Kick operator=(Kick const &rhs);
    
};
