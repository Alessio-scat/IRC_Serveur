# ifndef KICK_HPP
#define KICK_HPP

#include "../IRC.hpp"
#include "../user/User.hpp"
#include "../server/ErrorValue.hpp"

class Kick
{
private:
    std::string _user;
    std::string _channel;
    std::string _reason;
public:
    Kick(void);
    Kick(std::string str, User &user);
    Kick(Kick const &src);
    ~Kick();

    Kick operator=(Kick const &rhs);
};

#endif