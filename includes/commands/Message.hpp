#pragma once

#include "../IRC.hpp"
#include "../user/User.hpp"
#include "../Server/ErrorValue.hpp"

class Message
{
private:
public:
    Message(void);
    Message(Message const &src);
    Message(std::string str, User &user);
    ~Message();
    Message operator=(Message const &rhs);
};