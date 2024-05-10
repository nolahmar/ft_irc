#ifndef client_hpp
#define  client_hpp

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include <vector>
#include "channel.hpp"

class channel;
class client
{
    private:
        int fd;                                                                                                                                                                                                                                                                                                                                 
        //std::string port;
        std::string nickname;
        std::string username;
        std::string realname;
        std::string hostname;
        std::vector<channel*>  channel;
        std::vector<client*> clients;
        
    public:
    client(int fd);
    client();
    client & operator=(const client &orginal);
    ~client();
    void User(const std::string &userCmd);
    void write(const std::string& message) const;
    const std::string& getNickname() const;
    client* getClient(const std::string& nickname) const;
};

#endif