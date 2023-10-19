#include "../../includes/server/socket.hpp"

Socket::Socket(void)
{
    this->_mdp = "NULL";
    this->_host = 1001;
    this->maxClients = 10;
}

Socket::Socket(std::string host, std::string mdp)
{
    this->_mdp = mdp;
    this->_host = atoi(host.c_str());
    this->maxClients = 10;
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

    // if (password())
        discussion();

    close(this->serverSocket);
}

int Socket::password(void)
{
    // char passwordBuffer[1024];
    // // Demandez au client de saisir un mot de passe
    // send(this->newSocket, "Veuillez entrer le mot de passe : ", 29, 0);

    // // Attendez que le client réponde en recevant le mot de passe
    // int bytesRead = recv(this->newSocket, passwordBuffer, sizeof(passwordBuffer), 0);
    // if (bytesRead <= 0)
    // {
    //     close(this->newSocket);
    //     return (0);
    // }
    // else
    // {
    //     passwordBuffer[bytesRead] = '\0';

    //     // Vérifiez le mot de passe
    //     if (strcmp(passwordBuffer, this->_mdp.c_str()) == 0)
    //     {
    //         std::cout << "Mot de passe correct. Connexion autorisée." << std::endl;

    //         // Autorisez le client à poursuivre en appelant la fonction discussion
    //         return (1);
    //     }
    //     else
    //     {
    //         std::cout << "Mot de passe incorrect. Connexion refusée." << std::endl;
    //         close(this->newSocket);
    //         return (0);
    //     }
    // }
    std::string str;
    std::string mdp;
    size_t pos;
    size_t sizeStr;
    std::istringstream iss(this->buffer);
    while (std::getline(iss, str))
    {
        sizeStr = str.size() - 1;
        // pos = str.find_last_of("PASS");
        pos = str.find("PASS");
        if (pos !=  std::string::npos)
        {
            mdp = str.substr(pos + 5, sizeStr - (pos + 5));
            // std::cout << "|" << mdp << "|" << std::endl;
            if (mdp != this->_mdp)
            {
                std::cout << "<client> :Password incorrect\n";
                return (1);
            }
        }
    }
    return (0);
}

void Socket::discussion(void)
{
    std::vector<struct pollfd> clientSockets(this->maxClients + 1);

    // Ajout du socket serveur à la liste des sockets à surveiller
    clientSockets[0].fd = this->serverSocket;
    clientSockets[0].events = POLLIN;
    // int i = 0;

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
                    if (password())
                    {
                        close(clientSockets[i].fd);
                        clientSockets[i].fd = 0;
                    }
                    this->buffer[bytesRead] = '\0';
                    std::cout << "Client " << i << " : " << this->buffer << std::endl;
                }
            }
        }
    }
}