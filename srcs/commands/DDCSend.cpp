#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"
# include "../../includes/Server/Server.hpp"
# include "../../includes/Utils.hpp"

DDCSend::DDCSend(){}
DDCSend::~DDCSend(){}

void DDCSend::execute_cmd(std::string str){(void)str;}

void DDCSend::execute_cmd(const std::string& dccCommand, std::string& fileName, std::deque<struct pollfd> _pfds, User* _tabUser, int i)
{
    std::cout << "In command DDCSEND !!" << std::endl; 
    std::istringstream iss(dccCommand);
    std::string token;
    size_t pos = 0;

    // Exemple de format DCC SEND : "DCC SEND <filename> <ip> <port> <filesize>"
    while (std::getline(iss, token, ' '))
    {
        pos++;
        if (pos == 3){ // Nom de fichier
            fileName = token;
            break;
        }
    }

    handleFileTransfer(fileName, _tabUser, i, _pfds);
}

// void parseDCCSendCommand(const std::string& dccCommand, std::string& ipAddress, int& port, std::string& fileName) {
//     std::istringstream iss(dccCommand);
//     std::string token;
//     size_t pos = 0;

//     // Exemple de format DCC SEND : "DCC SEND <filename> <ip> <port> <filesize>"
//     while (std::getline(iss, token, ' ')) {
//         pos++;
//         if (pos == 3) { // Nom de fichier
//             fileName = token;
//         } else if (pos == 4) { // Adresse IP (en format décimal)
//             unsigned long ip = std::stoul(token);
//             ipAddress = std::to_string((ip >> 24) & 0xFF) + '.' +
//                         std::to_string((ip >> 16) & 0xFF) + '.' +
//                         std::to_string((ip >> 8) & 0xFF) + '.' +
//                         std::to_string(ip & 0xFF);
//         } else if (pos == 5) { // Port
//             port = std::stoi(token);
//             break;
//         }
//     }
// }

void DDCSend::handleFileTransfer(const std::string& fileName, User* _tabUser, int i ,std::deque<struct pollfd> _pfds) {
    // Cette fonction doit être adaptée selon que votre serveur agit comme un intermédiaire
    // ou simplement facilite la mise en relation des clients pour le transfert de fichier.
    
    // Exemple: envoi d'une notification au client pour accepter le fichier.
    // La logique réelle dépendra de la manière dont votre serveur gère les communications client.
    (void)_tabUser;
    std::string message = "DCC SEND request for file: " + fileName;
    send(_pfds[i].fd, message.c_str(), message.length(), 0);
    // (void)i;
    // writeInfd(DDCSEND(fileName), y, _pfds);
}