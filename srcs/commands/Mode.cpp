#include "../../includes/commands/Command.hpp"
#include "../../includes/IRC.hpp"

Mode::Mode(void){}

void Mode::execute_cmd(std::string str)
{
    (void)str;
}

Mode::Mode(Mode const &src):Command(src)
{
    this->_channelMode = src._channelMode;
    this->_who = src._who;
    this->_opt = src._opt;
}

Mode &Mode::operator=(Mode const &rhs)
{
    Command::operator=(rhs);
    this->_channelMode = rhs._channelMode;
    this->_who = rhs._who;
    this->_opt = rhs._opt;
    return (*this);
}

void Mode::execute_cmd(std::string str, Channel &channel)
{
    size_t endChannel = str.find(" ", 6);
    size_t startOpt;
    size_t endOpt;
    // size_t startWho;
    // size_t endWho;
    std::string tmpChannel;
    std::string tmpOpt;
    std::string tmpWho;

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
    if (str.find("+") != std::string::npos && str.find("-") != std::string::npos)
    {
        int tmpPosAdd = str.find("+");
        int tmpPosRemove = str.find("-");
        if (tmpPosAdd < tmpPosRemove)
            startOpt = tmpPosAdd;
        else
            startOpt = tmpPosRemove;
    }
    else
    {
        if (str.find("-") == std::string::npos)
            startOpt = str.find("+");
        else
            startOpt = str.find("-");
    }
    for (int i = startOpt; i < (int)str.size(); i++)
    {
        if (str[i] == ' ')
        {
            endOpt = i;
            break ;
        }
        else if (i == (int)str.size() - 1)
            endOpt = i + 1;
    }
    tmpOpt = str.substr(startOpt, endOpt - startOpt);
    this->_opt = tmpOpt;
    std::cout << "option Mode : " << this->_opt << std::endl;
    // while (str[endOpt] == ' ')
    //     endOpt++;
    // startWho = endOpt;
    // endWho = endOpt;
    // while (str[endWho] != ' ' && endWho <= str.size())
    //     endWho++;
    // tmpWho = str.substr(startWho, endWho - startWho);
    // ft_trim(tmpWho);
    tmpWho = str.substr(endOpt, str.size() - endOpt);
    ft_trim(tmpWho);
    this->_who = tmpWho;
    std::cout << "who : |" << this->_who << "|" << std::endl;
    channel.mapTopic[this->getChannelMode()];
}

Mode::~Mode(){}

void Mode::changeMode(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    if (this->_opt.size() < 2)
        return ;
    for (size_t i = 1; i < this->_opt.size(); i++)
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
                addModeT(channel, _tabUser, index, _pfds);
            else if (this->_opt[0] == '-')
                removeModeT(channel, _tabUser, index, _pfds);
        }
        else if (this->_opt[i] == 'k')
        {
            if (this->_opt[0] == '+')
                addModeK(channel, _tabUser, index, _pfds);
            else if (this->_opt[0] == '-')
                removeModeK(channel, _tabUser, index, _pfds);
        }
        else if (this->_opt[i] == 'o')
        {
            if (this->_who == "")
                std::cout << "ERROR: MODE o need who" << std::endl;
            else if (this->_opt[0] == '+')
                addModeO(channel, _tabUser, index, _pfds);
            else if (this->_opt[0] == '-')
                removeModeO(channel, _tabUser, index, _pfds);
        }
        else if (this->_opt[i] == 'l')
        {
            if (this->_opt[0] == '+')
                addModeL(channel, _tabUser, index, _pfds);
                // addMode('l', channel);
            else
                removeModeL(channel, _tabUser, index, _pfds);
                // removeMode('l', channel);
        }
        else
            std::cout << this->_opt[i] << " :is not a recognised channel mode." << std::endl;
    }
}


void Mode::addModeL(Channel &channel, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    if (!_who.size())
    {
        writeInfd(ERR_NEEDMOREPARAMS(_tabUser[i].getUsername(), "Usage /mode (+l)"), i, _pfds);
        return ;
    }
    
    _limit = std::atoi(_who.c_str());
    if (_limit <= 0)
    {
        writeInfd(ERR_INVALIDINPUT(_tabUser[i].getUsername(), "Usage /mode (+l)"), i, _pfds);
        return ;
    }
    channel._mapChannelLimit[_channelMode] = _limit;
    addMode('l', channel);
    std::string message = RPL_MODEADDL(_tabUser[i].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()), this->getWho());
    writeInfd(message, i, _pfds);
}

