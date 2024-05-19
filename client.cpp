#include "client.hpp"
#include "channel.hpp"

client::client()
{
	state = "none"; // pass - usernam mazl medkhl
	
}

client::client(const client &orginal)
{
	
	*this = orginal;
}

client &client::operator=(const client &orginal)
{
	
	if (this != &orginal)
	{
		this->fd = orginal.fd;
		this->nickname = orginal.nickname;
		this->username = orginal.username;
		this->realname = orginal.realname;
	}

	return *this;
}

void client::sendMessage(const std::string& message) {
        std::cout << "Sending message to client: " << message << std::endl;
}

void client::quiter()
{
	if (channels != nullptr)
    {
        channels->remove_client(this);
        channels = nullptr;
    }
}

void client::quit_network(std::map<int, client>& clients, int fd, const std::string& reason) const {
    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        channel* channel = *it;
        channel->remove_client(client);
    }
    std::cout << "ERROR: Closing Link: <servername> (Killed by operator (" << reason << "))" << std::endl;
}

void client::invite_to_channel(client* invitedClient, channel* channel) {
    if (!channel) {
        write("ERR_NOSUCHCHANNEL " + nickname + " " + channel->getName());
        return;
    }
    if (!channel->is_member(this)) {
        write("ERR_NOTONCHANNEL " + nickname + " " + channel->getName());
        return;
    }

    if (channel->is_member(invitedClient)) {
        write("ERR_USERONCHANNEL " + nickname + " " + channel->getName());
        return;
    }
    // Envoyer un message d'invitation à l'utilisateur invité
    invitedClient->write("INVITE " + nickname + " " + channel->getName());
    invitedClient->join_channel(channel);

    // Envoyer un message de confirmation à l'utilisateur qui a envoyé l'invitation
    write("RPL_INVITING " + channel->getName());
}

int client::get_fd() const
{
	return fd;
}



std::string client::is_registered()
{
    return state;
}

std::string client::get_password() const 
{
	return this->password;
}

void client::set_registered(std::string status)
{
        this->state = status;
}

std::string client::get_nickname() const
{
	return nickname;
}
std::string client::get_username() const
{
	return username;
}
std::string client::get_realname() const
{
	return realname;
}
std::string client::get_hostname() const
{
	return hostname;
}

std::vector<channel *> client::get_channel() const
{
	return channels;
}

/* Setters */

void client::set_nickname(const std::string nickn)
{
	this->nickname = nickn;
}

void client::set_username(const std::string usern)
{
	this->username = usern;
}

void client::set_realname(const std::string realn)
{
	this->realname = realn;
}

void client::set_hostname(const std::string hostn)
{
	this->hostname = hostn;
}

void client::set_channel(const std::vector<channel *> chan)
{
	this->channels = chan;
}

client::~client()
{
	std::cout << "Destrctor" << std::endl;
}
