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

    discussion();

    close(this->serverSocket);
}

void Socket::discussion(void)
{
    std::vector<struct pollfd> clientSockets(this->maxClients + 1);
    // Ajout du socket serveur à la liste des sockets à surveiller
    clientSockets[0].fd = this->serverSocket;
    clientSockets[0].events = POLLIN;

    // AllClient allClients;
    User _tabUser[MAX_USERS];

    while (true)
    {
        //en attente d'un event
        int activity = poll(clientSockets.data(), clientSockets.size(), -1);

        std::cout <<  "Discussion avec le client..." << std::endl;

        if ((activity < 0) && (errno != EINTR))
        {
            std::cerr << "Erreur lors de l'appel à poll" << std::endl;
        }

        if (clientSockets[0].revents & POLLIN) {
            // Nouvelle connexion entrante
            addrSize = sizeof(this->newAddr);
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
                    std::cout << "Client " << i << " : " << this->buffer << std::endl;

                    fillUser(_tabUser, i);
                }
            }
        }
    }
}

void Socket::fillUser(User *_tabUser, int i)
{
    std::string bufferStr(this->buffer);
    std::string nickname, username;

    size_t indexNick = bufferStr.find("NICK");
    size_t indexUser = bufferStr.find("USER");

    int sizeNick = 0;
    int sizeUser = 0;
    if (indexNick != std::string::npos && indexUser != std::string::npos)
    {
        sizeNick = (indexUser - 1) - (indexNick + 4);
        sizeUser = bufferStr.find(" 0 *") - (indexUser + 4);
    }
    nickname = bufferStr.substr(indexNick + 4, sizeNick);
    username = bufferStr.substr(indexUser + 4, sizeUser);
    _tabUser[i].setNickname(nickname);
    _tabUser[i].setUsername(username);
    // std::cout << "Nickname :" << _tabUser[i].getNickname() << std::endl;
    // std::cout << "Username :" << _tabUser[i].getUsername() << std::endl;
}