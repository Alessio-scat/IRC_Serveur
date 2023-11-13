#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"
# include "../../includes/Server/Server.hpp"

// std::string printMap(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser, std::string join);

Join::Join(void){}

void Join::execute_cmd(std::string str)
{
    (void)str;
}

/*
    ERR_NEEDMOREPARAMS (461) 
    OK! -- ERR_BADCHANNELKEY (475)
    ERR_BANNEDFROMCHAN (474)
    ERR_CHANNELISFULL (471)
    OK! -- ERR_INVITEONLYCHAN (473)
    OK! -- ERR_BADCHANMASK (476)
    OK! -- RPL_NAMREPLY (353)  
*/

void Join::connectChannelKey(Channel &channel)
{
    for (size_t i = 0; i < _tokensKey.size(); i++)
    {
        channel._mapChannelKey[_tokensChannel[i]] = _tokensKey[i];
    }

    for (std::map<std::string, std::string>::iterator it = channel._mapChannelKey.begin(); it != channel._mapChannelKey.end(); ++it) {
        std::cout << "Clé : " << it->first << ", Valeur : " << it->second << std::endl;
    }
}

void Join::ParseJoinCmd(std::string &str, Channel &channel)
{
    std::istringstream iss(str);
    std::string token;

    _tokensChannel.clear();
    _tokensKey.clear();
    while (std::getline(iss, token, ' '))
    {
        std::istringstream iss2(token);
        std::string subtoken;
        // std::cout << "11111111111111111111111111111" << std::endl;

        while (std::getline(iss2, subtoken, ','))
        {
            ft_trim(subtoken);
            if (subtoken == "JOIN")
                _cmd = subtoken;
            else if (subtoken[0] == '#' || subtoken[0] == '&')
                _tokensChannel.push_back(subtoken);
            else
                _tokensKey.push_back(subtoken);
                
        }
    }

    for (size_t i = 0; i < _tokensKey.size(); i++)
    {
        std::cout << "55555555555" << std::endl;
        channel.mapMode[_tokensChannel[i]].push_back('k');
    }

}

void Join::add_user_inChannel(Channel &channel, User *_tabUser, Join &join, int i, std::deque<struct pollfd> _pfds, std::string tokenChannel)
{
    (void)join;
    std::string list;
    std::string word;

    channel.mapChannel[tokenChannel].push_back(_tabUser[i].getUsername());
    // list = printMap(channel.mapChannel, _tabUser, tokenChannel);
    list = listUserChannel(channel.mapChannel, _tabUser, tokenChannel, i);
    std::istringstream ss(list);

    while (ss >> word)
    {
        for (int j = 1;j <= MAX_USERS; j++)
        {
            if (word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname())
                writeInfd(RPL_NAMREPLY(_tabUser[i].getNickname(), tokenChannel, list), j, _pfds);
        }
    }
}


int Join::verifModeChannel(Channel &channel, User *_tabUser, int y, std::string &tokenChannel)
{
    int isMode = 0;
    int isInvitation = 0;

    for (std::map<std::string, std::vector<char> >::iterator it = channel.mapMode.begin(); it != channel.mapMode.end(); ++it)
    {
        if (tokenChannel == it->first)
        {
            for (std::vector<char>::iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt)
            {
                std::cout << "ZZZZZZZZZZZZ" << std::endl;
                if (*vecIt == 'i')
                {
                    isMode = 1;
                    for (std::map<bool, std::list<std::string> >::iterator it = _tabUser[y]._mapModeUser.begin(); it != _tabUser[y]._mapModeUser.end(); ++it)
                    {
                        if (it->first == true)
                        {
                            for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
                            {
                                if (*subIt == tokenChannel)
                                    isInvitation = 1;
                            }
                        }
                    }

                    if (isMode == 1 && isInvitation != 1)
                        return 1;
                }
                else if (*vecIt == 'k')
                {
                    if (!_tokensKey.size())
                        return 2;
                    for (size_t i = 0; i < _tokensKey.size(); i++)
                    {
                        std::cout << "11111111111111111| " << i << std::endl;
                        // std::string list = printMap(channel.mapChannel, _tabUser, tokenChannel);
                        std::string list = listUserChannel(channel.mapChannel, _tabUser, tokenChannel, y);
                        if (list.empty())
                            connectChannelKey(channel);
                        else
                        {
                            for (std::map<std::string, std::string>::iterator it = channel._mapChannelKey.begin(); it != channel._mapChannelKey.end(); ++it)
                            {
                                // std::cout << GREEN << "it->first: " << it->first << " && tokenChannel" << _tokensChannel[i] << RESET << std::endl;
                                if (it->first == _tokensChannel[i])
                                {
                                    if (it->second != _tokensKey[i])
                                        return 2;

                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

void Join::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel, Join &join)
{
    if (str.find('#') == std::string::npos && str.find('&') == std::string::npos)
    {
        std::string test = "channel";
        writeInfd(ERR_BADCHANMASK(test), i, _pfds);
        // writeInfd(ERR_NEEDMOREPARAMS(_tabUser[i].getUsername(), _channelJoin), i, _pfds);
        return ;
    }
    ParseJoinCmd(str, channel);

    for (size_t k = 0; k < _tokensChannel.size(); k++)
    {
        if (verifModeChannel(channel, _tabUser, i, _tokensChannel[k]) == 1)
        {
            writeInfd(ERR_INVITEONLYCHAN(_tabUser[i].getUsername(), _tokensChannel[k]), i, _pfds);
            return ;
        }
        else if (verifModeChannel(channel, _tabUser, i, _tokensChannel[k]) == 2)
        {
            writeInfd(ERR_BADCHANNELKEY(_tabUser[i].getUsername(), _tokensChannel[k]), i, _pfds);
            return ;
        }
    }

    for (size_t j = 0; j < _tokensChannel.size() ; j++)
    {
        writeInfd(RPL_JOIN(_tabUser[i].getUsername(), _tokensChannel[j]), i, _pfds);
        add_user_inChannel(channel, _tabUser, join, i, _pfds, _tokensChannel[j]);
    }
}

Join::~Join(){}