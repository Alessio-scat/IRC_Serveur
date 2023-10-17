# include <iostream>
#include "../includes/IRC.hpp"
#include "../includes/user/User.hpp"

int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    socket();
    std::cout << "Hello World !" << std::endl;
    return 0;
}