#include "../../includes/commands/Message.hpp"

Message::Message(void){}

Message::Message(Message const &src)
{
    *this = src;
}

Message::Message(std::string str, User &user)
{

}

Message::~Message(){}

Message Message::operator=(Message const &rhs)
{

}