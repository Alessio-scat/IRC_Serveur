#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"

Invite::Invite(void):Command(){}

Invite::~Invite(void){}

void Invite::execute_cmd(std::string str)
{
    (void)str;
}

void Invite::ParseInviteCmd(std::string &str)
{
    ft_trim(str);
    _cmd = str.substr(0, 6);
    std::cout << UNDER << _cmd << RESET << std::endl;
}

void Invite::execute_cmd(std::string str, std::deque<struct pollfd> _pfds, User *_tabUser, int y)
{
    size_t index = 7;
    size_t endNick = str.find('#', index);
    std::string tmpNick;
    std::string tmpChannel;

    ParseInviteCmd(str);
    if (str.find('#', index) == std::string::npos)
    {
        std::cout << "ERROR: INVITE need #" << std::endl;
        // throw ERR_NEEDMOREPARAMS();
        writeInfd(ERR_NEEDMOREPARAMS(_tabUser[y].getNickname(), _cmd), y, _pfds);
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
    int i;
    for (i = 0; i < MAX_USERS; i++)
    {
        std::cout << "|" <<_tabUser[i].getNickname() << "|" << std::endl;
        if (_tabUser[i].getNickname() == _nickInvite)
            break ;
    }
    std::cout << i << std::endl;
    std::string message2 = ":" + _tabUser[y].getUsername() + " INVITE " + _nickInvite + " " + _channelInvite + "\r\n";
    // std::string message = "You have been invited to" + _channelInvite + "by" + _nickInvite + "\r\n";
    // send(_pfds[i].fd, message.c_str(), message.size(), 0);
    // write(_pfds[i].fd, message.c_str(), message.size());
    write(_pfds[i].fd, message2.c_str(), message2.size());
    write(_pfds[y].fd, message2.c_str(), message2.size());
}