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
    std::map<std::string, std::list<std::string> >::iterator it = channel.mapChannel.begin();
    for (; it != channel.mapChannel.end(); ++it)
    {
        if (it->first == channelFind)
            break ;
    }
    if (it != channel.mapChannel.end())
    {
        for (std::list<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            if (*it2 == nick)
                return (0);
        }
    }
    return (1);
}