#pragma once

#include "../IRC.hpp"

class Invite
{
private:
    std::string _nickInvite;
    std::string _channelInvite;
    Invite(void);
public:
    Invite(std::string str);
    Invite(Invite const &src);
    ~Invite();
    Invite operator=(Invite const &rhs);
    void getNickInvite(std::string nickInvite);
    void getChannelInvite(std::string channelInvite);

};
