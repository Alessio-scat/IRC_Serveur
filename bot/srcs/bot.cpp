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
    std::string user_cmd = "USER " + _name + " 0 * :" + _name + "\r\n";
    std::string nick_cmd = "NICK " + _name + "\r\n";
    std::string pass_cmd = "PASS " + _BotPassword + "\r\n";

    send(_BotSocket, user_cmd.c_str(), user_cmd.length(), 0);
    send(_BotSocket, nick_cmd.c_str(), nick_cmd.length(), 0);
    send(_BotSocket, pass_cmd.c_str(), pass_cmd.length(), 0);

    std::string join_cmd = "JOIN #bot\r\n";
    send(_BotSocket, join_cmd.c_str(), join_cmd.length(), 0);
}

int Bot::Bot_Start()
{
    _BotSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_BotSocket < 0)
    {
        std::cout << "Erreur lors de la création du socket serveur" << std::endl;
        // perror("Erreur lors de la création du socket serveur");
        return 1;
    }

    _BotServerAddr.sin_family = AF_INET;
    _BotServerAddr.sin_port = htons(_BotHost);
    _BotServerAddr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    if (setsockopt(_BotSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) < 0)
    {
        std::cout << "Erreur lors de la configuration de SO_REUSEADDR" << std::endl;
        perror("Erreur lors de la configuration de SO_REUSEADDR");
        return 1;
    }

    /*
    connect() est utilisée par le client pour établir une connexion avec un serveur, 
    la fonction bind() est utilisée par le serveur pour associer une adresse (IP et port) 
    à un socket avant d'écouter les connexions entrantes.
    */
    if (connect(_BotSocket, (struct sockaddr*)&_BotServerAddr, sizeof(_BotServerAddr)) < 0)
    {
        std::cout << "Error: connection in server" << std::endl;
        return 1;
    }

    identificationBotInServer();

    return 0;
}


bool searchWordInBot(const std::string& input, const std::string &target)
{
    std::cout << "inputBOT   |" << input << "|" << std::endl;
    std::string::size_type pos = input.find(target);
    // return pos != std::string::npos;
    if (pos != std::string::npos)
        return 0;
    else
        return 1;
}

int Bot::Bot_Run()
{
    while (1) 
    {
        std::cout << "testtttt" << std::endl;
        char buffer[1024];
        // int bytes_received = recv(_BotSocket, buffer, 1024 - 1, 0);
        int bytes_received = recv(_BotSocket, buffer, 1024, 0);
        if (bytes_received <= 0) 
        {
            break;
        }

        // buffer[bytes_received - 1] = '\0';
        buffer[bytes_received] = '\0';
        // std::string response(buffer);

        if (searchWordInBot(buffer, "MONSTRE") == 0) 
        {
            std::cout << "1111111111111111" << std::endl;
            std::string monstre_cmd = ":bot PRIVMSG #bot :DOUBLE MONSTRE\r\n";
            send(_BotSocket, monstre_cmd.c_str(), monstre_cmd.length(), 0);
        } 

        if (searchWordInBot(buffer, "NAH") == 0)
        {
            std::string nah_cmd = "PRIVMSG #bot :DOUBLE NAH\r\n";
            send(_BotSocket, nah_cmd.c_str(), nah_cmd.length(), 0);
        } 

        if (searchWordInBot(buffer, "COUCOU") == 0)
        {
            std::string coucou_cmd = "PRIVMSG #bot :DOUBLE COUCOU\r\n";
            send(_BotSocket, coucou_cmd.c_str(), coucou_cmd.length(), 0);
        } 
    }

    return 0;
}

int Bot::Bot_Stop()
{
    close (_BotSocket);
    return 0;
}