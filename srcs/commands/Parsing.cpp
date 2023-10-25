#include "../../includes/commands/Parsing.hpp"
#include "../../includes/commands/Command.hpp"

void Parsing::whatCommand(char *buffer, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
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
        pos = str.find("MODE");
        if (pos !=  std::string::npos)
        {
            std::cout << "MODE BY: " << _tabUser[i].getUsername() << std::endl;
            // Mode mode(str);
            Mode mode;
            mode.execute_cmd(str);
            mode.changeMode();
        }
        pos = str.find("JOIN");
        if (pos !=  std::string::npos)
        {
            std::cout << _tabUser[i].getUsername() << std::endl;
            std::cout << "JOIN command : " << str << std::endl;
            // int bytesSent = send(clientSockets[i].fd, str, str.size(), 0);
            // if (bytesSent == -1)
            // {
            //     std::cerr << "Erreur lors de l'envoi des données." << std::endl;
            // }
            // else
            // {
            //     std::cout << "Nombre d'octets envoyés : " << bytesSent << std::endl;
            // }
            std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
            std::cout << "message : " << message << std::endl;
            write(_pfds[i].fd, message.c_str(), message.size());
        }
    }
}