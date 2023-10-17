# include <iostream>
#include "../includes/IRC.hpp"
#include "../includes/user/User.hpp"
#include "../includes/server/socket.hpp"

int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    Socket server = Socket();
    server.connect();
    std::cout << "Hello World !" << std::endl;
    return 0;
}