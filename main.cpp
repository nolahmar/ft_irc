#include "channel.hpp"
#include "client.hpp"

int main(int argc,char **argv)
{
    if(argc != 3)
    {
        std::cerr << "usage : ./ircserv [port] [password]" << std::endl;
            return (1);
    }

    return (0);
}