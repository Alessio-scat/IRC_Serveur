#include "../../includes/commands/Command.hpp"

Join::Join(void){}

void Join::execute_cmd(std::string str)
{
    (void)str;
}

void Join::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    this->nameChannel = "#a";
    std::cout << _tabUser[i].getUsername() << std::endl;
    std::cout << "JOIN command : " << str << std::endl;
    std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
    std::cout << "message : " << message << std::endl;
    write(_pfds[i].fd, message.c_str(), message.size());
    //map #a -> list.push.back(_tabUser[i].getUsername())
}

Join::~Join(){}