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

void Command::whatCommand(char *buffer)
{
    std::string str;
    std::istringstream iss(buffer);
    size_t pos;
    while (std::getline(iss, str))
    {
        pos = str.find("KICK");
        if (pos !=  std::string::npos)
        {
            std::cout << "KICK command : " << str << std::endl;
        }
        pos = str.find("INVITE");
        if (pos !=  std::string::npos)
        {
            std::cout << "INVITE command : " << str << std::endl;
        }
        pos = str.find("TOPIC");
        if (pos !=  std::string::npos)
        {
            std::cout << "TOPIC command : " << str << std::endl;
        }
        pos = str.find("MODE");
        if (pos !=  std::string::npos)
        {
            std::cout << "MODE command : " << str << std::endl;
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            std::cout << "JOIN command : " << str << std::endl;
        }
    }
}