# include <iostream>
#include "../includes/IRC.hpp"
#include "../includes/Server/Server.hpp"
#include "../includes/IRC.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage: ./ircserv [host] [password]" << std::endl;
        return 1;
    }
    Server server = Server(av[1], av[2]);
    server.Start_Server();
    std::cout << "Hello World !" << std::endl;
    return 0;
}