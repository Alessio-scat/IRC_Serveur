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
    if (str.find('#') == std::string::npos)
    {
        this->_channelJoin = str.substr(5);
        std::cout << "ERROR: JOIN need more param" << std::endl;
        std::string message = ":IRChub 403 " + _tabUser[i].getNickname() + " " + this->_channelJoin + " :No such channel\r\n";
        std::cout << "message : |" << message << "|" << std::endl;
        send(_pfds[i].fd, message.c_str(), message.size(), 0);
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    this->_channelJoin = str.substr(6);
    this->nameChannel = this->_channelJoin;
    std::cout << _tabUser[i].getUsername() << std::endl;
    std::cout << "JOIN command : " << str << std::endl;
    std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
    std::cout << "message : " << message << std::endl;
    writeInfd(RPL_JOIN(_tabUser[i].getUsername() + " " + str), i, _pfds);
}

Join::~Join(){}