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