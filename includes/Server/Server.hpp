#pragma once

# include "../includes/IRC.hpp"
# include "../Channel/Channel.hpp"
#include "../../includes/user/User.hpp"
#include "../../includes/commands/Command.hpp"

# define MAXCLIENT 10

class Server
{

private:
    std::string _mdp;
    unsigned int _host;
    int newSocket;                 // pour le nouveau socket client lorsqu'une connexion est acceptée
    struct sockaddr_in serverAddr; // pour stocker les info du serveur
    struct sockaddr_in newAddr;    // et du client
    char buffer[1024];             // pour stocker les données reçues des clients
    socklen_t addrSize;
    std::deque<struct pollfd> _pfds;
    int serverSocket;
    Command command;
    User _tabUser[MAX_USERS];

public:
    Server(void);
    Server(Server const &src);
    Server(std::string host, std::string mdp);
    ~Server();
    Server operator=(Server const &assigment);

    void Start_Server(void);
    void Run_Server(void);
    void connect_client(void);
    int password(void);
    void fillUser(User *_tabUser, int i);
};