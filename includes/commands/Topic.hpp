#pragma once

#include "../IRC.hpp"

class Topic
{
private:
    std::string _channelTopic;
    std::string _msgTopic;

public:
    Topic(void);
    Topic(std::string str);
    Topic(Topic const &src);
    ~Topic();
    Topic operator=(Topic const &rhs);

};
