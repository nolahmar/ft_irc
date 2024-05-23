#include "channel.hpp"
#include "client.hpp"
#include "command.hpp"
#include "server.hpp"

int main(int argc,char **argv)
{
    //argv = argv;
    (void)argv;
    if(argc != 3)
    {
        std::cerr << "usage : ./ircserv [port] [password]" << std::endl;
            return (1);
    }
    try{
        server serverClient = server(argv[2]);
        serverClient.ft_server();
    }
    catch(std::string s)
    {
        std::cout << "error ==>" << s << std::endl;
    }
      return (0);

}