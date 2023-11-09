#include "../../includes/commands/Command.hpp"

Kick::Kick(void){}

void Kick::execute_cmd(std::string str)
{
    (void)str;
}

void Kick::execute_cmd(std::string str, std::deque<struct pollfd> _pfds, User *_tabUser, int y, Channel &channel)
{
    size_t pos;
    size_t pos2 = 0;

    ft_trim(str);
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
    std::cout  << "|" << this->_user << "|" << std::endl;
    std::cout << this->_reason << std::endl;
    std::cout << pos << std::endl;
    std::cout << pos2 << std::endl;
    str = ":" + _tabUser[y].getNickname() + " " + str + "\r\n";
    // for (std::map<std::string, std::list<std::string> >::iterator it = channel.mapChannel.begin(); it != channel.mapChannel.end(); ++it)
    // {
    //     if (it->first == this->_channel)
    //     {
    //         for (std::list<std::string>::iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
    //         {
    //             std::cout << GREEN << "erase1" << RESET << std::endl;
    //             if (*subIt == this->_user)
    //             {
    //                 std::cout << GREEN << "erase" << RESET << std::endl;
    //                 channel.mapChannel[this->_channel].erase(subIt);
    //                 break;
    //             }
    //         }
    //     }
    // }
    std::string list = listUserChannel(channel.mapChannel, _tabUser, this->_channel, y);
    std::cout << GREEN << list << RESET << std::endl;
    std::istringstream ss(list);
    std::string word;
    while (ss >> word)
    {
        for (int j = 1; j <= MAX_USERS; j++)
        {
            if (word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname())
                send(_pfds[j].fd, str.c_str(), str.size(), 0);
        }
    }
    channel.mapChannel[this->_channel].erase(std::remove( channel.mapChannel[this->_channel].begin(), channel.mapChannel[this->_channel].end(), this->_user), channel.mapChannel[this->_channel].end());
}

Kick::~Kick(){}
