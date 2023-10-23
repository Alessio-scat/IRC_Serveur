#include "../../includes/commands/Topic.hpp"

Topic::Topic(void){}

Topic::Topic(Topic const &src)
{
    *this = src;
}

Topic::Topic(std::string str)
{
    (void)str;
}

Topic::~Topic(){}

Topic Topic::operator=(Topic const &rhs)
{
    if (this == &rhs)
        return (*this);
    this->_msgTopic = rhs._msgTopic;
    this->_channelTopic = rhs._channelTopic;
    return (*this);
}