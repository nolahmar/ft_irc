#ifndef client_hpp
#define  client_hpp

#include <iostream>
#include <sstream>
#include <cstddef>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include<map>

#define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " " + channel + " :Cannot send to channel"
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token
#define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args
#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"
#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define RPL_PART(source, channel, reason)                       ":" + source + " PART :" + channel + " " + reason
#define ERR_UNKNOWNMODE(nickname, mode) "472 " + nickname + " " + mode + " :is unknown mode char to me"
#define RPL_PONG(prefix, token) ":" + prefix + " PONG :" + token
#define ERR_USERONCHANNEL(source, channel) "443 " + source + " " + channel + " :is already on channel"
#define RPL_INVITING(user, channel) "341 " + user + " " + channel + " :Inviting"


class channel;
class client
{
    private:
        std::string state;
        int fd;
        int id;                                                                                                                                                                                                                                                                                                                                
        std::string port;
        std::string nickname;
        std::string username;
        std::string realname;
        std::string hostname;
        std::string password;
        channel* ChannelPtr;
        std::string servername;
        std::vector<std::string>  Operators;
        std::vector<std::string> modes;

    public:
    /* Getters */
        std::vector<channel*>  channels;

        int             get_fd() const;
        int             get_port() const;
        std::string     get_nickname() const;
        std::string     get_username() const;
        std::string     get_realname() const;
        std::string     get_hostname() const;
        int get_id() const;
        std::vector<channel*>       get_channel() const;
        channel* get_channel_by_name(const std::string& name) const;
        std::string is_registered();
        std::string get_password() const;
        void sendMessage(const std::string& message);
        void quiter();
        void invite_to_channel(int fd, std::map<int, client>::iterator& invitedClient, channel* channel);
        std::string get_prefix() const;
        void write(int fd, const std::string& message) const;
        void quit_network(std::map<int, client>& clients, int fd, const std::string& reason) const;
        void join_channel(channel* channel);
        void remove_channel(const channel* channelToRemove);
        std::vector<std::string> &get_operators();
        void set_operators(const std::vector<std::string>& operators);
        void add_operator(std::string userId);
        void remove_operator(std::string &mode);
        void set_mode(char mode, bool active);
        void add_mode(const std::string& mode);
        void remove_mode(const std::string& mode);

    /**setes*/
        void            set_nickname(const std::string nickn);
        void            set_username(const std::string usern);
        void            set_realname(const std::string realn);
        void            set_hostname(const std::string hostn);
        void            set_channel(const std::vector<channel*> chan);
        void            set_registered(std::string status);
        void            set_servername(const std::string    server_n);
        client();
        client & operator=(const client &orginal);
        client(const client &orginal);
        ~client();
};

#endif