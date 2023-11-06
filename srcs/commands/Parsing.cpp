#include "../../includes/commands/Parsing.hpp"
#include "../../includes/commands/Command.hpp"
#include "../../includes/Channel/Channel.hpp"
#include "../../includes/Server/Server.hpp"

std::string printMap(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser, std::string join) {
    std::string list;
    int i = 0;
    (void)_tabUser;
    for (std::map<std::string, std::list<std::string> >::const_iterator it = channel.begin(); it != channel.end(); ++it) {
        // std::cout << "Channel: " << it->first << std::endl;
        // std::cout << "Subscribers: ";
        if (it->first == join)
        {
            for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
            {
                std::cout << CURSIVE << *subIt << " " << RESET;
                if (i == 0) //&& it->second.size() == 1)
                {
                    // std::cout << "1 size\n";
                    for (int j = 1; j <= MAXCLIENT; j++)
                    {
                        if (*subIt == _tabUser[j].getNickname())
                            _tabUser[j].setOperateur(1);
                    }
                    list += "@" + *subIt;
                }
                else if (i == 0)
                    list += *subIt;
                else
                    list += " " + *subIt;
                i++;
            }
            // std::cout << CURSIVE << list << RESET << std::endl;
            // std::cout << CURSIVE << i << RESET << std::endl;
            // std::cout << std::endl;
        }
    }
    return (list);
}

void Parsing::whatCommand(char *buffer, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel)
{
    std::string str;
    std::istringstream iss(buffer);
    size_t pos;
    while (std::getline(iss, str))
    {
        pos = str.find("KICK");
        if (pos !=  std::string::npos)
        {
            Kick kick;
            kick.execute_cmd(str);
        }
        pos = str.find("INVITE");
        if (pos !=  std::string::npos)
        {
            Invite invite;
            std::cout << CURSIVE << buffer << RESET << std::endl;
            invite.execute_cmd(str, _pfds, _tabUser, i, channel);
        }
        pos = str.find("TOPIC");
        if (pos !=  std::string::npos)
        {
            Topic topic; 
            topic.execute_cmd(str, _tabUser, i, _pfds, channel);
            ///ERREUR PARSING _channelTopic QUAND PAS DE TOPIC
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            std::string list;
            Join join;
            join.execute_cmd(str, _tabUser, i, _pfds);
            channel.channel[join.nameChannel].push_back(_tabUser[i].getUsername());
            list = printMap(channel.channel, _tabUser, join.nameChannel);
            std::string message = ":IRChub 353 " + _tabUser[i].getNickname() + " = " + join.nameChannel + " :" + list + "\r\n";
            std::istringstream ss(list);
            std::string word;
            while (ss >> word)
            {
                for (int j = 1;j <= MAXCLIENT; j++)
                {
                    if (word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname())
                        send(_pfds[j].fd, message.c_str(), message.size(), 0);
                }
            }
        }
        pos = str.find("MODE");
        if (pos !=  std::string::npos)
        {
            Mode mode;
            mode.execute_cmd(str, channel);
            mode.changeMode(channel);
            mode.printListMode(channel);
        }
        pos = str.find("PRIVMSG");
        if (pos !=  std::string::npos)
        {
            std::string list;
            pos = str.find("#");
            if (pos !=  std::string::npos)
            {
                int j = pos;
                int size = 0;
                while (str[j] && str[j] != ' ')
                {
                    j++;
                    size++;
                }
                std::string channelName = str.substr(pos, size);
                std::cout << "|" << channelName << "|" << std::endl;
                list = printMap(channel.channel, _tabUser, channelName);
                str = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
                std::istringstream ss(list);
                std::string word;
                while (ss >> word)
                {
                    for (int j = 1; j <= MAXCLIENT; j++)
                    {
                        if ((word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname()) && word != _tabUser[i].getNickname() && word != "@" + _tabUser[i].getNickname())
                            send(_pfds[j].fd, str.c_str(), str.size(), 0);
                    }
                }
            }
        }
    }
}