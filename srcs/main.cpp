# include <iostream>
#include "../includes/IRC.hpp"
#include "../includes/user/User.hpp"
#include "../includes/server/socket.hpp"

#include "../includes/IRC.hpp"
#include "../includes/server/ClientImpl.hpp"
#include "../includes/server/ReceptionHandler.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage: ./ircserv [host] [password]" << std::endl;
        return 1;
    }
    Socket server = Socket(av[1], av[2]);
    server.connect();
    std::cout << "Hello World !" << std::endl;
    return 0;
}