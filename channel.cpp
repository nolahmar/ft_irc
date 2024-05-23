#include "channel.hpp"

channel::channel(std::string& name, int owner, std::string topic, std::string key)
{
		this->Name = name;
		this->Owner = owner;
		this->Key = key;
		this->Topic = topic;
}

channel::channel()
{

}

channel::channel(const  channel &orginal)
{
	*this = orginal;
}

channel &channel::operator=(const channel &orginal)
{
	if(this != &orginal)
	{
		this->Name = orginal.Name;
		this->Admin = orginal.Admin;
		this->Owner = orginal.Owner;
		this->Users = orginal.Users;
		this->Key = orginal.Key;
		this->Topic = orginal.Topic;
	}

	return *this;
}

void channel::broadcast(const std::string& message, client* exclu)
{
    for (std::vector<client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (*it == exclu)
        {
            continue;
        }

        (*it)->sendMessage(message);
    }
}


void channel::remove_client(const client* clientToRemove)
{
    for (std::vector<client*>::iterator it = clients.begin(); it != clients.end();)
    {
        if (*it == clientToRemove)
        {
            it = clients.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}

client* channel::getClientById(int userId) const {
    for (std::vector<client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->get_fd() == userId) {
            return *it;
        }
    }
    return NULL;
}

bool channel::is_member(client* user) const {
    std::string userNickname = user->get_nickname();
    for (size_t i = 0; i < Users.size(); ++i) {
        client* currentUser = getClientById(Users[i]);
        if (currentUser != NULL && currentUser->get_nickname() == userNickname) {  // Remplacer NULL par NULL
            return true;
        }
    }
    return false;
}

channel* channel::get_channel_by_name(const std::string& channelName, const std::vector<channel*>& channels) {
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->get_name() == channelName) {
            return channels[i];
        }
    }
    return NULL;
}

bool channel::isExternalMessage() const {
    return _allowExternalMessages;
}

void channel::setExternalMessage(bool allow) {
    _allowExternalMessages = allow;
}

/* gesters*/

std::string channel::get_name() const
{
	return this->Name;
}

std::string channel::get_key() const
{
	return this->Key;
}

std::string channel::get_Topic() const
{
	return this->Topic;
}

std::vector<int>  &channel::getadmin()
{
	return Admin;
}

int channel::getOwner() const
{
	return  Owner;
}

std::vector<int> &channel::get_Users()
{
	return Users;
}

/*seters */

void channel::set_name(const std::string  namee)
{
	this->Name = namee;
}

void channel::set_key(const std::string keyy)
{
	this->Key = keyy;
}

void  channel::set_topic(const std::string topic)
{
	this->Topic = topic;
}

void channel::set_Admin(const std::vector<int> &admin)
{
	this->Admin = admin;
}

void channel::set_Owner(const int owner)
{
	this->Owner = owner;
}

void channel::set_Users(const std::vector<int> users)
{
	this->Users =  users;
}

void channel::addUser(int userId)
{
   Users.push_back(userId);
}

void channel::set_limit(int limit)
{
    _limit = limit;
}

channel::~channel()
{
	std::cout << "Destrctor" << std::endl;
}