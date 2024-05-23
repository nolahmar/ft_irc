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

void client::write(int fd, const std::string& message) const {
    send(fd, (message + "\r\n").c_str(), (message + "\r\n").length(), 0);
}

void client::sendMessage(const std::string& message) {
    // Envoyer le message au socket du client
    send(fd, message.c_str(), message.length(), 0);
}

// void client::quiter() {
//     if (!channels.empty()) {
//         for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
//             channel* currentChannel = *it;
//             currentChannel->remove_client(this);
//         }
//         channels.clear();
//     }
// }

void client::quit_network(std::map<int, client>& clients, int fd, const std::string& reason) const {
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        int client_fd = it->first;
        client& cl = it->second;
        if (client_fd != fd) {
            const std::vector<channel*>& channels = cl.get_channel();
            for (std::vector<channel*>::const_iterator it_channel = channels.begin(); it_channel != channels.end(); ++it_channel) {
                channel* currentChannel = *it_channel;
                currentChannel->remove_client(this);
            }
        }
    }
    std::cout << "ERROR: Closing Link: <servername> (Killed by operator (" << reason << "))" << std::endl;
}


void client::join_channel(channel* channel) {
	ChannelPtr = channel;
}

void client::invite_to_channel(int fd, client* invitedClient, channel* channel) {
    if (!channel) {
        write(fd, ERR_NOSUCHCHANNEL(get_nickname(), "ERR_NOSUCHCHANNEL"));
        return;
    }
    if (!channel->is_member(this)) {
        write(fd, ERR_NOTONCHANNEL(get_nickname(), channel->get_name()));
        return;
    }

    if (channel->is_member(invitedClient)) {
        write(fd, ERR_USERONCHANNEL(get_nickname(), channel->get_name()));
        return;
    }

    // Envoyer un message d'invitation à l'utilisateur invité
    invitedClient->write(fd, "INVITE " + get_nickname() + " " + channel->get_name());
    invitedClient->join_channel(channel);

    // Envoyer un message de confirmation à l'utilisateur qui a envoyé l'invitation
    write(fd, RPL_INVITING(get_nickname(), channel->get_name()));
}


void client::remove_channel(const channel* channelToRemove)
{
    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (*it == channelToRemove)
        {
            it = channels.erase(it);
            break;
        }
    }
}

int client::get_fd() const
{
	return fd;
}

std::string client::get_prefix() const 
{
     std::string user;
     std::string host;

    if (!username.empty()) {
        user = "!" + username;
    }

    if (!hostname.empty()) {
        host = "@" + hostname;
    }

    return nickname + user + host;
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

void           client:: set_servername(const std::string    server_n)
{
	this->servername = server_n;
}

client::~client()
{
	std::cout << "Destrctor" << std::endl;
}
