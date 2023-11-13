#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <poll.h>
#include <cerrno>
#include <ctime>
#include <vector>
#include <map>
#include <deque>
# include <list>

#define MAX_USERS 10

#include "user/User.hpp"
#include "Utils.hpp"
// #include "user/AllClient.hpp"

#define GREEN2 "\033[1;32m"
#define GREEN "\e[92;5;118m"
#define GRAY "\e[33;2;37m"
#define RESET "\e[0m"
#define CURSIVE	"\e[33;3m"
#define RED "\033[0;31m"
#define BOLD "\x1b[1m"
#define UNDER "\x1b[4m" //souligné

#define IRChub = "IRChub"


/*INVITE*/

#define ERR_INVALIDINPUT(source, command)    ": 461 " + source + " " + command + " :Invalid input"
#define ERR_NEEDMOREPARAMS(source, command)    ": 461 " + source + " " + command + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(source, channel)     ": 403 " + source + " " + channel + " :No such channel"
#define ERR_USERONCHANNEL(source, channel)     ": 443 " + source + " " + channel + " :is already on channel"
#define ERR_NOTONCHANNEL(source, channel)      ": 442 " + source + " " + channel + " :You're not on that channel"
/*-----------------*/

/*JOIN*/
#define RPL_NAMREPLY(source, channel, users)            ":IRChub 353 " + source + " = " + channel + " :" + users
#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
#define ERR_INVITEONLYCHAN(source, channel)    ": 473 " + source + " " + channel + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(source, channel)     ": 475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(source, channel)     ": 471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_BADCHANMASK(channel)               ": 476 " + channel + " :Bad Channel Mask"
/*-------------*/

/*TOPIC*/
#define RPL_TOPIC(nick, channel, topic)      ":IRChub 332 " + nick + " " + channel + " :" + topic + "\r\n"
#define RPL_TOPICWHOTIME(nick, channel, who, time)      ":IRChub 333 " + nick + " " + channel + " " + who + " " + time + "\r\n"

/*MODE*/
#define c(nick, who)     ":IRChub 401 " + nick + " " + who + " :No such nick/channel\r\n"
#define RPL_UMODEIS(network, nick, mode)      ":" + network + " 221 " + nick + " " + mode + "\r\n"
#define RPL_CREATIONTIME(network, nick, channel, time)      ":" + network + " 329 " + nick + " " + channel + " " + time + "\r\n"
#define ERR_UNKNOWNMODE(network, nick, mode)      ":" + network + " 472 " + nick + " " + mode + " :is unknown mode char to me\r\n"
#define RPL_CHANNELMODEIS(network, nick, channel, mode)      ":" + network + " 324 " + nick + " " + channel + " " + mode + "\r\n"
//mettre WHO a la fin de ces 2 RPL
#define RPL_MODEADDO(nick, channel, who)      ":" + nick + " MODE #" + channel + " +o " + who + "\r\n"
#define RPL_MODEREMOVEO(nick, channel, who)      ":" + nick + " MODE #" + channel + " -o " + who + "\r\n"

#define RPL_MODEADDK(nick, channel, password)            ":" + nick + " MODE #" + channel + " +k " + password + "\r\n"

#define ERR_USERNOTINCHANNEL(nick, who, channel)   ":IRChub 441 " + nick + " " + who + " " + channel + " :They aren't on that channel\r\n"
#define ERR_CHANOPRIVSNEEDED(nick, channel)   ":IRChub 482 " + nick + " " + channel + " :You're not channel operator\r\n"

#define ERR_NOSUCHNICK(client, nick)     ": 401 " + client + nick + " :No such nick/channel"
#define ERR_NOTEXTTOSEND(client)     ": 412 " + client + " :No text to send"
#define ERR_NOSUCHSERVER(client, channel)     ": 402 " + client + " " + channel + " :No such server"
