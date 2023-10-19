#include "../../includes/Server/Server.hpp"

Server::Server(void)
{
    this->_mdp = "NULL";
    this->_host = 1001;
    this->maxClients = 10;
}

Server::Server(std::string host, std::string mdp)
{
    this->_mdp = mdp;
    this->_host = atoi(host.c_str());
    this->maxClients = 10;
}

Server::Server(Server const &src)
{
    *this = src;
}

Server::~Server(){}

Server Server::operator=(Server const &assignment)
{
    if (this == &assignment)
        return (*this);
    this->_mdp = assignment._mdp;
    this->_host = assignment._host;
    return(*this);
}

void Server::Start_Server(void)
{
    // Création d'un socket serveur IPv4 et TCP
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket < 0)
    {
        perror("Erreur lors de la création du socket serveur");
        exit(1);
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->_host);
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    // Pour éviter l'erreur "Address already use"
    int opt = 1;
    if (setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) < 0)
    {
        perror("Erreur lors de la configuration de SO_REUSEADDR");
        exit(1);
    }

    // Liaison du socket serveur à une adresse IP et un port
    if (bind(this->serverSocket, (struct sockaddr*)&this->serverAddr, sizeof(this->serverAddr)) < 0)
    {
        perror("Erreur lors de la liaison du socket serveur");
        exit(1);
    }

    // Attente de connexions entrantes 10 maximum
    listen(this->serverSocket, 10);
    std::cout << "En attente de connexions..." << std::endl;

    Run_Server();

    close(this->serverSocket);
}

void Server::Run_Server(void)
{
    std::vector<struct pollfd> clientSockets(this->maxClients + 1);
    // Ajout du socket serveur à la liste des sockets à surveiller
    clientSockets[0].fd = this->serverSocket;
    clientSockets[0].events = POLLIN;

    while (true)
    {
        //en attente d'un event
        int activity = poll(clientSockets.data(), clientSockets.size(), -1);
        // password();
        std::cout <<  "Discussion avec le client..." << std::endl;

        if ((activity < 0) && (errno != EINTR))
        {
            std::cerr << "Erreur lors de l'appel à poll" << std::endl;
        }

        if (clientSockets[0].revents & POLLIN) {
            // Nouvelle connexion entrante
            this->newSocket = accept(this->serverSocket, (struct sockaddr*)&this->newAddr, &this->addrSize);
            if (this->newSocket < 0)
            {
                perror("Erreur lors de l'acceptation de la connexion");
                exit(1);
            }

            std::cout << "Nouvelle connexion, socket FD : " << this->newSocket << std::endl;

            // Ajout du nouveau socket client à la liste des sockets à surveiller
            for (int i = 1; i <= this->maxClients; i++) {
                if (clientSockets[i].fd == 0)
                {
                    clientSockets[i].fd = this->newSocket;
                    clientSockets[i].events = POLLIN;
                    break;
                }
            }
        }

        // Gestion des données reçues des clients
        for (int i = 1; i <= this->maxClients; i++)
        {
            if (clientSockets[i].revents & POLLIN)
            {
                int bytesRead = recv(clientSockets[i].fd, this->buffer, sizeof(this->buffer), 0);
                if (bytesRead <= 0)
                {
                    close(clientSockets[i].fd);
                    clientSockets[i].fd = 0;
                }
                else
                {
                    this->buffer[bytesRead] = '\0';
                    std::cout << "Client " << i << " : " << std::endl;
                    std::cout << this->buffer << std::endl;

                    if (strncmp(this->buffer, "JOIN", 4) == 0)
                    {
                        // Extraction du nom du canal (remplacez "JOIN" par le préfixe réel de la commande)
                        std::string joinCommand(this->buffer);
                        size_t pos = joinCommand.find("#");
                        if (pos != std::string::npos)
                        {
                            std::string channelName = joinCommand.substr(pos);

                            // Création et envoi de la commande au serveur IRC
                            std::string createChannelCommand = "/JOIN " + channelName;
                            send(clientSockets[i].fd, createChannelCommand.c_str(), createChannelCommand.length(), 0);

                            std::cout << "Création du canal " << channelName << " !" << std::endl;
                        }
                    }
                }
            }
        }
    }
}


/*
        *** Run server test ! ***

    - pfds.begin().base() renvoie un it pointant sur le premier element du vecteur pfds et base() pour obtenir un pointeur sur les structure pour la fonction poll
    - -1 pour signale que la fonction doit etre bloquante --> attendra indefiniment qu'un fd genere un evenement. 
*/
// void Server::Run_Server(void)
// {
//     std::vector<struct pollfd> pfds;
//     typename std::vector<struct pollfd>::iterator pfd_it;

//     while (true)
//     {
//         if (poll(pfds.begin().base(), pfds.size(), -1) < 0)
//             throw std::runtime_error("Error: poll()");

//         for (pfd_it it = pfds.begin(); it != pfds.end(); it++)
//         {
//             if (it->revents == 0) // revents == 0 --> Aucun evenement n'a ete detecte donc on pass au fd suivant.
//                 continue ;

//             if ((it->revents & POLLHUB) == POLLHUB) // event de deconnexion
//             {
//                 //gerer la deconnexion
//                 break ;
//             }

//             if ((it->revents & POLLIN) == POLLIN) // fd a genere un evenement de lecture et je verifie que le fd est celui du serveur lui - meme 
//             {
//                 if (it->fd == this->serverSocket) // ou !=
//                 {
//                      // gerer la nouvelle connexion d'un client
//                 }
//                 // faire une fonction qui permet juste de traiter les donnes recu du client.
//             }
//         }
//     }
// }