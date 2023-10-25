#include "../../includes/commands/Command.hpp"

Topic::Topic(void){}

bool isOnlySpace(std::string str)
{
    if (str.size() < 3)
        return (0);
    if (str[0] != ':')
        return (0);
    for (size_t i = 1; i < str.size() - 1; i++)
    {
        if (str[i] != ' ')
            return (0);
    }
    return (1);
}

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
    if ((tmpTopic.size() == 3 && (tmpTopic[0] == ':' && tmpTopic[1] != ':')) || isOnlySpace(tmpTopic))
    {
        std::cout << "CLEAR" << std::endl;
        //Clearing the topic on channel
        return ;
    }
    this->_msgTopic = tmpTopic.substr(1);
    std::cout << "msgTopic : " << this->_msgTopic << std::endl;

}

Topic::~Topic(){}