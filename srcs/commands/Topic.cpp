#include "../../includes/commands/Topic.hpp"

Topic::Topic(void){}

Topic::Topic(Topic const &src)
{
    *this = src;
}

Topic::Topic(std::string str)
{
    size_t endChannel = str.find(" ", 7);
    size_t startTopic;
    std::string tmpChannel;
    std::string tmpTopic;

    if (str.find('#') == std::string::npos)
    {
        std::cout << "ERROR: TOPIC need more param" << std::endl;
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    tmpChannel = str.substr(6, endChannel - 6);

    this->_channelTopic = tmpChannel;
    std::cout << "channelTopic : " << this->_channelTopic << std::endl;
    if (str.find(":") == std::string::npos)
    {
        std::cout << "CHECK" << std::endl;
        // Checking the topic for the channel
        return ;
    }
    startTopic = str.find(":");
    tmpTopic = str.substr(startTopic + 1);
    // if (tmpTopic.size() == 3 && (tmpTopic[0] == ':' && tmpTopic[1] != ':'))
    if (tmpTopic.size() == 2 && tmpTopic[1] != ':')
    {
        std::cout << "CLEAR" << std::endl;
        //Clearing the topic on channel
        return ;
    }
    this->_msgTopic = tmpTopic;
    std::cout << "msgTopic : " << this->_msgTopic << std::endl;

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