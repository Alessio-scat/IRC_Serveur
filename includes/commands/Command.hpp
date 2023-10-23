# ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../IRC.hpp"
#include "Kick.hpp"
#include "Invite.hpp"
#include "Topic.hpp"

class Command
{
private:
    /* data */
public:
    Command(/* args */);
    Command(Command const &src);
    ~Command();

    Command operator=(Command const &rhs);

    void whatCommand(char *buffer, User *_tabUser, int i);
};

#endif