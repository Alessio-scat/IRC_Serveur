# include "../includes/bot.hpp"

Bot::Bot(){}

Bot::Bot(Bot const &src){(void)src;}

Bot Bot::operator=(Bot const &rhs){(void)rhs;return(*this);}

Bot::~Bot(){}

Bot::Bot(const std::string &name, int host, std::string password, const std::string &ip):
    _name(name),
    _BotHost(host),
    _BotPassword(password),
    _BotIp(ip)
{}

void Bot::identificationBotInServer()
{
    // std::string user_cmd = "USER " + _name + " 0 * :" + _name + "\r\n";
    std::string user_cmd = "USER " + _name + " \r\n";
    std::string nick_cmd = "NICK " + _name + "\r\n";
    std::string pass_cmd = "PASS " + _BotPassword + "\r\n";

    send(_BotSocket, user_cmd.c_str(), user_cmd.length(), 0);
    usleep(1000);
    send(_BotSocket, nick_cmd.c_str(), nick_cmd.length(), 0);
    usleep(1000);
    send(_BotSocket, pass_cmd.c_str(), pass_cmd.length(), 0);
    usleep(1000);

    std::string join_cmd = "JOIN #bot\r\n";
    send(_BotSocket, join_cmd.c_str(), join_cmd.length(), 0);
}

int Bot::Bot_Start()
{
    //créer une nouvelle socket, qui est un point d'extrémité pour envoyer et recevoir des données sur un réseau.
    _BotSocket = socket(AF_INET, SOCK_STREAM, 0);  
    if (_BotSocket < 0)
    {
        std::cout << "Erreur lors de la création du socket serveur" << std::endl;
        // perror("Erreur lors de la création du socket serveur");
        return 1;
    }

    //Configure l'adresse du seveur
    _BotServerAddr.sin_family = AF_INET;//indique que l'adresse est une adresse IPv4
    _BotServerAddr.sin_port = htons(_BotHost);
    _BotServerAddr.sin_addr.s_addr = INADDR_ANY; // indique que la socket sera liée à toutes les adresses IP disponibles sur la machine hôte

    //Etablir une connexion entre une socket et une adresse specifique 
    if (connect(_BotSocket, (const struct sockaddr*)&_BotServerAddr, sizeof(_BotServerAddr)) < 0)
    {
        std::cout << "Error: connection in server" << std::endl;
        return 1;
    }

    identificationBotInServer();

    if (Bot_Run() == 1)
        return 1;

    return 0;
}

void ft_trim(std::string &str)
{
    size_t start = 0;
    size_t end = str.length() - 1;

    while (start <= end && std::isspace(str[start]))
        start++;
    while (end >= start && std::isspace(str[end]))
        end--;
    str = str.substr(start, end - start + 1);
}

bool searchWordInBot(std::string& input, const std::string &target)
{
    // ft_trim(input);
    std::cout << "inputBOT   |" << input << "||||" << std::endl;
    std::string::size_type pos = input.find(target);
    // return pos != std::string::npos;
    if (pos != std::string::npos)
        return true ;
    else
        return false;
}

int Bot::Bot_Run()
{
    char buffer[1024];
    while (1) 
    {
        // std::cout << "1111111111111111111" << std::endl;
        // int bytes_received = recv(_BotSocket, buffer, 1024 - 1, MSG_DONTWAIT);
        int bytes_received = recv(_BotSocket, buffer, 1024 - 1, 0);
        // std::cout << "2222222222222222222" << std::endl;
        // int bytes_received = recv(_BotSocket, buffer, sizeof(buffer), 0);
        // if (bytes_received <= 0) 
        // {
        //     std::cout << "testtttt" << std::endl;
        //     break;
        // }
        if (bytes_received > 0)
        {
            usleep(1000);
            buffer[bytes_received] = '\0';
            std::string strBuffer(buffer);
            std::cout << buffer << std::endl;

            if (searchWordInBot(strBuffer, "MONSTRE") == true) 
            {
                std::cout << "ooooooooooooooooooo" << std::endl;
                std::string monstre_cmd = "PRIVMSG #bot :DOUBLE MONSTRE\r\n";
                send(_BotSocket, monstre_cmd.c_str(), monstre_cmd.length(), 0);
            } 

            if (searchWordInBot(strBuffer, "NAH") == true)
            {
                std::string nah_cmd = "PRIVMSG #bot :DOUBLE NAH\r\n";
                send(_BotSocket, nah_cmd.c_str(), nah_cmd.length(), 0);
            } 

            if (searchWordInBot(strBuffer, "COUCOU") == true)
            {
                std::string coucou_cmd = "PRIVMSG #bot :DOUBLE COUCOU\r\n";
                send(_BotSocket, coucou_cmd.c_str(), coucou_cmd.length(), 0);
            } 
        }
        else if (bytes_received < 0) 
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK) 
            {
                continue;
            } 
            else 
            {
                std::cerr << "Erreur de reception: " << strerror(errno) << std::endl;
                break;
            }
        }
        else 
        {
            std::cout << "Le serveur a fermé la connexion." << std::endl;
            break;
        }
    }

    return 0;
}

/*
    EAGAIN : Signifie "try again" (réessayez). Ce code d'erreur est utilisé pour indiquer 
    qu'aucune donnée n'est disponible pour le moment et que vous devriez réessayer ultérieurement.

    EWOULDBLOCK : C'est souvent synonyme de EAGAIN, en particulier dans le contexte des sockets. 
    Il indique également que l'opération sur une socket non bloquante ne peut pas être complétée immédiatement et devrait être réessayée plus tard.
*/

int Bot::Bot_Stop()
{
    close (_BotSocket);
    return 0;
}