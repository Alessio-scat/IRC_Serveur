#include "../../includes/commands/Mode.hpp"

Mode::Mode(void){}

Mode::Mode(Mode const &src)
{
    *this = src;
}

Mode::Mode(std::string str)
{
    (void)str;
}

Mode::~Mode()
{
}

Mode Mode::operator=(Mode const &rhs)
{
    if (this == &rhs)
        return (*this);
    // this->_nickMode = rhs._nickMode;
    // this->_channelMode = rhs._channelMode;
    return (*this);
}
