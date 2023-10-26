#include "../../includes/commands/Parsing.hpp"
#include "../../includes/commands/Command.hpp"
#include "../../includes/Channel/Channel.hpp"
#include "../../includes/Server/Server.hpp"

std::string printMap(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser) {
    std::string list;
    int i = 0;
    (void)_tabUser;
    for (std::map<std::string, std::list<std::string> >::const_iterator it = channel.begin(); it != channel.end(); ++it) {
        std::cout << "Channel: " << it->first << std::endl;
        std::cout << "Subscribers: ";
        
        for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt) {
            std::cout << *subIt << " ";
            if (i == 0) //&& it->second.size() == 1)
            {
                std::cout << "1 size\n";
                for (int j = 1;j <= MAXCLIENT; j++)
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
        
        std::cout << CURSIVE << list << RESET << std::endl;
        std::cout << CURSIVE << i << RESET << std::endl;
        std::cout << std::endl;
    }
    return (list);
}

void Parsing::whatCommand(char *buffer, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel)
{
    std::string str;
    std::istringstream iss(buffer);
    size_t pos;
    // std::cout << "ici" << std::endl;
    while (std::getline(iss, str))
    {
        pos = str.find("KICK");
        if (pos !=  std::string::npos)
        {
            std::cout << "KICK command : " << str << std::endl;
            // Kick kick(str, _tabUser[i]);
            Kick kick;
            kick.execute_cmd(str);
        }
        pos = str.find("INVITE");
        if (pos !=  std::string::npos)
        {
            std::cout << "INVITE BY: " << _tabUser[i].getUsername() << std::endl;
            Invite invite;
            invite.execute_cmd(str);
        }
        pos = str.find("TOPIC");
        if (pos !=  std::string::npos)
        {
            std::cout << "TOPIC BY: " << _tabUser[i].getUsername() << std::endl;
            // Topic topic(str);
            Topic topic;
            topic.execute_cmd(str);
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            std::string list;
            std::cout << "JOIN BY: " << _tabUser[i].getUsername() << std::endl;
            Join join;
            join.execute_cmd(str, _tabUser, i, _pfds);
            channel.channel[join.nameChannel].push_back(_tabUser[i].getUsername());
            list = printMap(channel.channel, _tabUser);
            std::string message = ":IRChub 353 " + _tabUser[i].getNickname() + " = #a :" + list + "\r\n";
            std::cout << CURSIVE << list << "|" << RESET << std::endl;
            std::cout << CURSIVE << "message : |" << message << "|" << RESET << std::endl;
            std::istringstream ss(list);
            std::string word;
            while (ss >> word)
            {
                std::cout << CURSIVE << word << RESET << std::endl;
                for (int j = 1;j <= MAXCLIENT; j++)
                {
                    if (word == _tabUser[j].getNickname())
                        write(_pfds[j].fd, message.c_str(), message.size());
                }
            }
        }
        pos = str.find("MODE");
        if (pos !=  std::string::npos)
        {
            std::cout << "MODE BY: " << _tabUser[i].getUsername() << std::endl;
            // Mode mode(str);
            Mode mode;
            mode.execute_cmd(str);
            mode.changeMode();
        }
        // pos = str.find("PRIVMSG");
        // if (pos !=  std::string::npos)
        // {
        //     std::cout << "PRIVMSG BY: " << _tabUser[i].getUsername() << std::endl;
        //     // Message message;
        //     // message.execute_cmd(str);
        // }
    }
}