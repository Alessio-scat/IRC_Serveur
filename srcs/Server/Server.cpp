#include "../../includes/Server/Server.hpp"
// #include "../../includes/server/socket.hpp"

Server::Server(void)
{
    this->_mdp = "NULL";
    this->_host = 1001;
    this->maxClients = 10;
    this->_pfds.resize(this->maxClients + 1);
}

Server::Server(std::string host, std::string mdp)
{
    this->_mdp = mdp;
    this->_host = atoi(host.c_str());
    this->maxClients = 10;
    this->_pfds.resize(this->maxClients + 1);
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

// void Server::Run_Server(void)
// {
//     std::vector<struct pollfd> clientSockets(this->maxClients + 1);
//     // Ajout du socket serveur à la liste des sockets à surveiller
//     clientSockets[0].fd = this->serverSocket;
//     clientSockets[0].events = POLLIN;

//     while (true)
//     {
//         //en attente d'un event
//         int activity = poll(clientSockets.data(), clientSockets.size(), -1);
//         // password();
//         std::cout <<  "Discussion avec le client..." << std::endl;

//         if ((activity < 0) && (errno != EINTR))
//         {
//             std::cerr << "Erreur lors de l'appel à poll" << std::endl;
//         }

//         if (clientSockets[0].revents & POLLIN) {
//             // Nouvelle connexion entrante
//             this->newSocket = accept(this->serverSocket, (struct sockaddr*)&this->newAddr, &this->addrSize);
//             if (this->newSocket < 0)
//             {
//                 perror("Erreur lors de l'acceptation de la connexion");
//                 exit(1);
//             }

//             std::cout << "Nouvelle connexion, socket FD : " << this->newSocket << std::endl;

//             // Ajout du nouveau socket client à la liste des sockets à surveiller
//             for (int i = 1; i <= this->maxClients; i++) {
//                 if (clientSockets[i].fd == 0)
//                 {
//                     clientSockets[i].fd = this->newSocket;
//                     clientSockets[i].events = POLLIN;
//                     break;
//                 }
//             }
//         }

//         // Gestion des données reçues des clients
//         for (int i = 1; i <= this->maxClients; i++)
//         {
//             if (clientSockets[i].revents & POLLIN)
//             {
//                 int bytesRead = recv(clientSockets[i].fd, this->buffer, sizeof(this->buffer), 0);
//                 if (bytesRead <= 0)
//                 {
//                     close(clientSockets[i].fd);
//                     clientSockets[i].fd = 0;
//                 }
//                 else
//                 {
//                     this->buffer[bytesRead] = '\0';
//                     std::cout << "Client " << i << " : " << std::endl;
//                     std::cout << this->buffer << std::endl;

//                     if (strncmp(this->buffer, "JOIN", 4) == 0)
//                     {
//                         // Extraction du nom du canal (remplacez "JOIN" par le préfixe réel de la commande)
//                         std::string joinCommand(this->buffer);
//                         size_t pos = joinCommand.find("#");
//                         if (pos != std::string::npos)
//                         {
//                             std::string channelName = joinCommand.substr(pos);

//                             // Création et envoi de la commande au serveur IRC
//                             std::string createChannelCommand = "/JOIN " + channelName;
//                             send(clientSockets[i].fd, createChannelCommand.c_str(), createChannelCommand.length(), 0);

//                             std::cout << "Création du canal " << channelName << " !" << std::endl;
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }


/*
        *** Run server test ! ***

    - pfds.begin().base() renvoie un it pointant sur le premier element du vecteur pfds et base() pour obtenir un pointeur sur les structure pour la fonction poll
    - -1 pour signale que la fonction doit etre bloquante --> attendra indefiniment qu'un fd genere un evenement. 
*/
// #include <stdio.h>
// void Server::Run_Server(void)
// {
//     // std::vector<struct pollfd> pfds(MAXCLIENT);
//     // typedef std::vector<struct pollfd>::iterator pfds_it;
//     // pfds[0].fd = this->serverSocket;
//     // pfds[0].events = POLLIN;
//     Command command;
//     pollfd srv = {this->serverSocket, POLLIN, 0};
//     pfds.push_back(srv);

//     while (true)
//     {
//         if (poll(pfds.data(), pfds.size(), -1) < 0)
//             throw std::runtime_error("Error: poll()");

//         for (int i = 1; i < this->maxClients ; i++)
//         {
//             if (pfds[i].revents == 0) // revents == 0 --> Aucun evenement n'a ete detecte donc on pass au fd suivant.
//             {
//                 // std::cout << "Nothing Event" << std::endl;
//                 continue ;
//             }

