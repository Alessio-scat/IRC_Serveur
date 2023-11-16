#pragma once
# include "IRC.hpp"
#include "user/User.hpp"
#include "Channel/Channel.hpp"

class User;
class Channel;

void ft_trim(std::string &str);
void writeInfd(const std::string& message, int i, std::deque<struct pollfd> _pfds);
std::string listUserChannel(const std::map<std::string, std::list<std::string> >& channel, User *_tabUser, std::string join, int userCmd);
void printListMode(std::string channelFind, Channel &channel);
int clientIsChannelOperator(std::string channelFind, User *_tabUser, int i, std::deque<struct pollfd> _pfds);
void errNeedMoreParams(std::string source, std::string command, int i, std::deque<struct pollfd> _pfds);