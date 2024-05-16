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
        std::vector<channel*>  channels;
        std::vector<client*> clients;
        channel* ChannelPtr;
        
    public:
    client(int fd);
    client();
    client & operator=(const client &orginal);
    ~client();
    void User(const std::string &userCmd);
    void write(const std::string& message) const;
    const std::string& getNickname() const;
    client* getClient(const std::string& nickname) const;
    void send_pong(const std::string& token);
    void send_whois(const std::string& target, const std::string& nickname);
    bool is_authorized_for_whois() const;
    void send_to_server(const std::string& message) const;
    std::string wait_for_response() const;
    void process_whois_response(const std::string& response) const;
    void invite_to_channel(client* invitedClient, channel* channel);
    void join_channel(channel* channel);
    void quit_network(client* client, const std::string& reason) const;

};

#endif