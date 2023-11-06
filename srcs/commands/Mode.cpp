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

void Mode::changeMode(Channel &channel, User *_tabUser, int index)
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
                addModeO(channel, _tabUser, index);
            else
            {
                _tabUser[index].setOperateur(false);
                std::cout << "\x1B[31m" << _tabUser[index].getNickname() << " not OPERATOR" << "\x1B[0m" << std::endl;
                removeMode('o', channel);
            }
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

void Mode::addModeO(Channel &channel, User *_tabUser, int index)
{
    _tabUser[index].setOperateur(true);
    addRemoveChanOperator(_tabUser, index, 1);
    std::cout << "\x1B[32m" << _tabUser[index].getNickname() << " is now OPERATOR" << "\x1B[0m" << std::endl;
    addMode('o', channel);
    printListChanOperator(_tabUser, index);
}

void Mode::removeModeO(Channel &channel, User *_tabUser, int index)
{
    _tabUser[index].setOperateur(false);
    addRemoveChanOperator(_tabUser, index, 0);
    std::cout << "\x1B[31m" << _tabUser[index].getNickname() << " not OPERATOR" << "\x1B[0m" << std::endl;
    removeMode('o', channel);
    printListChanOperator(_tabUser, index);
}

void Mode::addRemoveChanOperator(User *_tabUser, int index, bool isAdd)
{
    if (std::find(_tabUser[index]._chanOperator.begin(), _tabUser[index]._chanOperator.end(), this->_channelMode) == _tabUser[index]._chanOperator.end())
    {
        if (isAdd == 1)
        {
            _tabUser[index]._chanOperator.push_back(this->_channelMode);
            std::cout << "ChannelOperator ajouté : " << this->_channelMode << std::endl;
        }
        else
            std::cout << "ChannelOperator non présent : " << this->_channelMode << std::endl;
    }
    else
    {
        if (isAdd == 1)
            std::cout << "ChannelOperator déjà présent : " << this->_channelMode << std::endl;
        else
        {
            _tabUser[index]._chanOperator.erase(std::remove(_tabUser[index]._chanOperator.begin(), _tabUser[index]._chanOperator.end(), this->_channelMode), _tabUser[index]._chanOperator.end());
            std::cout << "ChannelOperator supprimé : " << this->_channelMode << std::endl;
        }
    }
}

void Mode::printListChanOperator(User *_tabUser, int index)
{
    std::list<std::string>::iterator iterator = _tabUser[index]._chanOperator.begin();

    std::cout << "List of channel operator : [";
    while (iterator != _tabUser[index]._chanOperator.end())
    {
        std::cout << *iterator << " ";
        iterator++;
    }
    std::cout << "]" << std::endl;
}

