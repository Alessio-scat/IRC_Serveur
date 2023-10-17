#pragma once

#include "../includes/IRC.hpp"

class Socket
{

private:
    std::string _mdp;
    unsigned int _host;
    int serverSocket;

public:
    Socket(void);
    Socket(Socket const &src);
    Socket(std::string host, std::string mdp);
    ~Socket();
    Socket operator=(Socket const &assigment);

    void connect(void);

};