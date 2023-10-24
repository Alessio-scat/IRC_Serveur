#include "../../includes/commands/Command.hpp"

Command::Command(/* args */)
{
}

Command::Command(Command const &src)
{
   *this = src; 
}

Command::~Command()
{
}

Command Command::operator=(Command const &rhs)
{
    (void)rhs;
    return (*this);
}

void Command::whatCommand(char *buffer, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    std::string str;
    std::istringstream iss(buffer);
    size_t pos;
    // std::cout << "ici" << std::endl;
    while (std::getline(iss, str))
    {
        pos = str.find("KICK");
        if (pos !=  std::string::npos)
        {
            std::cout << "KICK command : " << str << std::endl;
            Kick kick(str, _tabUser[i]);
        }
        pos = str.find("INVITE");
        if (pos !=  std::string::npos)
        {
            std::cout << "INVITE BY: " << _tabUser[i].getUsername() << std::endl;
            Invite invite(str);
        }
        pos = str.find("TOPIC");
        if (pos !=  std::string::npos)
        {
            std::cout << "TOPIC BY: " << _tabUser[i].getUsername() << std::endl;
            Topic topic(str);
        }
        pos = str.find("MODE");
        if (pos !=  std::string::npos)
        {
            std::cout << "MODE BY: " << _tabUser[i].getUsername() << std::endl;
            Mode mode(str);
            mode.changeMode();
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            std::cout << "JOIN BY: " << _tabUser[i].getUsername() << std::endl;
            Join join(str, _tabUser, i, _pfds);
            // std::cout << _tabUser[i].getUsername() << std::endl;
            // std::cout << "JOIN command : " << str << std::endl;
            // std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
            // std::cout << "message : " << message << std::endl;
            // write(_pfds[i].fd, message.c_str(), message.size());
        }
    }
}