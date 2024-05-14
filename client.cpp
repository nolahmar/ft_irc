#include "client.hpp"
#include "channel.hpp"

client::client(int fd)
{
	std::cout << "constrctor dinislisation" << std::endl;
}

client::client()
{
	std::cout<< "constrctor par defaut" << std::endl;
}

client::client(const  client &orginal)
{
	std::cout << "constrctor par copier" << std::endl;
	*this = orginal;
}

client &client::operator=(const client &orginal)
{
	std::cout << "operator assinment" << std::endl;
	if(this != &orginal)
	{
		this->fd = orginal.fd;
		this->nickname = orginal.nickname;
		this->username = orginal.username;
		this->realname = orginal.realname;

	}

	return *this;
}

// stntax: USER <username> <hostname> <servername> <realname>

// void client::User(const std::string &userCmd)
// {
// 	std::istringstream iss(userCmd);

// 	std::string cmd;
// 	std::string	uname;
// 	std::string	hname;
// 	std::string	Nname;
// 	std::string	rname;

// 	iss >> cmd >> uname >> hname >> Nname >>  rname ;
// 	this->username = uname;
// 	this->hostname = hname;
// 	this->realname = rname;
// 	this->nickname = Nname;
// 	std::getline(iss,rname);

// 	std::cout << "user details :\n" ;
// 	std::cout << "nickname: " <<  username << "\n" ;
// 	std::cout << "hostname: " << hostname << "\n";
// 	std::cout << "realname: " << realname << "\n" ;
// 	std::cout << "hostname: " << hostname << "\n" ;
// }

client::~client()
{
	std::cout << "Destrctor" << std::endl;
}

const std::string& client::getNickname() const {
        return nickname;
    }

client* client::getClient(const std::string& nickname) const {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i]->getNickname() == nickname) {
            return clients[i];
        }
    }
    return nullptr;
}

void client::join_channel(channel* channel) {
	ChannelPtr = channel;
}
