#pragma once

#include "../IRC.hpp"

class Socket
{

private:
    std::string _mdp;
    unsigned int _host;
    int serverSocket;
    int newSocket;        // pour le nouveau socket client lorsqu'une connexion est acceptée
    struct sockaddr_in serverAddr;   //pour stocker les info du serveur
    struct sockaddr_in newAddr;    //et du client
    char buffer[1024];   //pour stocker les données reçues des clients
    socklen_t addrSize;
    int maxClients; // Nombre maximal de clients que le serveur peut gérer

public:
    Socket(void);
    Socket(Socket const &src);
    Socket(std::string host, std::string mdp);
    ~Socket();
    Socket operator=(Socket const &assigment);

    void connect(void);
    void discussion(void);
    int password(void);

};