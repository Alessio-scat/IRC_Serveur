#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"

Join::Join(void){}

void Join::execute_cmd(std::string str)
{
    (void)str;
}

// void            writeInfd(const std::string& message, int i, std::deque<struct pollfd> _pfds)
// {
//     std::string buffer = message + "\r\n";
//     if (send(_pfds[i].fd, buffer.c_str(), buffer.length(), 0) < 0)
//         throw std::runtime_error("Error while sending a message to a client!");
// }

void Join::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    // std::cout << "str: " << str << std::endl;
    // this->nameChannel = "#a";
    // std::cout << _tabUser[i].getUsername() << std::endl;
    // std::cout << "JOIN command : " << str << std::endl;
    // std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
    // std::cout << "message : " << message << std::endl;
    // write(_pfds[i].fd, message.c_str(), message.size());
    writeInfd(RPL_JOIN(_tabUser[i].getUsername() + " " + str), i, _pfds);
    //map #a -> list.push.back(_tabUser[i].getUsername())
}

Join::~Join(){}