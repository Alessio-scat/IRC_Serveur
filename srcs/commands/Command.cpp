#include "../../includes/commands/Command.hpp"

Command::Command(/* args */)
{
}

Command::Command(Command const &src)
{
   *this = src; 
}

Command::~Command()
{
}

Command Command::operator=(Command const &rhs)
{
    (void)rhs;
    return (*this);
}

void Command::whatCommand(char *buffer)
{
    std::cout << buffer << std::endl;
}