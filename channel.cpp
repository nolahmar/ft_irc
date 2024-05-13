#include "channel.hpp"

channel::channel(std::string& Name, client * owner, std::string topic)
{
	std::cout << "constrctor dinislisation" << std::endl;
}

channel::channel()
{
	std::cout<< "constrctor par defaut" << std::endl;
}

channel::channel(const  client &orginal)
{
	std::cout << "constrctor par copier" << std::endl;
	*this = orginal;
}

channel &channel::operator=(const channel &orginal)
{
	std::cout << "operator assinment" << std::endl;

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

channel::~channel()
{
	std::cout << "Destrctor" << std::endl;
}

channel* channel::getChannel() {
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->Name == Name) {
            return channels[i];
        }
    }
    return nullptr;
}

void channel::remove_operator(client* client) {
        auto it = std::find(Operators.begin(), Operators.end(), client);
        if (it != Operators.end()) {
            Operators.erase(it);
        }
    }

bool channel::is_operator(client* client) const {
        return std::find(Operators.begin(), Operators.end(), client) != Operators.end();
    }

void channel::add_user(client* client) {
        Users.push_back(client);
    }
