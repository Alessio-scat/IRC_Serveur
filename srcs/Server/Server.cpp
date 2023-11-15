#include "../../includes/Server/Server.hpp"

Server::Server(void)
{
    this->_mdp = "NULL";
    this->_host = 1001;
    this->_pfds.resize(MAX_USERS + 1);
}

Server::Server(std::string host, std::string mdp)
{
    this->_mdp = mdp;
    this->_host = atoi(host.c_str());
    this->_pfds.resize(MAX_USERS + 1);
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
            if (sizeStr <= 3)
                return (1);
            mdp = str.substr(pos + 5, sizeStr + 1 - (pos + 5));
            ft_trim(mdp);
            // std::cout << "MDP: |" << mdp << "|" << std::endl;
            if (mdp != this->_mdp)
            {
                std::cout << "<client> :Password incorrect\n";
                return (1);
            }
        }
    }
    return (0);
}

// void Server::fillUser(User *_tabUser, int i)
// {
//     std::string bufferStr(this->buffer);
//     std::string nickname, username;

//     size_t indexNick = bufferStr.find("NICK");
//     size_t indexUser = bufferStr.find("USER");

//     int sizeNick = 0;
//     int sizeUser = 0;

//     if (indexNick != std::string::npos) {
//         // sizeNick = bufferStr.find(" ", indexNick + 5) - (indexNick + 5);
//         i = indexNick + 5;
//         while (bufferStr[i] > 32 && bufferStr[i])
//         {
//             sizeNick++;
//             i++;
//         }
//         nickname = bufferStr.substr(indexNick + 5, sizeNick);
//     }

//     if (indexUser != std::string::npos) {
//         sizeUser = bufferStr.find(" ", indexUser + 5) - (indexUser + 5);
//         username = bufferStr.substr(indexUser + 5, sizeUser);
//     }

//     if (!nickname.empty()) {
//         _tabUser[i].setNickname(nickname);
//         std::cout << "Nickname :" << "|" << _tabUser[i].getNickname() << "|" << std::endl;
//     }

//     if (!username.empty()) {
//         _tabUser[i].setUsername(username);
//         std::cout << "Username :" << "|" << _tabUser[i].getUsername() << "|" << std::endl;
//     }
// }

void Server::fillUser(User *_tabUser, int i)
{
    std::string bufferStr(this->buffer);
    std::string nickname, username;

    size_t indexNick = bufferStr.find("NICK");
    size_t indexUser = bufferStr.find("USER");

    int sizeNick = 0;
    int sizeUser = 0;
    if (_tabUser[i].getNickname() != "" && _tabUser[i].getUsername() != "")
        return;
    if (indexNick != std::string::npos && indexUser != std::string::npos)
    {
        sizeNick = (indexUser - 2) - (indexNick + 4) - 1;
        sizeUser = bufferStr.find(" 0 *") - (indexUser + 4) - 1;
        nickname = bufferStr.substr(indexNick + 5, sizeNick + 1);
        username = bufferStr.substr(indexUser + 5, sizeUser + 1);
        ft_trim(nickname);
        ft_trim(username);
        if (nickname == "")
            return ;
        _tabUser[i].setNickname(nickname);
        _tabUser[i].setUsername(username);
        std::cout << "Nickname :" << "|" << _tabUser[i].getNickname() << "|" << std::endl;
        std::cout << "Username :" << "|" << _tabUser[i].getUsername() << "|" << std::endl;
        return ;
    }
    if (indexNick != std::string::npos) {
        std::cout << GREEN << "\nbuffer : " << this->buffer << "||" <<std::endl;
        sizeNick = bufferStr.find(" ", indexNick + 5) - (indexNick + 5);
        nickname = bufferStr.substr(indexNick + 5, sizeNick);
        ft_trim(nickname);
        _tabUser[i].setNickname(nickname);
        std::cout << "Nickname :" << "|" << _tabUser[i].getNickname() << "|\n" << std::endl;
        return;
    }

    if (indexUser != std::string::npos) {
        std::cout << GREEN << "\nbuffer : " << this->buffer << "||\n" <<std::endl;
        sizeUser = bufferStr.find(" ", indexUser + 5) - (indexUser + 5);
        username = bufferStr.substr(indexUser + 5, sizeUser);
        ft_trim(username);
        _tabUser[i].setUsername(username);
        std::cout << "Username :" << "|" << _tabUser[i].getUsername() << "|" << std::endl;
        return;
    }
}

char* stringToCharArray(const std::string& str) {
    char* result = new char[str.length() + 1]; // +1 for null-terminator
    std::strcpy(result, str.c_str());
    return result;
}

void Server::Run_Server(void)
{
    _pfds[0].fd = this->serverSocket;
    _pfds[0].events = POLLIN;
    Channel channel;
    for (int j = 1; j < MAX_USERS; j++)
        _tabUser[j].setBufferSignal("");
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
        for (int i = 1; i < MAX_USERS; i++)
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
                    std::cout << "bytesRead : " << bytesRead << std::endl;
                    if (password())
                    {
                        close(_pfds[i].fd);
                        _pfds[i].fd = 0;
                    }
                    std::cout << GREEN << i << RESET << std::endl;
                    fillUser(_tabUser, i); 
                    this->buffer[bytesRead] = '\0';
                    std::cout << CURSIVE << UNDER << "buffer" << RESET << CURSIVE << ": " << "|" << this->buffer << "|" << RESET << std::endl;
                    if (static_cast<std::string>(this->buffer).find("\n") != std::string::npos)
                    {
                        
                        if (_tabUser[i].getBufferSignal() != "")
                        {
                            //BUFFER SIGNAL EST REMPLI IL FAUT CONCATENER
                            std::cout << "BUFFER SIGNAL : |" << _tabUser[i].getBufferSignal() << "|" << std::endl;
                            std::string toAppend = _tabUser[i].getBufferSignal();
                            size_t newSize = toAppend.size() + strlen(this->buffer) + 1;
                            char* newBuffer = new char[newSize];
                            std::strcpy(newBuffer, toAppend.c_str());
                            std::strcat(newBuffer, this->buffer);
                            std::cout << "newBuffer: " << newBuffer << std::endl;

                            _tabUser[i].setBufferSignal("");
                            std::cout << GREEN << "BUFFER" << RESET << ": |" << this->buffer << "|" << std::endl;
                            std::cout << GREEN << "SIGNAL" << RESET << ": |" << _tabUser[i].getBufferSignal() << "|" << std::endl;
                            if (_tabUser[i].getNickname() != "" && _tabUser[i].getUsername() != "")
                            command.whatCommand(newBuffer, _tabUser, i, _pfds, channel);

                        }
                        
                        _tabUser[i].setBufferSignal("");
                        std::cout << GREEN << "BUFFER" << RESET << ": |" << this->buffer << "|" << std::endl;
                        std::cout << GREEN << "SIGNAL" << RESET << ": |" << _tabUser[i].getBufferSignal() << "|" << std::endl;
                        if (_tabUser[i].getNickname() != "" && _tabUser[i].getUsername() != "")
                            command.whatCommand(this->buffer, _tabUser, i, _pfds, channel);
                    }
                    else
                    {
                        std::cout << "Ya eu un ctrl-D" << std::endl;
                        _tabUser[i].setBufferSignal(this->buffer);
                    }
                }
                _pfds[i].revents |= POLLOUT;
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
    for (int i = 1; i < MAX_USERS; i++)
    {
        if (_pfds[i].fd == 0)
        {
            _pfds[i].fd = this->newSocket;
            _pfds[i].events = POLLIN;
             break;
        }
    }
}
