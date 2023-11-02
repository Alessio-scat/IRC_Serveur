#include "../../includes/commands/Command.hpp"

Mode::Mode(void){}

void Mode::execute_cmd(std::string str)
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
    if (str.find("+") == std::string::npos)
    {
        std::cout << "ERROR: MODE wrong opt" << std::endl;
        // Checking the topic for the channel
        return ;
    }
    startOpt = str.find("+");
    tmpOpt = str.substr(startOpt);
    // if (tmpOpt.size() != 3 || (tmpOpt[1] != 'i' && tmpOpt[1] != 't'
    //     && tmpOpt[1] != 'k' && tmpOpt[1] != 'o' && tmpOpt[1] != 'l'))
    // {
    //     std::cout << "ERROR: Opt incorrect" << std::endl;
    //     return ;
    // }
    this->_opt = tmpOpt;
    std::cout << "option Mode : " << this->_opt << std::endl;
}

Mode::~Mode(){}

void Mode::changeMode(void)
{
    if (this->_opt.size() == 2)
    {
        std::cout << "AAAAAAA" << std::endl;
        return ;
    }
    for (size_t i = 1; i < this->_opt.size(); i++)
    {
        if (this->_opt[i] == 'i')
            std::cout << "MODE +i" << std::endl;
        else if (this->_opt[i] == 't')
            std::cout << "MODE +t" << std::endl;
        else if (this->_opt[i] == 'k')
            std::cout << "MODE +k" << std::endl;
        else if (this->_opt[i] == 'o')
            std::cout << "MODE +o" << std::endl;
        else if (this->_opt[i] == 'l')
            std::cout << "MODE +l" << std::endl;
        else
            std::cout << this->_opt[i] << ":is not a recognised channel mode." << std::endl;
    }
}