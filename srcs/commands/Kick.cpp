#include "../../includes/commands/Kick.hpp"

Kick::Kick(void){}

Kick::Kick(Kick const &src)
{
    *this = src;
}

Kick::Kick(std::string str)
{
    (void)str;
}

Kick::~Kick(){}

Kick Kick::operator=(Kick const &rhs)
{
    this->_channel = rhs._channel;
    this->_user = rhs._user;
    return (*this);
}