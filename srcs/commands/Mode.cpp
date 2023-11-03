#include "../../includes/commands/Command.hpp"

Mode::Mode(void){}

void Mode::execute_cmd(std::string str)
{
    (void)str;
}

void Mode::execute_cmd(std::string str, Channel &channel)
{
    size_t endChannel = str.find(" ", 6);
    size_t startOpt;
    std::string tmpChannel;
    std::string tmpOpt;

    if (str.find('#') == std::string::npos)
    {
        std::cout << "ERROR: MODE need more param" << std::endl;
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    tmpChannel = str.substr(5, endChannel - 5);
    if (tmpChannel.size() < 2)
    {
        std::cout << "ERROR: MODE wrong channel" << std::endl;
        // throw ERR_NOSUCHCHANNEL();
        return ;
    }
    this->_channelMode = tmpChannel;
    std::cout << "channelMode : " << this->_channelMode << std::endl;
    if (str.find("+") == std::string::npos && str.find("-") == std::string::npos)
    {
        std::cout << "ERROR: MODE wrong opt" << std::endl;
        // Checking the topic for the channel
        return ;
    }
    if (str.find("-") == std::string::npos)
        startOpt = str.find("+");
    else
        startOpt = str.find("-");
    tmpOpt = str.substr(startOpt);
    // if (tmpOpt.size() != 3 || (tmpOpt[1] != 'i' && tmpOpt[1] != 't'
    //     && tmpOpt[1] != 'k' && tmpOpt[1] != 'o' && tmpOpt[1] != 'l'))
    // {
    //     std::cout << "ERROR: Opt incorrect" << std::endl;
    //     return ;
    // }
    this->_opt = tmpOpt;
    std::cout << "option Mode : " << this->_opt << std::endl;
    channel.mapTopic[this->getChannelMode()];
}

Mode::~Mode(){}

void Mode::changeMode(Channel &channel)
{
    if (this->_opt.size() <= 2)
        return ;
    for (size_t i = 1; i < this->_opt.size() - 1; i++)
    {
        if (this->_opt[i] == 'i')
        {
            if (this->_opt[0] == '+')
                addMode('i', channel);
            else
                removeMode('i', channel);
        }
        else if (this->_opt[i] == 't')
        {
            if (this->_opt[0] == '+')
                addMode('t', channel);
            else
                removeMode('t', channel);
        }
        else if (this->_opt[i] == 'k')
        {
            if (this->_opt[0] == '+')
                addMode('k', channel);
            else
                removeMode('k', channel);
        }
        else if (this->_opt[i] == 'o')
        {
            if (this->_opt[0] == '+')
                addMode('o', channel);
            else
                removeMode('o', channel);
        }
        else if (this->_opt[i] == 'l')
        {
            if (this->_opt[0] == '+')
                addMode('l', channel);
            else
                removeMode('l', channel);
        }
        else
            std::cout << this->_opt[i] << " :is not a recognised channel mode." << std::endl;
    }
}

void Mode::addMode(char mode, Channel &channel)
{
    std::vector<char>::iterator iterator = channel.mapMode[this->_channelMode].begin();
    while (iterator != channel.mapMode[this->_channelMode].end())
    {
        if (*iterator == mode)
            return ;
        iterator++;
    }
    channel.mapMode[this->_channelMode].push_back(mode);
}

void Mode::removeMode(char mode, Channel &channel)
{
    std::vector<char>::iterator iterator = channel.mapMode[this->_channelMode].begin();
    while (iterator != channel.mapMode[this->_channelMode].end())
    {
        if (*iterator == mode)
        {
            channel.mapMode[this->_channelMode].erase(iterator);
            return ;
        }
        iterator++;
    }
}

void Mode::printListMode(Channel &channel)
{
    std::vector<char>::iterator iterator = channel.mapMode[this->_channelMode].begin();

    std::cout << "List of mode : [";
    while (iterator != channel.mapMode[this->_channelMode].end())
    {
        std::cout << *iterator << " ";
        iterator++;
    }
    std::cout << "]" << std::endl;
}

std::string Mode::getChannelMode(void)
{
    return (this->_channelMode);
}