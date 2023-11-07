#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"
# include "../../includes/Server/Server.hpp"

std::string printMap(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser, std::string join);

Join::Join(void){}

void Join::execute_cmd(std::string str)
{
    (void)str;
}

/*
    A faire:
        -  ERR_NEEDMOREPARAMS (461) 
        -  ERR_BADCHANNELKEY (475) 
        -  OK: ERR_INVITEONLYCHAN (473)
        -  RPL_NAMREPLY (353) 
        -  RPL_ENDOFNAMES (366) 
*/

void Join::ParseJoinCmd(std::string &str)
{
    // std::istringstream ss(str);
    // std::string token;
    // int i = 0;

    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ' ')) {
        // Divise la chaîne en utilisant l'espace comme délimiteur
        std::istringstream iss2(token);
        std::string subtoken;

        while (std::getline(iss2, subtoken, ',')) {
            // Divise la sous-chaîne en utilisant la virgule comme délimiteur
            ft_trim(subtoken);
            tokens.push_back(subtoken);
        }
    }

   for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
    const std::string& t = *it;
    std::cout << "|" << t << "|" << std::endl;
    }

    // while (ss >> token)
    // {
    //     std::cout << UNDER << "str|" << token << "|" << RESET << std::endl;
    //     if (i == 0)
    //     {
    //         _cmd = token;
    //         std::cout << UNDER << "cmd|" << _cmd << "|" << RESET << std::endl;
    //         i = 1;
    //     }
    //     else if (i == 1)
    //     {
    //         _channelJoin = token;
    //         std::cout << UNDER << "_channelJoin|" << _channelJoin << "|" << RESET << std::endl;
    //         i = 2;
    //     }
    // }
}

void Join::add_user_inChannel(Channel &channel, User *_tabUser, Join &join, int i, std::deque<struct pollfd> _pfds)
{
    std::cout << BOLD << "ICI" << RESET << std::endl;
    std::string list;
    std::string word;

    channel.channel[join.nameChannel].push_back(_tabUser[i].getUsername());
    list = printMap(channel.channel, _tabUser, join.nameChannel);
    std::istringstream ss(list);

    while (ss >> word)
    {
        for (int j = 1;j <= MAXCLIENT; j++)
        {
            if (word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname())
                writeInfd(RPL_NAMREPLY(_tabUser[i].getNickname(), join.nameChannel, list), j, _pfds);
        }
    }
}


int Join::verifModeChannel(Channel &channel, User *_tabUser, int y)
{
    int isMode = 0;
    int isInvitation = 0;
    for (std::map<std::string, std::vector<char> >::iterator it = channel.mapMode.begin(); it != channel.mapMode.end(); ++it)
    {
        if (_channelJoin == it->first)
        {
            for (std::vector<char>::iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt)
            {
                if (*vecIt == 'i')
                {
                    isMode = 1;
                    std::cout << "IL Y UN MODE !!" << std::endl;
                }
            }
        }
    }

    std::cout << GREEN << _tabUser[y].getNickname() << RESET << std::endl;
    for (std::map<bool, std::list<std::string> >::iterator it = _tabUser[y]._mapModeUser.begin(); it != _tabUser[y]._mapModeUser.end(); ++it)
    {
        if (it->first == true)
        {
            for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
            {
                if (*subIt == _channelJoin)
                    isInvitation = 1;
            }
        }
    }

    std::cout << GREEN << isMode << " && " << isInvitation << RESET << std::endl;
    if (isMode == 1 && isInvitation != 1)
    {
        std::cout << "BLOCKKKK JOINNNNN" << std::endl;
        return 1;
    }
    return 0;
}

void Join::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel, Join &join)
{
    ParseJoinCmd(str);
    if (str.find('#') == std::string::npos)
    {
        writeInfd(ERR_NEEDMOREPARAMS(_tabUser[i].getUsername(), _channelJoin), i, _pfds);
        return ;
    }
    this->nameChannel = this->_channelJoin;
    if (verifModeChannel(channel, _tabUser, i) == 1)
    {
        writeInfd(ERR_INVITEONLYCHAN(_tabUser[i].getUsername(), _channelJoin), i, _pfds);
        return ;
    }
    writeInfd(RPL_JOIN(_tabUser[i].getUsername(), _channelJoin), i, _pfds);
    add_user_inChannel(channel, _tabUser, join, i, _pfds);
}

Join::~Join(){}