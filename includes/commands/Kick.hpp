# ifndef KICK_HPP
#define KICK_HPP

#include "../IRC.hpp"

class Kick
{
private:
    std::string _user;
    std::string _channel;
    std::string _reason;
public:
    Kick(void);
    Kick(std::string str);
    Kick(Kick const &src);
    ~Kick();

    Kick operator=(Kick const &rhs);
};

#endif