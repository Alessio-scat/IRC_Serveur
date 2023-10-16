
#include "../includes/IRC.hpp"
#include "../includes/server/ClientImpl.hpp"
#include "../includes/server/ReceptionHandler.hpp"

int main()
{
    // Création du socket serveur
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Erreur lors de la création du socket serveur");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse et du port pour le serveur
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);  // Port 8080

    // Liaison du socket serveur à l'adresse et au port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Erreur lors de la liaison du socket serveur à l'adresse");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Écoute sur le socket pour les connexions entrantes
    if (listen(serverSocket, 5) == -1) {
        perror("Erreur lors de l'écoute sur le socket serveur");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Serveur en attente de connexions..." << std::endl;

    // Accepte une connexion entrante
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        perror("Erreur lors de l'acceptation de la connexion");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connecté." << std::endl;

    // Ferme les sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}