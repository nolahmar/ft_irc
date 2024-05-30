#ifndef channel_hpp
#define  channel_hpp

#include "client.hpp"
#include <cstddef>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include <vector>
#include <cstring>
#include <set>

class channel
{
    private:
        std::string Name;
        int Owner;
        std::vector<int>  Users;
        std::string Key;
        std::string Topic;
        std::set<int> Operators; // Vecteur pour stocker les identifiants des opérateurs de canal
        std::set<char> mode;
        int _limit; // Variable pour stocker la limite du nombre d'utilisateurs
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
        void set_limit(int limit);
        void addUser(int userId);
        void remove_user(int userId);
        void broadcast(const std::string& message, std::map<int, client>& clients, int curr_client_fd);
        // void remove_client(const client* clientToRemove);
        // bool is_member(client* user) const ;
        bool is_member(int userId) const ;
        bool is_admin(int userId) const;
        bool is_operator(int userId) const;
        void add_user(int userId);
        channel* get_channel_by_name(const std::string& channelName, const std::vector<channel*>& channels);
        ~channel();
        void change_invite_only_mode(std::string& mode);
        void change_topic_mode(std::string& mode);
        bool change_key_mode(std::vector<std::string>& args, std::string& mode, int fd);
        bool change_operator_mode(std::map<int, client>& clients, std::vector<std::string>& args, std::string& mode, int fd);
        bool change_limit_mode(std::vector<std::string>& args, std::string& mode, int fd);
};

void ft_response(int fd, const char* message);

#endif
