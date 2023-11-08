#include "../../includes/commands/Parsing.hpp"
#include "../../includes/commands/Command.hpp"
#include "../../includes/Channel/Channel.hpp"
#include "../../includes/Server/Server.hpp"

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
            // std::cout << "JOIN BY: " << _tabUser[i].getUsername() << std::endl;
            Join join;
            join.execute_cmd(str, _tabUser, i, _pfds);
            // std::cout << "nameChannel" << "|" << join.nameChannel << "|" << std::endl;
            channel.mapChannel[join.nameChannel].push_back(_tabUser[i].getUsername());
            list = listUserChannel(channel.mapChannel, _tabUser, join.nameChannel, i);
            std::string message = ":IRChub 353 " + _tabUser[i].getNickname() + " = " + join.nameChannel + " :" + list + "\r\n";
            // std::cout << CURSIVE << list << "|" << RESET << std::endl;
            // std::cout << CURSIVE << "message : |" << message << "|" << RESET << std::endl;
            std::istringstream ss(list);
            std::string word;
            while (ss >> word)
            {
                // std::cout << CURSIVE << word << RESET << std::endl;
                for (int j = 1;j <= MAX_USERS; j++)
                {
                    if (word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname())
                        send(_pfds[j].fd, message.c_str(), message.size(), 0);
                        // write(_pfds[j].fd, message.c_str(), message.size());
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
            Message message;
            message.execute_cmd(str, _tabUser, i, _pfds, channel);
        }
    }
}