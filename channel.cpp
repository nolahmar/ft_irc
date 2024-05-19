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
void Channel::broadcast(const std::string& message, lient* exclu)
{
    client_iterator it_b = clients.begin();
    client_iterator it_e = clients.end();

    while (it_b != it_e)
    {
        if (*it_b == exclu)
        {
            it_b++;
            continue;
        }

        (*it_b)->write(message);
        it_b++;
    }
}

void Channel::remove_client(client* client)
{
    std::vector<std::string>iterator::it = std::find(clients.begin(), clients.end(), client);
    if (it != clients.end())
    {
        clients.erase(it);
    }
}

bool channel::is_member(client* user) const {
    for (size_t i = 0; i < Users.size(); ++i) {
        if (Users[i] == user) {
            return true;
        }
    }
    return false;
}

channel* channel::get_channel_by_name(const std::string& channelName, const std::vector<channel*>& channels) {
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->getName() == channelName) {
            return *it;
        }
    }
    return nullptr;
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


channel::~channel()
{
	std::cout << "Destrctor" << std::endl;
}