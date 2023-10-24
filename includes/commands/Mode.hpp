#pragma once

#include "../IRC.hpp"

class Mode
{
private:
    std::string _channelMode;
    std::string _opt;

public:
    Mode(void);
    Mode(std::string str);
    Mode(Mode const &src);
    ~Mode();
    Mode operator=(Mode const &rhs);
    void changeMode(void);
    
};
