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
        int Owner;
        std::vector<int>  Users;
        std::string Key;
        std::string Topic;
    public:
        std::vector<int>  Admin;
        channel(std::string& name, int owner, std::string topic, std::string key);
        channel();
        channel(const channel &orginal);
        channel & operator=(const channel &orginal);
        std::string get_name() const;
        std::string get_key() const;
        std::string get_Topic() const;
        std::vector<int>  &getadmin();
        int getOwner() const;
        std::vector<int> &get_Users();
        void set_name(const std::string  namee);
        void set_key(const std::string keyy);
        void set_topic(const std::string topic);
        void set_Admin(const std::vector<int> &admin);
        void set_Owner(const int owner);
        void set_Users(const std::vector<int> users);
        void addUser(int userId);
        void broadcast(const std::string& message, Client* exclu);
        void remove_client(client* client);
        bool is_member(client* user) const ;
        channel* get_channel_by_name(const std::string& channelName, const std::vector<channel*>& channels);
        ~channel();
};

#endif