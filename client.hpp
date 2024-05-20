#ifndef client_hpp
#define  client_hpp

#include <iostream>
#include <sstream>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include <vector>
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


class channel;
class client
{
    private:
        std::string state;
        int fd;                                                                                                                                                                                                                                                                                                                                 
        std::string port;
        std::string nickname;
        std::string username;
        std::string realname;
        std::string hostname;
        std::string password;
        channel* ChannelPtr;
        // std::vector<channel*>  channels;

    public:
    /* Getters */
        std::vector<channel*>  channels;

        int             get_fd() const;
        int             get_port() const;
        std::string     get_nickname() const;
        std::string     get_username() const;
        std::string     get_realname() const;
        std::string     get_hostname() const;
        std::vector<channel*>       get_channel() const;
        std::string is_registered();
        std::string get_password() const;
        void sendMessage(const std::string& message);
        void quiter();
        void invite_to_channel(client* invitedClient, channel* channel);
        std::string get_prefix() const;
        void write(const std::string& message) const;
        void quit_network(std::map<int, client>& clients, int fd, const std::string& reason) const;
        void join_channel(channel* channel);
        void remove_channel(const channel* channelToRemove);

    /**setes*/
        void            set_nickname(const std::string nickn);
        void            set_username(const std::string usern);
        void            set_realname(const std::string realn);
        void            set_hostname(const std::string hostn);
        void            set_channel(const std::vector<channel*> chan);
        void            set_registered(std::string status);
        client();
        client & operator=(const client &orginal);
        client(const client &orginal);
        ~client();
};

#endif