void Mode::removeModeL(Channel &channel, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    channel._mapChannelLimit[_channelMode] = MAX_USERS;
    removeMode('l', channel);
    std::string message = RPL_MODEREMOVEL(_tabUser[i].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()));
    writeInfd(message, i, _pfds);
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
    std::cout << "CHANNELMODE : |" << this->_channelMode << "|" << std::endl;
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

std::string Mode::getWho(void)
{
    return (this->_who);
}

void Mode::addModeO(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    _tabUser[index].setOperateur(true);
    addRemoveChanOperator(channel, _tabUser, index, 1, _pfds);
    addMode('o', channel);
    printListChanOperator(_tabUser, index);
}

void Mode::removeModeO(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    // _tabUser[index].setOperateur(false);
    addRemoveChanOperator(channel, _tabUser, index, 0, _pfds);
    removeMode('o', channel);
    printListChanOperator(_tabUser, index);
}

int Mode::isWhoInChannel(Channel &channel)
{
    std::list<std::string>::iterator iterator = channel.mapChannel[this->_channelMode].begin();

    while (iterator != channel.mapChannel[this->_channelMode].end())
    {
        // std::cout << "iterator : |" << *iterator << "|" << std::endl;
        if (*iterator == this->_who)
            return (0);
        iterator++;
    }
    return (1);
}

int Mode::isUserChannelOperatorInChannel(User *_tabUser, int index)
{
    // _tabUser->_chanOperator.push_back(this->_channelMode);
    std::list<std::string>::iterator iterator = _tabUser[index]._chanOperator.begin();

    /////////////////////////// Print list of mode
    std::cout << "CHANNELMODE : |" << this->_channelMode << "|" << std::endl;
    std::list<std::string>::iterator iterator2 = _tabUser[index]._chanOperator.begin();

    std::cout << "List of channelOp for " << _tabUser[index].getNickname() << " : [";
    while (iterator2 != _tabUser[index]._chanOperator.end())
    {
        std::cout << *iterator2 << " ";
        iterator2++;
    }
    std::cout << "]" << std::endl;
    ///////////////////////////
    while (iterator != _tabUser[index]._chanOperator.end())
    {
        // std::cout << "A trouver: " << this->_channelMode << std::endl;
        // std::cout << "iterator : |" << *iterator << "|" << std::endl;
        if (*iterator == this->_channelMode)
            return (0);
        iterator++;
    }
    return (1);
}

void Mode::addRemoveChanOperator(Channel &channel, User *_tabUser, int index, bool isAdd, std::deque<struct pollfd> _pfds)
{
    if (isWhoInChannel(channel))
    {
        std::string message = ERR_USERNOTINCHANNEL(_tabUser[index].getNickname(), this->_who, this->_channelMode);
        writeInfd(message, index, _pfds);
        return ;
    }
    if (isUserChannelOperatorInChannel(_tabUser, index))
    {
        std::string message = ERR_CHANOPRIVSNEEDED(_tabUser[index].getNickname(), this->_channelMode);
        writeInfd(message, index, _pfds);
        return ;
    }
    int who = 0;
    for (; who < MAX_USERS; who++)
    {
        if (_tabUser[who].getNickname() == this->_who)
        {
            break;
        }
    }
    if (std::find(_tabUser[who]._chanOperator.begin(), _tabUser[who]._chanOperator.end(), this->_channelMode) == _tabUser[who]._chanOperator.end())
    {
        if (isAdd == 1)
        {
            _tabUser[who]._chanOperator.push_back(this->_channelMode);
            std::cout << "ChannelOperator ajouté : " << this->_channelMode << std::endl;
            std::cout << "\x1B[32m" << _tabUser[who].getNickname() << " is now OPERATOR" << "\x1B[0m" << std::endl;
            // std::cout << "WHO " << this->_who << std::endl;
            std::string message = RPL_MODEADDO(_tabUser[index].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()), this->getWho());
            // std::cout << "message : |" << message << "|" << std::endl;
            std::string list = listUserChannel(channel.mapChannel, _tabUser, this->_channelMode, index);
            std::istringstream ss(list);
            std::string word;
            while (ss >> word)
            {
                for (int j = 1;j < MAX_USERS; j++)
                {
                    if (word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname())
                        send(_pfds[j].fd, message.c_str(), message.size(), 0);
                }
            }
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
            if (_tabUser[who].getNickname() == _tabUser[index].getNickname())
            {
                std::cout << "ERROR: You can't remove yourself from channel operator" << std::endl;
                return ;
            }
            _tabUser[who]._chanOperator.erase(std::remove(_tabUser[who]._chanOperator.begin(), _tabUser[who]._chanOperator.end(), this->_channelMode), _tabUser[who]._chanOperator.end());
            std::cout << "ChannelOperator supprimé : " << this->_channelMode << std::endl;
            std::cout << "\x1B[31m" << _tabUser[who].getNickname() << " not OPERATOR" << "\x1B[0m" << std::endl;
            std::string message = RPL_MODEREMOVEO(_tabUser[index].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()), this->getWho());
            // std::string message = RPL_MODEREMOVEO(_tabUser[who].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()), _tabUser[who].getNickname());
            std::cout << "message : |" << message << "|" << std::endl;
            send(_pfds[index].fd, message.c_str(), message.size(), 0);
        }
    }
}

