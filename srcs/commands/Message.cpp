#include "../../includes/commands/Command.hpp"

Message::Message(void){}

// Message::Message(Message const &src)
// {
//     *this = src;
// }

void Message::execute_cmd(std::string str)
{
    (void)str;
}

void Message::execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel)
{
    size_t pos;
    pos = str.find("#");
    if (pos != std::string::npos)
    {
        // if(str) message to op
        this->messageToChannel(str, _tabUser, i, _pfds, channel, pos);
    }
    else
    {
        pos = str.find(" ");
        if (pos != std::string::npos)
            this->messageToSomeone(str, _tabUser, i, _pfds, pos);
    }
}

Message::~Message(){}

void Message::messageToChannel(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel, int pos)
{
        std::string list;
        int j = pos;
        int size = 0;
        while (str[j] && str[j] != ' ')
        {
            j++;
            size++;
        }
        std::string channelName = str.substr(pos, size);
        std::cout << "|" << channelName << "|" << std::endl;
        list = listUserChannel(channel.mapChannel, _tabUser, channelName);
        str = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
        std::istringstream ss(list);
        std::string word;
        while (ss >> word)
        {
            for (int j = 1; j <= MAX_USERS; j++)
            {
                if ((word == _tabUser[j].getNickname() || word == "@" + _tabUser[j].getNickname()) && word != _tabUser[i].getNickname() && word != "@" + _tabUser[i].getNickname())
                    send(_pfds[j].fd, str.c_str(), str.size(), 0);
            }
        }
}

void Message::messageToSomeone(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, int pos)
{
        int j = pos + 1;
        int size = 0;
        while (str[j] && str[j] != ' ')
        {
            j++;
            size++;
        }
        std::string destName = str.substr(pos + 1, size);
        str = ":" + _tabUser[i].getNickname() + " " + str + "\r\n";
        for (int j = 1; j <= MAX_USERS; j++)
        {
            if (destName == _tabUser[j].getNickname())
                send(_pfds[j].fd, str.c_str(), str.size(), 0);
        }
}

// Message Message::operator=(Message const &rhs)
// {
//     (void)rhs;
//     return (*this);
// }