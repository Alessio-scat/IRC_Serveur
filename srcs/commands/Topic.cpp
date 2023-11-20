#include "../../includes/commands/Command.hpp"
#include "../../includes/Channel/Channel.hpp"

Topic::Topic(void){}

Topic::~Topic(){}

Topic::Topic(Topic const &src):Command(src)
{
    this->_channelTopic = src._channelTopic;
    this->_msgTopic = src._msgTopic;
}

Topic &Topic::operator=(Topic const &rhs)
{
    Command::operator=(rhs);
    this->_channelTopic = rhs._channelTopic;
    this->_msgTopic = rhs._msgTopic;
    return (*this);
}

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
        errNeedMoreParams(_tabUser[i].getNickname(), "TOPIC", i, _pfds);
        std::cout << "ERROR: TOPIC need more param" << std::endl;
        return ;
    }
    tmpChannel = str.substr(6, endChannel - 6);
    ft_trim(tmpChannel);
    if (isModePresentInChannel(channel, tmpChannel, 't'))
    {
        if (clientIsChannelOperator(tmpChannel, _tabUser, i, _pfds))
            return ;
    }
    if (str.find(":") == std::string::npos)
    {
        std::cout << "CHECK" << std::endl;
        checkTopic(tmpChannel, channel, _tabUser, i, _pfds);
        return ;
    }
    this->_channelTopic = tmpChannel;
    startTopic = str.find(":");
    tmpTopic = str.substr(startTopic);
    ft_trim(tmpTopic);
    if ((tmpTopic.size() == 1 && (tmpTopic[0] == ':' && tmpTopic[1] != ':')) || isOnlySpace(tmpTopic))
    {
        std::cout << "CLEAR" << std::endl;
        this->_msgTopic = "";
        channel.mapTopic[this->getChannelTopic()] = this->getMsgTopic();
        this->rplTopic(_tabUser, i, _pfds);
        return ;
    }
    this->_msgTopic = tmpTopic.substr(1);
    std::cout << "msgTopic : " << "|" << this->_msgTopic << "|" << std::endl;
    this->rplTopicWhoTime(_tabUser, i, _pfds);
    this->rplTopic(_tabUser, i, _pfds);
    channel.mapTopic[this->getChannelTopic()] = this->getMsgTopic();
    printMapTopic(channel.mapTopic);
}

void Topic::rplTopic(User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    std::string message = RPL_TOPIC(_tabUser[i].getNickname(), this->_channelTopic, this->_msgTopic);
    writeInfd(message, i, _pfds);
}

void Topic::rplTopicWhoTime(User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    struct timeval currentTime;
    getCurrentTime(currentTime);

    std::string message = RPL_TOPICWHOTIME(_tabUser[i].getNickname(), this->_channelTopic, _tabUser[i].getNickname(), intToString(currentTime.tv_sec));
    writeInfd(message, i, _pfds);
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

void Topic::checkTopic(std::string tmpChannel, Channel &channel, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    this->_channelTopic = tmpChannel;
    std::cout << "channelTopic : " << this->_channelTopic << std::endl;
    std::cout << "channelTopic : " << "|" << this->_channelTopic << "|" << std::endl;
    printTopic(this->getChannelTopic(), channel.mapTopic);
    printMapTopic(channel.mapTopic);
    this->_msgTopic = channel.mapTopic[this->getChannelTopic()];
    this->rplTopic(_tabUser, i, _pfds);
}

std::string Topic::getChannelTopic(void)
{
    return (this->_channelTopic);
}

std::string Topic::getMsgTopic(void)
{
    return (this->_msgTopic);
}

void Topic::getCurrentTime(struct timeval& tv)
{
    gettimeofday(&tv, NULL);
}

std::string Topic::intToString(int value)
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}