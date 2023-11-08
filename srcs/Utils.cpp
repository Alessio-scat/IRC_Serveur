# include "../includes/Utils.hpp"

void ft_trim(std::string &str)
{
    size_t start = 0;
    size_t end = str.length() - 1;

    while (start <= end && std::isspace(str[start]))
        start++;
    while (end >= start && std::isspace(str[end]))
        end--;
    str = str.substr(start, end - start + 1);
}

void            writeInfd(const std::string& message, int i, std::deque<struct pollfd> _pfds)
{
    std::string buffer = message + "\r\n";
    if (send(_pfds[i].fd, buffer.c_str(), buffer.length(), 0) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
}

std::string listUserChannel(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser, std::string join, int userCmd)
{
    std::string list;
    int i = 0;
    for (std::map<std::string, std::list<std::string> >::const_iterator it = channel.begin(); it != channel.end(); ++it) {
        if (it->first == join)
        {
            for (std::list<std::string>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
            {
                std::cout << CURSIVE << *subIt << " " << RESET;
                if (i == 0 && it->second.size() == 1)
                {
                    for (int j = 1; j <= MAX_USERS; j++)
                    {
                        if (*subIt == _tabUser[j].getNickname() && *subIt == _tabUser[userCmd].getNickname())
                            _tabUser[j]._chanOperator.push_back(join);
                    }
                    // list += "@" + *subIt;
                }
                if (i == 0)
                {
                    for (int j = 1; j <= MAX_USERS; j++)
                    {
                        if (*subIt == _tabUser[j].getNickname())
                        {
                            if (std::find(_tabUser[j]._chanOperator.begin(), _tabUser[j]._chanOperator.end(), join) != _tabUser[j]._chanOperator.end())
                                list += "@" + *subIt;
                            else
                                list += *subIt;
                        }
                    }
                }
                else
                {
                    for (int j = 1; j <= MAX_USERS; j++)
                    {
                        if (*subIt == _tabUser[j].getNickname())
                        {
                            if (std::find(_tabUser[j]._chanOperator.begin(), _tabUser[j]._chanOperator.end(), join) != _tabUser[j]._chanOperator.end())
                                list += " @" + *subIt;
                            else
                                list += " " + *subIt;
                        }
                    } 
                }
                i++;
            }
        }
    }
    return (list);
}