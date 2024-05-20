#ifndef command_hpp
#define command_hpp

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <unistd.h>     // for close()
#include <sys/socket.h> // for socket-related functions
#include <unistd.h>     // for close()
#include <cstring>      // for memset()
#include <iostream>     // for cout
#include <string> 
#include <string>
#include <algorithm>
#include "client.hpp"


class command
{
	private:

	public:
	command(const command& src);
	void excute(const std::string& command,const std::vector<std::string>& parameters,std::map< int ,client> &clients,int fd,std::string password,std::vector<channel *> &channels);
	command();
	void ft_kick(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd ,std::vector<channel *> &channels);
	void	ft_user(std::vector<std::string> parametres ,std::map< int ,client> &clients,int fd);
	void ft_pass(std::vector<std::string> parametres ,std::map< int ,client> &clients ,int fd ,std::string pass);
	void ft_join(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd,std::vector<channel *> &channels);
	void ft_nick(std::vector<std::string> parametres ,std::map< int ,client> &clients ,int fd);
	void ft_topic(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd);
	void ft_Quit(std::vector<std::string> parameters, std::map<int, client>& clients, int fd, std::vector<channel *>& channels);
	void ft_privmsg(std::vector<std::string> args, std::map<int, client>& clients, int fd);
	void ft_notice(std::vector<std::string> args, std::map<int, client>& clients, int fd);
	void ft_ping(std::vector<std::string> args, std::map<int, client>& clients, int fd);
	void ft_part(std::vector<std::string> args, std::map<int, client>& clients, int fd);
	void ft_kill(client* operatorClient, std::map<int, client>& clients, int fd, const std::string& reason);
	void cap(const std::string& subcommand, const std::string& capabilities, int fd);
	void invite(int fd, const std::vector<std::string>& args, std::map<int, client>& clients, std::vector<channel*>& channels);
	void mode(std::vector<std::string> args, std::map<int, client>& clients, std::vector<channel*>& channels, int fd);
	// std::string welcomemsg(void);

	~command();

};

#endif