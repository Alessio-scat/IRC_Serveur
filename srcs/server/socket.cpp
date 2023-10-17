#include "../../includes/server/socket.hpp"

Socket::Socket(void)
{
    this->_mdp = "NULL";
    this->_host = 0;
}

Socket::Socket(std::string host, std::string mdp)
{
    this->_mdp = mdp;
    this->_host = atoi(host.c_str());
}

Socket::Socket(Socket const &src)
{
    *this = src;
}

Socket::~Socket(){}

Socket Socket::operator=(Socket const &assignment)
{
    if (this == &assignment)
        return (*this);
    this->_mdp = assignment._mdp;
    this->_host = assignment._host;
    return(*this);
}

void Socket::connect(void)
{
    int newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char buffer[1024];

    // Création d'un socket serveur IPv4 et TCP
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket < 0)
    {
        perror("Erreur lors de la création du socket serveur");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->_host);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    int opt = 1;
    if (setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) < 0)
    {
        perror("Erreur lors de la configuration de SO_REUSEADDR");
        exit(1);
    }

    // Liaison du socket serveur à une adresse IP et un port
    if (bind(this->serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Erreur lors de la liaison du socket serveur");
        exit(1);
    }

    // Attente de connexions entrantes 10 maximum
    listen(this->serverSocket, 10);
    std::cout << "En attente de connexions..." << std::endl;

    int maxClients = 5; // Nombre maximal de clients que le serveur peut gérer
    std::vector<struct pollfd> clientSockets(maxClients + 1);

    // Ajout du socket serveur à la liste des sockets à surveiller
    clientSockets[0].fd = this->serverSocket;
    clientSockets[0].events = POLLIN;

    while (true)
    {
        //en attente d'un event
        int activity = poll(clientSockets.data(), clientSockets.size(), -1);

        if ((activity < 0) && (errno != EINTR))
        {
            std::cerr << "Erreur lors de l'appel à poll" << std::endl;
        }

        if (clientSockets[0].revents & POLLIN) {
            // Nouvelle connexion entrante
            newSocket = accept(this->serverSocket, (struct sockaddr*)&newAddr, &addrSize);
            if (newSocket < 0)
            {
                perror("Erreur lors de l'acceptation de la connexion");
                exit(1);
            }

            std::cout << "Nouvelle connexion, socket FD : " << newSocket << std::endl;

            // Ajout du nouveau socket client à la liste des sockets à surveiller
            for (int i = 1; i <= maxClients; i++) {
                if (clientSockets[i].fd == 0)
                {
                    clientSockets[i].fd = newSocket;
                    clientSockets[i].events = POLLIN;
                    break;
                }
            }
        }

        // Gestion des données reçues des clients
        for (int i = 1; i <= maxClients; i++)
        {
            if (clientSockets[i].revents & POLLIN)
            {
                int bytesRead = recv(clientSockets[i].fd, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0)
                {
                    close(clientSockets[i].fd);
                    clientSockets[i].fd = 0;
                }
                else
                {
                    buffer[bytesRead] = '\0';
                    std::cout << "Client " << i << " : " << buffer << std::endl;
                }
            }
        }
    }
    close(this->serverSocket);
}