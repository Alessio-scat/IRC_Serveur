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
        void ExistChannel(const std::map<std::string, std::list<std::string> >& channel, std::deque<struct pollfd> _pfds, int i);
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
        void changeMode(void);
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
};

class Join: public Command
{
    private:
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