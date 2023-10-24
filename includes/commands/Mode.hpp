#pragma once

#include "../IRC.hpp"

class Mode
{
private:

public:
    Mode(void);
    Mode(std::string str);
    Mode(Mode const &src);
    ~Mode();
    Mode operator=(Mode const &rhs);
    
};
