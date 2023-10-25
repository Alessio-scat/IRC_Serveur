#include "../../includes/commands/Command.hpp"

Topic::Topic(void){}

void Topic::execute_cmd(std::string str)
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
    tmpTopic = str.substr(startTopic);
    if (tmpTopic.size() == 3)
    {
        std::cout << "CLEAR" << std::endl;
        //Clearing the topic on channel
        return ;
    }
    this->_msgTopic = tmpTopic;
    std::cout << "msgTopic : " << this->_msgTopic << std::endl;

}

Topic::~Topic(){}