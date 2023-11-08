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

    std::map<std::string, std::list<std::string> >::iterator it = channel.channel.begin();
    for (; it != channel.channel.end(); ++it)
    {
        // std::cout << "iterator : |" << it->first << "|" << std::endl;
        // std::cout << "channelFind : |" << channelFind << "|" << std::endl;
        if (it->first == channelFind)
        {
            channelExist = 1;
            break;
        }
    }
    if (channelExist != 0)
    {
        for (std::list<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            // std::cout << "iterator : " << *it2 << std::endl;
            if (*it2 == nick)
                return (0);
        }
    }
    // std::cout << "BBBBB" << std::endl;
    return (1);
}

int isModePresentInChannel(Channel &channel, std::string channelFind, char mode)
{
    std::cout << "CHANELFIND: |" << channelFind << "|" << std::endl;
    for (std::map<std::string, std::vector<char> >::iterator it = channel.mapMode.begin(); it != channel.mapMode.end(); ++it)
    {
        if (channelFind == it->first)
        {
            std::cout << "YOUPIII" << std::endl;

            ////////////////////// Print list of mode
            std::vector<char>::iterator iterator = channel.mapMode[channelFind].begin();
            std::cout << "List of mode : [";
            while (iterator != channel.mapMode[channelFind].end())
            {
                std::cout << *iterator << " ";
                iterator++;
            }
            std::cout << "]" << std::endl;
            //////////////////////

            for (std::vector<char>::iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt)
            {
                std::cout << "vecIt: " << *vecIt << std::endl;
                if (*vecIt == mode)
                {
                    std::cout << "IL Y A LE MODE " << mode << " !!" << std::endl;
                    return (1);
                }
            }
        }
    }
    //Pas de mode present
    return (0);
}