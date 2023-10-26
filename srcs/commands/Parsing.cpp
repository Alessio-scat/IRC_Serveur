#include "../../includes/commands/Parsing.hpp"
#include "../../includes/commands/Command.hpp"
#include "../../includes/Channel/Channel.hpp"

void printMap(const std::map<std::string, std::list<std::string> >& channel) {
    for (std::map<std::string, std::list<std::string> >::const_iterator it = channel.begin(); it != channel.end(); ++it) {
        std::cout << "Channel: " << it->first << std::endl;
        std::cout << "Subscribers: ";
        
        for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt) {
            std::cout << *subIt << " ";
        }
        
        std::cout << std::endl;
    }
}

void printMapTopic(const std::map<std::string, std::string>& mapTopic)
{
    for (std::map<std::string,  std::string>::const_iterator it = mapTopic.begin(); it != mapTopic.end(); ++it) {
        std::cout << "\033[34m" << "MAPTOPIC: |" << it->first << "| |" << it->second << "| \033[0m" << std::endl;
        std::cout << std::endl;
    }
}

void Parsing::whatCommand(char *buffer, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel)
{
    std::string str;
    std::istringstream iss(buffer);
    size_t pos;
    std::cout << "BUFFER: " << buffer << std::endl;
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
            topic.rpl(str, _tabUser, i, _pfds);
            channel.mapTopic[topic.getChannelTopic()] = topic.getMsgTopic();
            printMapTopic(channel.mapTopic);
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            std::cout << "JOIN BY: " << _tabUser[i].getUsername() << std::endl;
            Join join;
            join.execute_cmd(str, _tabUser, i, _pfds);
            channel.channel[join.nameChannel].push_back(_tabUser[i].getUsername());
            printMap(channel.channel);
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