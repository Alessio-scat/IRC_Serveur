#pragma once

#include "../IRC.hpp"

class Topic
{
private:
    std::string _msgTopic;
    std::string _channelTopic;

public:
    Topic(void);
    Topic(std::string str);
    Topic(Topic const &src);
    ~Topic();
    Topic operator=(Topic const &rhs);

};