//             if ((pfds[i].revents & POLLHUP) == POLLHUP) // event de deconnexion
//             {
//                 //gerer la deconnexion
//                 while(1){std::cout << "A client is deconnect" << std::endl;}
//                 break ;
//             }

//             if ((pfds[i].revents & POLLIN) == POLLIN) // fd a genere un evenement de lecture et je verifie que le fd est celui du serveur lui - meme 
//             {
//                 if (pfds[i].fd == this->serverSocket) // ou !=
//                 {
//                      // gerer la nouvelle connexion d'un client
//                     std::cout << "A client is connect" << std::endl;
//                     connect_client();
//                 }
//                 std::cout << "Analyst data of client" << std::endl;
//                 // faire une fonction qui permet juste de traiter les donnes recu du client.
//                 int fd = pfds[i].fd;
//                 std::cout << "fd before: " << fd << std::endl;
//                 Interpret_Data(pfds[i].fd, i, command);
//             }
//         }
//     }
// }

// void Server::connect_client(void)
// {
//     this->newSocket = accept(this->serverSocket, (struct sockaddr*)&this->newAddr, &this->addrSize);
//     if (this->newSocket < 0)
//         throw std::runtime_error("Error: failed fd");

//     pollfd pfd = {this->newSocket, POLLIN, 0};
//     (void)pfd;
// }

// void Server::Interpret_Data(int &fd, int i, Command &command)
// {
//     std::cout << fd << std::endl;
//     User _tabUser[MAX_USERS];
//     int bytesRead = recv(fd, this->buffer, sizeof(this->buffer), 0);
//     if (bytesRead <= 0)
//     {
//         std::cout << "1" << std::endl;
//         close(fd);
//         fd = 0;
//     }
//     else
//     {
//         if (password())
//         {
//             std::cout << "2" << std::endl;
//             close(fd);
//             fd = 0;
//         }

//     fillUser(_tabUser, i);

//     this->buffer[bytesRead] = '\0';
//     command.whatCommand(this->buffer, _tabUser, i);
//     std::cout << "Client " << i << " : " << this->buffer << std::endl;

//     }
    
// }


/*=============================*/

int Server::password(void)
{
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

void Server::fillUser(User *_tabUser, int i)
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
    if (nickname == "")
        return ;
    _tabUser[i].setNickname(nickname);
    _tabUser[i].setUsername(username);
    std::cout << "Nickname :" << _tabUser[i].getNickname() << std::endl;
    std::cout << "Username :" << _tabUser[i].getUsername() << std::endl;
}

void Server::Run_Server(void)
{
    // std::vector<struct pollfd> clientSockets(this->maxClients + 1);
    // Ajout du socket serveur à la liste des sockets à surveiller
    _pfds[0].fd = this->serverSocket;
    _pfds[0].events = POLLIN;
    Command command;
    User _tabUser[MAX_USERS];

    while (true)
    {
        //en attente d'un event

        if (!_pfds.empty())
        {
            if (poll(&_pfds.front(), _pfds.size(), -1) < 0)
                throw std::runtime_error("Error while polling from fd!");
        }

        if (_pfds[0].revents & POLLIN)
        {
            connect_client();
        }

        // Gestion des données reçues des clients
        for (int i = 1; i <= this->maxClients; i++)
        {
            if (_pfds[i].revents & POLLIN)
            {
                int bytesRead = recv(_pfds[i].fd, this->buffer, sizeof(this->buffer), 0);
                if (bytesRead <= 0)
                {
                    close(_pfds[i].fd);
                    _pfds[i].fd = 0;
                }
                else
                {
                    if (password())
                    {
                        close(_pfds[i].fd);
                        _pfds[i].fd = 0;
                    }

                    fillUser(_tabUser, i);

                    this->buffer[bytesRead] = '\0';
                    command.whatCommand(this->buffer, _tabUser, i);
                    std::cout << "Client " << i << " : " << this->buffer << std::endl;

                }
            }
        }
    }
}

void Server::connect_client(void)
{
    // Nouvelle connexion entrante
    addrSize = sizeof(this->newAddr);
    this->newSocket = accept(this->serverSocket, (struct sockaddr*)&this->newAddr, &this->addrSize);
    if (this->newSocket < 0)
        throw std::runtime_error("Error: failed accept()");

    std::cout << "Nouvelle connexion, socket FD : " << this->newSocket << std::endl;

    // Ajout du nouveau socket client à la liste des sockets à surveiller
    for (int i = 1; i <= this->maxClients; i++)
    {
        if (_pfds[i].fd == 0)
        {
            _pfds[i].fd = this->newSocket;
            _pfds[i].events = POLLIN;
             break;
        }
    }
}
