# ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../IRC.hpp"
#include "../Channel/Channel.hpp"


class Command
{
    private:

    
    public:
        Command(void);
        Command(Command const &src);
        Command &operator=(Command const &rhs);
        virtual ~Command(void);

        virtual void execute_cmd(std::string str) = 0;

};

class Invite: public Command
{
    private:
        std::string _nickInvite;
        std::string _channelInvite;
        std::string _cmd;

    public:
        Invite(void);
        ~Invite(void);
        void InviteClient(User *_tabUser, std::deque<struct pollfd> _pfds, int y);
        int ExistChannel(const std::map<std::string, std::list<std::string> >& channel, std::deque<struct pollfd> _pfds, int i, std::string &client);
        void ParseInviteCmd(std::string &str);
        void execute_cmd(std::string str);
        void execute_cmd(std::string str, std::deque<struct pollfd> _pfds, User *_tabUser, int y, Channel &channel);
};

class Kick: public Command
{
    private:
        std::string _user;
        std::string _channel;
        std::string _reason;

    public:
        Kick(void);
        ~Kick(void);
        void execute_cmd(std::string str);
};

class Mode: public Command
{
    private:
        std::string _channelMode;
        std::string _opt;

    public:
        Mode(void);
        ~Mode(void);
        void execute_cmd(std::string str);
        void execute_cmd(std::string str, Channel &channel);
        void changeMode(Channel &channel);
        void addMode(char mode, Channel &channel);
        void removeMode(char mode, Channel &channel);
        void printListMode(Channel &channel);
        std::string getChannelMode(void);
};

class Topic: public Command
{
    private:
       std::string _channelTopic;
        std::string _msgTopic;

    public:
        Topic(void);
        ~Topic(void);
        void execute_cmd(std::string str);
        void execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds, Channel &channel);
        void rplTopic(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds);
        void rplTopicWhoTime(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds);
        void printTopic(std::string channelTopic, std::map<std::string, std::string>& mapTopic);
        void printMapTopic(const std::map<std::string, std::string>& mapTopic);
        std::string getChannelTopic(void);
        std::string getMsgTopic(void);
        void getCurrentTime(struct timeval& tv);
        std::string intToString(int value);

};

class Join: public Command
{
    private:
        std::string _channelJoin;
    public:
        std::string nameChannel;
        Join(void);
        ~Join(void);

        void execute_cmd(std::string str);
        void execute_cmd(std::string str, User *_tabUser, int i, std::deque<struct pollfd> _pfds);
};

// class Message: public Command
// {
// private:
// public:
//     Message(void);
//     Message(Message const &src);
//     ~Message();
//     Message operator=(Message const &rhs);
//     void execute_cmd(std::string str, User *_tabUser, std::deque<struct pollfd> _pfds);
// };

#endif