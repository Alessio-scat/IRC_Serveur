#pragma once

# include "../includes/IRC.hpp"
# include "../Channel/Channel.hpp"

class Server
{

private:
    std::string _mdp;
    unsigned int _host;
    int serverSocket;
    int newSocket;                 // pour le nouveau socket client lorsqu'une connexion est acceptée
    struct sockaddr_in serverAddr; // pour stocker les info du serveur
    struct sockaddr_in newAddr;    // et du client
    char buffer[1024];             // pour stocker les données reçues des clients
    socklen_t addrSize;
    int maxClients; // Nombre maximal de clients que le serveur peut gérer

    /*Test Creation Channel*/
    std::vector<Channel *> _channel;

public:
    Server(void);
    Server(Server const &src);
    Server(std::string host, std::string mdp);
    ~Server();
    Server operator=(Server const &assigment);

    void Start_Server(void);
    void Run_Server(void);
    void connect_client(void);
    void Interpret_Data(int fd);
    int password(void);

    /*Test Creation Channel*/
    Channel *creation_Channel();
};