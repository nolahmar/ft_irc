#include "channel.hpp"
#include"command.hpp"
#include "client.hpp"
#include "server.hpp"

// #include "ft_bot.hpp"
void welcomemsg(void)
{
	std::string welcome = RED;
	welcome.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	welcome.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	welcome.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	welcome.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	welcome.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	welcome.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	welcome.append(BLEU);
	welcome.append("You need to login so you can start chatting OR you can send HELP to see how :) \n");
	welcome.append(RS);
    std::cout << welcome<< std::endl;
	//return (welcome);
}

bool server::signn = true;
server::server()
{
    
}

server::server(std::string p)
{
    this->pass= p;
}
void server::signalHandler(int i)
{
    signn = false;
    (void)i;
     throw ("throw signal \n");
}

void server::ft_close()
{
    
    for(std::map<int, client>::iterator n = clients.begin(); n != clients.end(); n++)
        close (n->first);
    close(serverSocket);
}

void server::ft_server()
{
    int c = 0;
    command executeCommand = command();
    //bot bot;


    serverSocket =  socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cout << "error in create socket \n";
        close (serverSocket);
    }
   struct sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(8080);
serverAddr.sin_addr.s_addr = INADDR_ANY;
int optval = 1;

// Set SO_REUSEADDR
if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) 
{
    close(serverSocket);
    throw "Error setting SO_REUSEADDR socket option";
}

// Set SO_REUSEPORT
if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1) 
{
    close(serverSocket);
    throw "Error setting SO_REUSEPORT socket option";
}
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        close(serverSocket);
        throw "Error binding socket";
    }
    if (listen(serverSocket, 10) == -1)
    {
        close(serverSocket);
        throw "Error listening";
    }
     welcomemsg();
    std::cout << YELLOW << "Server listening .......\n" << BD;
    
    std::vector<pollfd> fds;
    pollfd t;
    t.fd = serverSocket;
    t.events = POLLIN;
    fds.push_back(t);
    while (signn != false)
    {
        c = poll(fds.data(), fds.size(), -1);
        if (c == -1)
        {
            std::cout << "error in function poll \n";
        }
        else if (c > 0)
        {
            for(unsigned int i = 0; i < fds.size() ; ++i)
            {
                if (fds[i].revents & POLLIN)
                {
                    if (fds[i].fd == serverSocket)
                    {
                        struct sockaddr_in clientAddr;
                     
		                socklen_t clientAddrSize = sizeof(clientAddr);
                        int clientsock = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);
                        std::cout << "fd ======" << clientsock << std::endl;
                        if (clientsock == -1)
                        {
                            
                            close(serverSocket);
                            close (clientsock);
                            throw "Error in accept";
                        }
                        else 
                        {
                            pollfd t;
                            t.fd = clientsock;
                            t.events = POLLIN;
                            fds.push_back(t); 
                            
                            client *newClient = new client();
                            clients[t.fd] = *newClient;
                            std::cout << RS << "accept connection ......." << BD << std::endl;
                        }
                    }
                    else
                    {
                        char buffer[1024];
                        std::string total;
                        int bytesReceived = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                        std::cout << "=========" << fds[i].fd << std::endl;
                        if (bytesReceived == -1)
                        {
                            close(fds[i].fd);
                           // close(serverSocket);
                           // throw "error in recv";
                        }
                        else if (bytesReceived == 0) 
                        {
                            std::cout <<  BLEU << "😢 client disconnected" <<  BD  << std::endl;
                            close(fds[i].fd);
                            fds.erase(fds.begin() + i);
                            clients.erase(fds[i].fd);
                            --i;
                       }
                       else 
                       {
                            std::string line = std::string(buffer, bytesReceived);
                            std::vector<std::string> tokens;
                            std::cout << "line ==>" << line << std::endl;
                            std::istringstream iss(line);
                            std::string token;
                            std::string com ;
                             iss >> com;
                            while (iss >> token) 
                            {
                                tokens.push_back(token);
                            }
                                executeCommand.excute(com,tokens, clients,fds[i].fd,pass,channels);
                       }
                    }
               }
        }
    }
    }    
}
