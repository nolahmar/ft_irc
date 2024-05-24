#include "client.hpp"
#include "channel.hpp"

client::client(): fd(-1), id(-1), ChannelPtr(NULL)
{
	state = "none"; // pass - usernam mazl medkhl
	
}

client::client(const client& original) {
    fd = original.fd;
    id = original.id;
    nickname = original.nickname;
    username = original.username;
    realname = original.realname;
    hostname = original.hostname;
    password = original.password;
    ChannelPtr = original.ChannelPtr;
    servername = original.servername;
    channels = original.channels;
}

client& client::operator=(const client& original) {
    if (this != &original) {
        fd = original.fd;
        id = original.id;
        nickname = original.nickname;
        username = original.username;
        realname = original.realname;
        hostname = original.hostname;
        password = original.password;
        ChannelPtr = original.ChannelPtr;
        servername = original.servername;
        channels = original.channels;
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
    std::string quitMessage = "QUIT :" + reason + "\n";
    write(fd, quitMessage);
    close(fd);
    clients.erase(fd);
}


void client::join_channel(channel* chan) {
    if (!chan->is_member(id)) {
        chan->add_user(id);
        channels.push_back(chan);
    }
}

void client::invite_to_channel(int fd, client* invitedClient, channel* channel) {
    if (!channel) {
        write(fd, ERR_NOSUCHCHANNEL(get_nickname(), channel->get_name()));
        return;
    }
    if (!channel->is_member(invitedClient->get_fd()) && channel->getOwner() != fd) {
        write(fd, ERR_NOTONCHANNEL(get_nickname(), channel->get_name()));
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

int client::get_id() const {
    return id;
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
