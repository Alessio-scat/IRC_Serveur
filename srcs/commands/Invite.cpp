#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"

Invite::Invite(void):Command()
{
    this->_isActive = 0;
}

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

void Invite::InviteClient(User *_tabUser, std::deque<struct pollfd> _pfds, int y)
{
    int i;
    for (i = 0; i < MAX_USERS; i++)
    {
        std::cout << "|" <<_tabUser[i].getNickname() << "|" << std::endl;
        if (_tabUser[i].getNickname() == _nickInvite)
            break ;
    }
    std::string message = ":" + _tabUser[y].getUsername() + " INVITE " + _nickInvite + " " + _channelInvite + "\r\n";
    write(_pfds[i].fd, message.c_str(), message.size());
    write(_pfds[y].fd, message.c_str(), message.size());
}

int Invite::User_on_channel(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser)
{
    int y;
    for (y = 0; y < MAX_USERS; y++)
    {
        if (_tabUser[y].getNickname() == _nickInvite)
            break ;
    }

    for (std::map<std::string, std::list<std::string> >::const_iterator it = channel.begin(); it != channel.end(); ++it) {
        if (it->first == this->_channelInvite)
        {
            for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
            {
                if (*subIt == _tabUser[y].getNickname()){
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* 
    Make a : ERR_NOTONCHANNEL (442)
             ERR_CHANOPRIVSNEEDED (482)
*/

void Invite::execute_cmd(std::string str, std::deque<struct pollfd> _pfds, User *_tabUser, int y, Channel &channel)
{
    ParseInviteCmd(str);

    if (_cmd.empty() || _nickInvite.empty() || _channelInvite.empty())
    {
        std::cout << "COUCOU" << std::endl;
        writeInfd(ERR_NEEDMOREPARAMS(_tabUser[y].getNickname(), _cmd), y, _pfds);
        return ;
    }

    if (User_on_channel(channel.channel, _tabUser) == 1){
        writeInfd(ERR_USERONCHANNEL(_tabUser[y].getNickname(), _cmd), y, _pfds);
        return ;
    }

    if (ExistChannel(channel.channel, _pfds, y, _nickInvite) == 1)
        return ;
    
     InviteClient(_tabUser, _pfds, y); 
}