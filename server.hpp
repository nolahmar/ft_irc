#ifndef server_hpp
#define  server_hpp

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sys/poll.h>
#define RED "\e[1;31m" 
#define GREEN "\e[1;32m" 
#define YELLOW "\e[1;33m"
#define BD "\e[1;00m"
#define RS "\033[1;35m"
#define BLEU "\033[1;34m"
#include <map>
#include "channel.hpp"
#include "client.hpp"
#include "command.hpp"

class server
{
    private:
    std::string pass;
    std::map<int,client>  clients;
    public:
    server();
    std::vector<channel *> channels;
    server(std::string p);
    void ft_server();
    void signalHandler(int i);
    void ft_close();
    int serverSocket;
    static bool signn;

};

#endif