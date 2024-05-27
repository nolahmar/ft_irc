#include "client.hpp"
#include "channel.hpp"
#include <algorithm>

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
    std::cout << "fd: " << fd << std::endl;
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


void client::invite_to_channel(int fd, std::map<int, client>::iterator& invitedClient, channel* channel) {
    int target = invitedClient->first;
    //check mode !!!!! on utilison std::vector<std::string>Operators
    // Envoyer un message d'invitation à l'utilisateur invité !!! Merciiii
    write(target, "INVITE " + get_nickname() + " " + channel->get_name());
    // Join target to the target channel
    invitedClient->second.channels.push_back(channel);
    channel->addUser(target);
    // Envoyer un message de confirmation à l'utilisateur qui a envoyé l'invitation !!! Merciiii
    write(fd, RPL_INVITING(get_nickname(), channel->get_name()));
}



void client::remove_channel(const channel* channelToRemove)
{
    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->get_name() == channelToRemove->get_name())
        {
            it = channels.erase(it);
            return;
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

channel* client::get_channel_by_name(const std::string& name) const {

    for (std::vector<channel*>::const_iterator it = this->channels.begin(); it != this->channels.end(); ++it)
    {
        if ((*it)->get_name() == name) 
            return *it;
    }
    return NULL;
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

std::vector<std::string> &client::get_operators() {
    return Operators;
}

void client::set_operators(const std::vector<std::string>& operators) {
    Operators = operators;
}

void client::add_operator(std::string userId) {
    Operators.push_back(userId);
}

void client::remove_operator(std::string& mode) 
{
    // Recherche et suppression de l'utilisateur du vecteur des opérateurs
    std::vector<std::string>::iterator it;
    for (it = Operators.begin(); it != Operators.end(); ++it) {
        if (*it == mode) {
            Operators.erase(it);
            break;
        }
    }
}

void client::set_mode(char mode, bool active) {
        if (active) {
            add_mode(std::string(1, mode));
        } else {
            remove_mode(std::string(1, mode));
        }
    }

void client::add_mode(const std::string& mode) {
        if (std::find(modes.begin(), modes.end(), mode) == modes.end()) {
            modes.push_back(mode);
        }
    }

void client::remove_mode(const std::string& mode) {
        std::vector<std::string>::iterator it = std::find(modes.begin(), modes.end(), mode);
        if (it != modes.end()) {
            modes.erase(it);
        }
    }

// bool channel::is_operator(int userId) const {
//     // Vérifie si l'utilisateur est un opérateur en vérifiant s'il est présent dans le vecteur des opérateurs
//     std::vector<int>::const_iterator it;
//     for (it = Operators.begin(); it != Operators.end(); ++it) {
//         if (*it == userId) {
//             return true;
//         }
//     }
//     return false;
// }


client::~client()
{
	std::cout << "Destrctor" << std::endl;
}
