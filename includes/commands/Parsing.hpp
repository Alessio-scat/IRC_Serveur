# ifndef PARSING_CLASS_HPP
# define PARSING_CLASS_HPP

#include "../IRC.hpp"

class Parsing
{
    private:

    public:
       void whatCommand(char *buffer, User *_tabUser, int i, std::deque<struct pollfd> _pfds); 
};

#endif