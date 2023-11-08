# ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP

# include "../IRC.hpp"

class Channel
{
    private:
    
    public:
        Channel(void);
        Channel(Channel const &src);
        Channel &operator=(Channel const &rhs);
        ~Channel(void);

        std::map<std::string, std::list<std::string> > channel;
        std::map<std::string, std::string> mapTopic;
        std::map<std::string, std::vector<char> > mapMode;

        std::map<std::string, std::string > _mapChannelKey;
    
};

int isInChannel(std::string channelFind, std::string nick, Channel &channel);

# endif 