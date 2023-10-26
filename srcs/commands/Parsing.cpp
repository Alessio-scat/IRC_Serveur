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
            invite.execute_cmd(str, _pfds, _tabUser, i, channel);
        }
        pos = str.find("TOPIC");
        if (pos !=  std::string::npos)
        {
            Topic topic;
            topic.execute_cmd(str);
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            Join join;
            join.execute_cmd(str, _tabUser, i, _pfds);
            std::cout << "nameChannel" << "|" << join.nameChannel << "|" << std::endl;
            channel.channel[join.nameChannel].push_back(_tabUser[i].getUsername());
            // printMap(channel.channel);
        }
        pos = str.find("MODE");
        if (pos !=  std::string::npos)
        {
            Mode mode;
            mode.execute_cmd(str);
            mode.changeMode();
        }
    }
}