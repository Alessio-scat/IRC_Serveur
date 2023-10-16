#include "../includes/user/User.hpp"

User::User(/* args */){}

User::User(User const &src)
{
    *this = src;
}

User::~User(){}

User User::operator=(User const &rhs)
{
    *this = rhs;
    return(*this);
}

std::string User::getNickname(void)const
{
    return (this->_nickname);
}

void User::setNickname(std::string nickname)
{
    this->_nickname = nickname;
}

std::string User::getUsername(void)const
{
    return (this->_username);
}

void User::setUsername(std::string username)
{
    this->_username = username;
}