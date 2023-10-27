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

void Invite::execute_cmd(std::string str, std::deque<struct pollfd> _pfds, User *_tabUser, int y, Channel &channel)
{
    ParseInviteCmd(str);

    if (_cmd.empty() || _nickInvite.empty() || _channelInvite.empty())
    {
        std::cout << "COUCOU" << std::endl;
        writeInfd(ERR_NEEDMOREPARAMS(_tabUser[y].getNickname(), _cmd), y, _pfds);
        return ;
    }

    if (ExistChannel(channel.channel, _pfds, y, _nickInvite) == 1)
        return ;
    
    InviteClient(_tabUser, _pfds, y); 
}