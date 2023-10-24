#pragma once

#include "../IRC.hpp"
#include "../user/User.hpp"
#include "../Server/ErrorValue.hpp"

class Join
{
private:

public:
    Join(void);
    Join(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds);
    Join(Join const &src);
    ~Join();
    Join operator=(Join const &rhs);
    
};
