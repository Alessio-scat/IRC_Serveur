# ifndef USER_HPP
#define USER_HPP

#include "../IRC.hpp"

class User
{
private:
    std::string _username;
    std::string _nickname;
    bool _operator;
    std::list<std::string> _chanOperator;

public:
    User();
    User(User const &src);
    ~User();

    User operator=(User const &rhs);
    
    std::string getNickname(void)const;
    void setNickname(std::string nickname);
    std::string getUsername(void)const;
    void setUsername(std::string username);
};

#endif
