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
#include <algorithm>

class client;
class channel
{
    private:
        std::string Name;
        std::vector<client *>  Admin;
        client  *Owner;
        std::vector<client*> Users;
        std::string Key;
        std::string Topic;
        std::vector<channel*> channels;
        std::vector<client*> Operators;

    public:
    channel(std::string& Name, client * owner, std::string topic);
    channel();
    channel(const  client &orginal);
    ~channel();
    channel & operator=(const channel &orginal);
    void send_msg(const std::string& sender, const std::string& message, client* senderClient) const;
    bool is_member(client* user) const;
    channel* getChannel();
    void remove_user(client* client);
    void remove_operator(client* client);
    bool is_operator(client* client) const;
    void add_user(client* client);
    void process_whois_response(const std::string& response) const;
    const std::string& getName() const;
    void send_notice(const std::string& sender, const std::string& notice) const;
    channel* get_channel_by_name(const std::string& channelName);
};

#endif