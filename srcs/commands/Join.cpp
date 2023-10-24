#include "../../includes/commands/Join.hpp"

Join::Join(void){}

Join::Join(Join const &src)
{
    *this = src;
}

Join::Join(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    std::cout << _tabUser[i].getUsername() << std::endl;
    std::cout << "JOIN command : " << str << std::endl;
    std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
    std::cout << "message : " << message << std::endl;
    write(_pfds[i].fd, message.c_str(), message.size());
}

Join::~Join(){}

Join Join::operator=(Join const &rhs)
{
    (void)rhs;
    return (*this);
}