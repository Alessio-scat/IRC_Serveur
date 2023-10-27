#pragma once
# include "IRC.hpp"

void ft_trim(std::string &str);
void writeInfd(const std::string& message, int i, std::deque<struct pollfd> _pfds);