# ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP

# include "../IRC.hpp"

class Channel
{
    public:
        Channel(void);
        Channel(Channel const &src);
        Channel &operator=(Channel const &rhs);
        ~Channel(void);

        std::map<std::string, std::list<std::string> > channel;
    private:
};

# endif 