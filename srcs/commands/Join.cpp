#include "../../includes/commands/Command.hpp"
# include "../../includes/Utils.hpp"

Join::Join(void){}

void Join::execute_cmd(std::string str)
{
    (void)str;
}

/*
    A faire:
        -  ERR_NEEDMOREPARAMS (461) 
        -  ERR_BADCHANNELKEY (475) 
        -  ERR_INVITEONLYCHAN (473)
        -  RPL_NAMREPLY (353) 
        -  RPL_ENDOFNAMES (366) 
*/

void Join::ParseJoinCmd(std::string &str)
{
    std::istringstream ss(str);
    std::string token;
    int i = 0;
    // ft_trim(str);

    while (ss >> token)
    {
        std::cout << UNDER << "str|" << token << "|" << RESET << std::endl;
        if (i == 0)
        {
            _cmd = token;
            std::cout << UNDER << "cmd|" << _cmd << "|" << RESET << std::endl;
            i = 1;
        }
        else if (i == 1)
        {
            _channelJoin = token;
            std::cout << UNDER << "_channelJoin|" << _channelJoin << "|" << RESET << std::endl;
            i = 2;
        }
        // else if (i == 2)
        // {
        //     if (token == "IRChub")
        //     {
        //         _channelInvite = "";
        //         break;
        //     }
        //     _channelInvite = token;
        //     std::cout << UNDER << "_channelInvite|" << _channelInvite << "|" << RESET << std::endl;
        //     break;
        // }
    }
}

void Join::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds)
{
    ParseJoinCmd(str);
    if (str.find('#') == std::string::npos)
    {
        // this->_channelJoin = str.substr(5);
        std::cout << "ERROR: JOIN need more param" << std::endl;
        std::string message = ":IRChub 403 " + _tabUser[i].getNickname() + " " + this->_channelJoin + " :No such channel\r\n";
        std::cout << "message : |" << message << "|" << std::endl;
        send(_pfds[i].fd, message.c_str(), message.size(), 0);
        // throw ERR_NEEDMOREPARAMS();
        return ;
    }
    // this->_channelJoin = str.substr(5, str.size() - 6);
    std::cout << "nameChannel" << "|" << _channelJoin << "|" << std::endl;
    this->nameChannel = this->_channelJoin;
    // std::cout << _tabUser[i].getUsername() << std::endl;
    // std::cout << "JOIN command : " << str << std::endl;
    // std::string message = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
    // std::cout << "message : " << message << std::endl;
    // writeInfd(RPL_JOIN(_tabUser[i].getUsername() + " " + str), i, _pfds);
    writeInfd(RPL_JOIN(_tabUser[i].getUsername(), _channelJoin), i, _pfds);
}

Join::~Join(){}