#ifndef channel_hpp
#define  channel_hpp

#include "client.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include <vector>

class channel
{
    private:
        std::string Name;
        std::vector<client *>  Admin;
        client  *Owner;
        std::vector<client*>  Users;
        std::string Key;
        std::string Topic;
        std::vector<channel*> channels;

    public:
    channel(std::string& Name, client * owner, std::string topic);
    channel();
    channel(const  client &orginal);
    ~channel();
    channel & operator=(const channel &orginal);
    void send_msg(const std::string& sender, const std::string& message, client* senderClient) const;
    bool is_member(client* user) const;
    channel* getChannel();

};

#endif