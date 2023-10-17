# ifndef USER_HPP
#define USER_HPP

#include <iostream>

class User
{
private:
    std::string _username;
    std::string _nickname;
public:
    User(/* args */);
    User(User const &src);
    ~User();

    User operator=(User const &rhs);
    
    std::string getNickname(void)const;
    void setNickname(std::string nickname);
    std::string getUsername(void)const;
    void setUsername(std::string username);
};

#endif
