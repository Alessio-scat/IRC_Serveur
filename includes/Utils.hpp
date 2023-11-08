#pragma once
# include "IRC.hpp"
#include "user/User.hpp"

class User;

void ft_trim(std::string &str);
void writeInfd(const std::string& message, int i, std::deque<struct pollfd> _pfds);
std::string listUserChannel(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser, std::string join, int userCmd);