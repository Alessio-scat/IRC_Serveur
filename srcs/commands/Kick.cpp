#include "../../includes/commands/Command.hpp"

Kick::Kick(void){}

void Kick::execute_cmd(std::string str)
{
    size_t pos;
    size_t pos2 = 0;

    pos = str.find(" ") + 1;
    if (pos != std::string::npos)
    {
        pos2 = pos;
        while(str[pos2] != ' ' && str[pos2])
            pos2++;
        this->_channel = str.substr(pos, pos2 - pos);
    }
    pos = str.find(" ", pos2 + 1);
    if (pos != std::string::npos)
        this->_user = str.substr(pos2 + 1, pos - pos2);
    else
        this->_user = str.substr(pos2 + 1, str.size() - pos2);
    pos = str.find(":");
    if (pos != std::string::npos)
        this->_reason = str.substr(pos + 1, str.size() - pos);
    if (this->_channel.empty() || this->_user.empty())
    {
        std::cout << "Error\n";
        // throw(ERR_NEEDMOREPARAMS);
    }
    std::cout << this->_channel << std::endl;
    std::cout << this->_user << std::endl;
    std::cout << this->_reason << std::endl;
    std::cout << pos << std::endl;
    std::cout << pos2 << std::endl;
}

Kick::~Kick(){}