void Mode::addModeT(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    if (isUserChannelOperatorInChannel(_tabUser, index))
    {
        std::cout << "ERROR: Client not channel operator" << std::endl;
        std::string message = ERR_CHANOPRIVSNEEDED(_tabUser[index].getNickname(), this->_channelMode);
        writeInfd(message, index, _pfds);
        return ;
    }
    addMode('t', channel);
    printListMode(channel);
}

void Mode::removeModeT(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    if (isUserChannelOperatorInChannel(_tabUser, index))
    {
        std::cout << "ERROR: Client not channel operator" << std::endl;
        std::string message = ERR_CHANOPRIVSNEEDED(_tabUser[index].getNickname(), this->_channelMode);
        writeInfd(message, index, _pfds);
        return ;
    }
    removeMode('t', channel);
    printListMode(channel);
}

void Mode::addModeK(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    (void)_tabUser;
    (void)index;
    (void)_pfds;
    if (isUserChannelOperatorInChannel(_tabUser, index))
    {
        std::cout << "ERROR: Client not channel operator" << std::endl;
        std::string message = ERR_CHANOPRIVSNEEDED(_tabUser[index].getNickname(), this->_channelMode);
        writeInfd(message, index, _pfds);
        return ;
    }
    if (!this->_who.size())
    {
        std::cout << "ERROR: MODE k need key" << std::endl;
        return ;
    }
    channel._mapChannelKey[this->_channelMode] = this->_who;
    std::cout << "Key activate in channel " << this->_channelMode << " with key : |" << channel._mapChannelKey[this->_channelMode] << "|" << std::endl;
    addMode('k', channel);
    printListMode(channel);
    std::string message = RPL_MODEADDK(_tabUser[index].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()), this->getWho());
    writeInfd(message, index, _pfds);
}

void Mode::removeModeK(Channel &channel, User *_tabUser, int index, std::deque<struct pollfd> _pfds)
{
    (void)_tabUser;
    (void)index;
    (void)_pfds;
    
    if (isUserChannelOperatorInChannel(_tabUser, index))
    {
        std::cout << "ERROR: Client not channel operator" << std::endl;
        std::string message = ERR_CHANOPRIVSNEEDED(_tabUser[index].getNickname(), this->_channelMode);
        writeInfd(message, index, _pfds);
        return ;
    }

    std::map<std::string, std::string>::iterator iterator = channel._mapChannelKey.find(this->_channelMode);
    
    if (iterator == channel._mapChannelKey.end())
    {
        std::cout << "MODE k doesn't exist" << std::endl;
        return ;
    }
    channel._mapChannelKey.erase(iterator);
    std::cout << "Key deleted in channel " << this->_channelMode << std::endl;
    removeMode('k', channel);
    printListMode(channel);
    std::string message = RPL_MODEREMOVEK(_tabUser[index].getNickname(), this->_channelMode.substr(1, this->_channelMode.size()));
    writeInfd(message, index, _pfds);
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
