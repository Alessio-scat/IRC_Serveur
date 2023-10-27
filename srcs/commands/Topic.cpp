#include "../../includes/commands/Command.hpp"
#include "../../includes/Channel/Channel.hpp"

Topic::Topic(void){}

Topic::~Topic(){}

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
    (void)str;
}

void Topic::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel)
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

    // this->_channelTopic = tmpChannel.substr(1, tmpChannel.size() - 1);
    this->_channelTopic = tmpChannel.substr(0, tmpChannel.size() - 1);
    std::cout << "channelTopic : " << this->_channelTopic << std::endl;
    if (str.find(":") == std::string::npos)
    {
        std::cout << "CHECK" << std::endl;
        // Checking the topic for the channel
        // this->_msgTopic = "";
        // std::cout << "msgTopic : " << "|" << this->_msgTopic << "|" << std::endl;
        std::cout << "channelTopic : " << "|" << this->_channelTopic << "|" << std::endl;
        printTopic(this->getChannelTopic(), channel.mapTopic);
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
    this->_msgTopic = tmpTopic.substr(1, tmpTopic.size() - 2);
    std::cout << "msgTopic : " << "|" << this->_msgTopic << "|" << std::endl;
    this->rpl(str, _tabUser, i, _pfds);
    channel.mapTopic[this->getChannelTopic()] = this->getMsgTopic();
    printMapTopic(channel.mapTopic);
}

void Topic::rpl(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    (void)str;
    std::string message = ":IRChub 332 " + _tabUser[i].getNickname() + " " + this->_channelTopic + " :" + this->_msgTopic + "\r\n";
    std::cout << "message : |" << message << "|" << std::endl;
    size_t size = send(_pfds[i].fd, message.c_str(), message.size(), 0);
    if (size < 0)
        std::cout << "null\n";
    else
        std::cout << "good\n";
}

void Topic::printTopic(std::string channelTopic, std::map<std::string, std::string> &mapTopic)
{
    std::map<std::string, std::string>::iterator it = mapTopic.find(channelTopic);
    if (it != mapTopic.end())
    {
        std::cout << "MAPTOPIC: " << it->first << " " << it->second << std::endl;
    }
    else
    {
        std::cout << "Le canal " << channelTopic << " n'a pas été trouvé dans la carte." << std::endl;
    }
}

void Topic::printMapTopic(const std::map<std::string, std::string>& mapTopic)
{
    for (std::map<std::string,  std::string>::const_iterator it = mapTopic.begin(); it != mapTopic.end(); ++it) {
        std::cout << "\033[34m" << "MAPTOPIC: |" << it->first << "| |" << it->second << "| \033[0m" << std::endl;
        std::cout << std::endl;
    }
}

std::string Topic::getChannelTopic(void)
{
    return (this->_channelTopic);
}

std::string Topic::getMsgTopic(void)
{
    return (this->_msgTopic);
}