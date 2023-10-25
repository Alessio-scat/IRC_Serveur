#include "../../includes/Server/Server.hpp"

Server::Server(void)
{
    this->_mdp = "NULL";
    this->_host = 1001;
    this->_pfds.resize(MAXCLIENT + 1);
}

Server::Server(std::string host, std::string mdp)
{
    this->_mdp = mdp;
    this->_host = atoi(host.c_str());
    this->_pfds.resize(MAXCLIENT + 1);
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
        sizeNick = (indexUser - 2) - (indexNick + 4);
        sizeUser = bufferStr.find(" 0 *") - (indexUser + 4);
    }
    nickname = bufferStr.substr(indexNick + 5, sizeNick);
    username = bufferStr.substr(indexUser + 5, sizeUser);
    if (nickname == "")
        return ;
    _tabUser[i].setNickname(nickname);
    _tabUser[i].setUsername(username);
    // std::cout << "Nickname :" << _tabUser[i].getNickname() << std::endl;
    // std::cout << "Username :" << _tabUser[i].getUsername() << std::endl;
}

void Server::Run_Server(void)
{
    _pfds[0].fd = this->serverSocket;
    _pfds[0].events = POLLIN;

    while (true)
    {
        //en attente d'un event

        if (!_pfds.empty())
        {
            if (poll(&_pfds.front(), _pfds.size(), -1) < 0)
                throw std::runtime_error("Error while polling from fd!");
        }

        // event de connexion
        if (_pfds[0].revents & POLLIN)
            connect_client();

        // Gestion des données reçues des clients
        for (int i = 1; i <= MAXCLIENT; i++)
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
                    command.whatCommand(this->buffer, _tabUser, i, _pfds);
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
    for (int i = 1; i <= MAXCLIENT; i++)
    {
        if (_pfds[i].fd == 0)
        {
            _pfds[i].fd = this->newSocket;
            _pfds[i].events = POLLIN;
             break;
        }
    }
}
