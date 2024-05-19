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