# include "../../includes/Channel/Channel.hpp"

Channel::Channel(void){}

Channel::Channel(Channel const &src)
{
    (void)src;
}

Channel &Channel::operator=(Channel const &rhs)
{
    (void)rhs;
    return (*this);
}

Channel::~Channel(void){}

int isInChannel(std::string channelFind, std::string nick, Channel &channel)
{
    int channelExist = 0;
    
    std::map<std::string, std::list<std::string> >::iterator it = channel.mapChannel.begin();
    for (; it != channel.mapChannel.end(); ++it)
    {
        std::cout << "iterator : |" << it->first << "|" << std::endl;
        std::cout << "channelFind : |" << channelFind << "|" << std::endl;
        if (it->first == channelFind)
        {
            std::cout << "AAAAA" << std::endl;
            channelExist = 1;
            break;
        }
    }
    if (channelExist != 0)
    {
        for (std::list<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            std::cout << "iterator : " << *it2 << std::endl;
            if (*it2 == nick)
                return (0);
        }
    }
    std::cout << "BBBBB" << std::endl;
    return (1);
}