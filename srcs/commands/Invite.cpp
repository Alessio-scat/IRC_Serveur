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
    std::istringstream ss(str);
    std::string token;
    int i = 0;
    // ft_trim(str);
    // _cmd = str.substr(0, 6);
    while (ss >> token)
    {
        std::cout << UNDER << "str|" << token << "|" << RESET << std::endl;
        if (i == 0)
        {
            _cmd = token;
            std::cout << UNDER << "cmd|" << _cmd << "|" << RESET << std::endl;
            i = 1;
        }
        else if (i == 1)
        {
            _nickInvite = token;
            std::cout << UNDER << "_nickInvite|" << _nickInvite << "|" << RESET << std::endl;
            i = 2;
        }
        else if (i == 2)
        {
            if (token == "IRChub")
            {
                _channelInvite = "";
                break;
            }
            _channelInvite = token;
            std::cout << UNDER << "_channelInvite|" << _channelInvite << "|" << RESET << std::endl;
            break;
        }
    }


}

int Invite::ExistChannel(const std::map<std::string, std::list<std::string> >& channel, std::deque<struct pollfd> _pfds, int i, std::string &client)
{
    for (std::map<std::string, std::list<std::string> >::const_iterator it = channel.begin(); it != channel.end(); ++it) {
        if (it->first == this->_channelInvite)
            return 0;
    }
    writeInfd(ERR_NOSUCHCHANNEL(client, _channelInvite), i, _pfds);
    return 1;
}

void Invite::execute_cmd(std::string str, std::deque<struct pollfd> _pfds, User *_tabUser, int y, Channel &channel)
{
    // size_t index = 7;
    // size_t endNick = str.find('#', index);
    // std::string tmpNick;
    // std::string tmpChannel;

    ParseInviteCmd(str);
    if (_cmd.empty() || _nickInvite.empty() || _channelInvite.empty())
    {
        std::cout << "COUCOU" << std::endl;
        writeInfd(ERR_NEEDMOREPARAMS(_tabUser[y].getNickname(), _cmd), y, _pfds);
        return ;
    }
    // while (str[index] == ' ')
    //     index++;
    // if (index == std::string::npos)
    // {
    //     std::cout << "ERROR: INVITE need more param" << std::endl;
    //     // throw ERR_NEEDMOREPARAMS();
    //     return ;
    // }
    // tmpNick = str.substr(index, endNick - index - 1);
    // if (tmpNick.find(' ') != std::string::npos)
    // {
    //     std::cout << "ERROR: INVITE wrong nickname" << std::endl;
    //     // throw ERR_NEEDMOREPARAMS();
    //     return ;
    // }
    // tmpChannel = str.substr(endNick);
    // if (tmpChannel.find(' ') != std::string::npos || tmpChannel.size() == 2)
    // {
    //     std::cout << "ERROR: INVITE wrong channel" << std::endl;
    //     // throw ERR_NOSUCHCHANNEL();
    //     return ;
    // }
    // this->_nickInvite = tmpNick;
    // this->_channelInvite = tmpChannel;
    if (ExistChannel(channel.channel, _pfds, y, _nickInvite) == 1)
        return ;
    int i;
    for (i = 0; i < MAX_USERS; i++)
    {
        std::cout << "|" <<_tabUser[i].getNickname() << "|" << std::endl;
        if (_tabUser[i].getNickname() == _nickInvite)
            break ;
    }
    std::string message2 = ":" + _tabUser[y].getUsername() + " INVITE " + _nickInvite + " " + _channelInvite + "\r\n";
    write(_pfds[i].fd, message2.c_str(), message2.size());
    write(_pfds[y].fd, message2.c_str(), message2.size());
}