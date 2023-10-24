# include <iostream>
#include "../includes/IRC.hpp"
#include "../includes/user/User.hpp"
#include "../includes/Server/Server.hpp"
#include "../includes/user/AllClient.hpp"
#include "../includes/Server/Server.hpp"
#include "../includes/IRC.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage: ./ircserv [host] [password]" << std::endl;
        return 1;
    }

    try
    {
        Server server = Server(av[1], av[2]);
        server.Start_Server();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}