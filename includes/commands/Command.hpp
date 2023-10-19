# ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../IRC.hpp"

class Command
{
private:
    /* data */
public:
    Command(/* args */);
    Command(Command const &src);
    ~Command();

    Command operator=(Command const &rhs);

    void whatCommand(char *buffer);
};

#endif