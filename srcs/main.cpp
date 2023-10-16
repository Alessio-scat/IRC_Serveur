# include <iostream>
#include "../includes/IRC.hpp"
#include "../includes/user/User.hpp"

int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    // std::cout << "Hello World !" << std::endl;
    // std::cout << "branch master" << std::endl;
    // std::cout << "Pusssy ganggg !!" << std::endl;
    int sokcetServeur = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer;
    addrServer.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(30000);

    bind(sokcetServeur, (const sockaddr *)&addrServer, sizeof(addrServer));
    printf("bind : %d\n", sokcetServeur);

    listen(sokcetServeur, 5);
    printf("listen.\n");

    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    int socketClient = accept(sokcetServeur, (struct sockaddr *)&addrClient, &csize);
    printf("accept\n");

    printf("client: %d\n", socketClient);
    User user;
    user.setUsername("yo");

    close(socketClient);
    close(sokcetServeur);
    
    return 0;
}