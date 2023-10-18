#include "../../includes/server/Server.hpp"

Server::Server(void){}

Server::Server(Server const &src)
{
    *this = src;
}

Server::Server(std::string host, std::string mdp):_mdp(mdp)
{
    this->_host = atoi(host.c_str());
}

Server::~Server(){}

Server Server::operator=(Server const &rhs)
{
    (void)rhs;
    return (*this);
}

void Server::connect(void)
{
    // int sokcetServeur = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in addrServer;
    // addrServer.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
    // addrServer.sin_family = AF_INET;
    // addrServer.sin_port = htons(30000);

    // bind(sokcetServeur, (const sockaddr *)&addrServer, sizeof(addrServer));
    // printf("bind : %d\n", sokcetServeur);

    // listen(sokcetServeur, 5);
    // printf("listen.\n");

    // struct sockaddr_in addrClient;
    // socklen_t csize = sizeof(addrClient);
    // int socketClient = accept(sokcetServeur, (struct sockaddr *)&addrClient, &csize);
    // printf("accept\n");

    // printf("client: %d\n", socketClient);
    // User user;
    // user.setUsername("yo");
    // send(socketClient, &user, sizeof(user), 0);
    // while(1)
    // {

    // }
    // close(socketClient);
    // close(sokcetServeur);

    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char buffer[1024];

    // Création d'un socket serveur
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        perror("Erreur lors de la création du socket serveur");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->_host);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Liaison du socket serveur à une adresse IP et un port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Erreur lors de la liaison du socket serveur");
        exit(1);
    }

    // Attente de connexions entrantes
    listen(serverSocket, 10);
    std::cout << "En attente de connexions..." << std::endl;

    int maxClients = 5; // Nombre maximal de clients que le serveur peut gérer
    std::vector<struct pollfd> clientSockets(maxClients + 1);

    // Ajout du socket serveur à la liste des sockets à surveiller
    clientSockets[0].fd = serverSocket;
    clientSockets[0].events = POLLIN;

    while (true)
    {
        int activity = poll(clientSockets.data(), clientSockets.size(), -1);

        if ((activity < 0) && (errno != EINTR))
        {
            std::cerr << "Erreur lors de l'appel à poll" << std::endl;
        }

        if (clientSockets[0].revents & POLLIN) {
            // Nouvelle connexion entrante
            newSocket = accept(serverSocket, (struct sockaddr*)&newAddr, &addrSize);
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
    close(serverSocket);
}