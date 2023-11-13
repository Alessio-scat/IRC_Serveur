# include "../includes/bot.hpp"

int main(int ac, char **av)
{
    std::cout << "YOOOOOO" << std::endl;
    if (ac != 3)
    {
        std::cout << "Error: Usage /bot...." << std::endl;
        return 1;
    }

    Bot bot = Bot("Bot", std::atoi(av[1]), av[2], "127.0.0.1");
    if (bot.Bot_Start() == 1)
        return 1;

    if (bot.Bot_Run() == 1)
        return 1;

    if (bot.Bot_Stop() == 1)
        return 1;
    return 0;
}