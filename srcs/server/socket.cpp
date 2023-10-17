#include "../../includes/IRC.hpp"

void socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
    {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error setting SO_REUSEADDR" << std::endl;
        close(sockfd);
        return;
    }
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(4001);
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Error binding" << std::endl;
        close(sockfd);
        return;
    }
    std::cout << "SOCKFD " << sockfd << std::endl;
    if (listen(sockfd, 2) < 0)
    {
        std::cerr << "Error listening" << std::endl;
        close(sockfd);
        return;
    }
    struct sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int clientSocket = accept(sockfd, (struct sockaddr*)&client, &clientSize);
    if (clientSocket < 0)
    {
        std::cerr << "Error accepting client" << std::endl;
        close(sockfd);
        return;
    }
    std::cout << "CLIENT " << clientSocket << std::endl;
    close(clientSocket);
    close(sockfd);
}