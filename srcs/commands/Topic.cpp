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
    //////////////////////////////
    std::cout << "CHANNELMODE : |" << tmpChannel << "|" << std::endl;
    std::vector<char>::iterator iterator = channel.mapMode[tmpChannel].begin();

    std::cout << "List of mode : [";
    while (iterator != channel.mapMode[tmpChannel].end())
    {
        std::cout << *iterator << " ";
        iterator++;
    }
    std::cout << "]" << std::endl;
    //////////////////////////////
    ft_trim(tmpChannel);
    if (isModePresentInChannel(channel, tmpChannel, 't'))
    {
        std::list<std::string>::iterator it = _tabUser[i]._chanOperator.begin();
        while (it != _tabUser[i]._chanOperator.end())
        {
            if (*it == tmpChannel)
            {
                break;
            }
            it++;
        }
        if (it == _tabUser[i]._chanOperator.end())
        {
            std::cout << "ERROR: Client not channel operator" << std::endl;
            return ;
        }
    }
    // if (isInChannel(tmpChannel, _tabUser[i].getNickname(), channel))
    // {
    //     std::cout << "ERROR: Client not in channel" << std::endl;
    //     return ;
    // }
    if (str.find(":") == std::string::npos)
    {
        std::cout << "CHECK" << std::endl;
        this->_channelTopic = tmpChannel;
        std::cout << "channelTopic : " << this->_channelTopic << std::endl;
        std::cout << "channelTopic : " << "|" << this->_channelTopic << "|" << std::endl;
        printTopic(this->getChannelTopic(), channel.mapTopic);
        printMapTopic(channel.mapTopic);
        this->_msgTopic = channel.mapTopic[this->getChannelTopic()];
        this->rplTopic(_tabUser, i, _pfds);
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
    // std::cout << "MSGTOPIC: " << this->_msgTopic << std::endl;
    // std::string message = ":IRChub 332 " + _tabUser[i].getNickname() + " " + this->_channelTopic + " :" + this->_msgTopic + "\r\n";
    std::string message = RPL_TOPIC(_tabUser[i].getNickname(), this->_channelTopic, this->_msgTopic);
    std::cout << "message : |" << message << "|" << std::endl;
    size_t size = send(_pfds[i].fd, message.c_str(), message.size(), 0);
    if (size < 0)
        std::cout << "null\n";
    else
        std::cout << "good\n";
}

void Topic::rplTopicWhoTime(User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    struct timeval currentTime;
    getCurrentTime(currentTime);

    //Change WHO pour le mec qui avait changer le topic
    // std::string message = ":IRChub 333 " + _tabUser[i].getNickname() + " " + this->_channelTopic + " " + _tabUser[i].getNickname() + " " + intToString(currentTime.tv_sec) + "\r\n";
    std::string message = RPL_TOPICWHOTIME(_tabUser[i].getNickname(), this->_channelTopic, _tabUser[i].getNickname(), intToString(currentTime.tv_sec));
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