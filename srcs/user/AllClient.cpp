#include "../../includes/user/AllClient.hpp"

AllClient::AllClient()
{
    for (int i = 0; i < MAX_USERS; i++)
    {
        this->_tabUser[i].setNickname("");
        this->_tabUser[i].setUsername("");
    }
}

AllClient::~AllClient()
{
}

AllClient::AllClient(AllClient const &src)
{
    *this = src;
}

AllClient AllClient::operator=(AllClient const &assigment)
{
    if (this == &assigment)
        return (*this);
    for (int i = 0; i < MAX_USERS; i++)
    {
        this->_tabUser[i].getNickname() = assigment._tabUser[i].getNickname();
        this->_tabUser[i].getUsername() = assigment._tabUser[i].getUsername();
    }
    return (*this);
}

void AllClient::addUser(User user)
{
    for (int i = 0; i < MAX_USERS ; i++)
    {
        if (this->_tabUser[i].getNickname() == "")
        {
            this->_tabUser[i] = user;
            break;
        }
    }
}

// User *AllClient::getTabUser(void)
// {
//     return (this->_tabUser);
// }