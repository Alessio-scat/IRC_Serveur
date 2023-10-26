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
#include <vector>
#include <map>
#include <deque>
# include <list>

#define MAX_USERS 10

#include "user/User.hpp"

#define GREEN2 "\033[1;32m"
#define GREEN "\e[92;5;118m"
#define GRAY "\e[33;2;37m"
#define RESET "\e[0m"
#define CURSIVE	"\e[33;3m"
#define RED "\033[0;31m"
#define BOLD "\x1b[1m"
#define UNDER "\x1b[4m" //souligné
