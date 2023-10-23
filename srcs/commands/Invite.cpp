#include "../../includes/commands/Invite.hpp"

Invite::Invite(void){}

Invite::Invite(Invite const &src)
{
    *this = src;
}

Invite::Invite(std::string str)
{
    size_t index = 7;
    size_t endNick = str.find('#', index);
    std::string tmpNick;
    std::string tmpChannel;

    if (str.find('#', index) == std::string::npos)
    {
        std::cout << "ERROR: INVITE need #" << std::endl;
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    while (str[index] == ' ')
        index++;
    if (index == std::string::npos)
    {
        std::cout << "ERROR: INVITE need more param" << std::endl;
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    tmpNick = str.substr(index, endNick - index - 1);
    if (tmpNick.find(' ') != std::string::npos)
    {
        std::cout << "ERROR: INVITE wrong nickname" << std::endl;
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    tmpChannel = str.substr(endNick);
    if (tmpChannel.find(' ') != std::string::npos || tmpChannel.size() == 2)
    {
        std::cout << "ERROR: INVITE wrong channel" << std::endl;
        // throw ERR_NOSUCHCHANNEL();
        return ;
    }
    this->_nickInvite = tmpNick;
    this->_channelInvite = tmpChannel;
    std::cout << "nickInvite : " << this->_nickInvite << std::endl;
    std::cout << "channelInvite : " << this->_channelInvite << std::endl;
}

Invite::~Invite()
{
}

Invite Invite::operator=(Invite const &rhs)
{
    if (this == &rhs)
        return (*this);
    this->_nickInvite = rhs._nickInvite;
    this->_channelInvite = rhs._channelInvite;
    return (*this);
}

void Invite::getNickInvite(std::string nickInvite)
{
    this->_nickInvite = nickInvite;
}

void Invite::getChannelInvite(std::string channelInvite)
{
    this->_channelInvite = channelInvite;
}