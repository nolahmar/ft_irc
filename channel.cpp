#include "channel.hpp"
#include <algorithm>

channel::channel(std::string& name, int owner, std::string topic, std::string key)
		: Name(name), Owner(owner), Key(key), Topic(topic), _limit(-1) {
        Admin.push_back(owner); // L'utilisateur qui crée le canal devient automatiquement administrateur
        Users.push_back(owner);
}

channel::channel(): Owner(-1), _limit(-1) {}

channel::channel(const  channel &original)
: Name(original.Name), Owner(original.Owner), Users(original.Users), Key(original.Key),
          Topic(original.Topic), _limit(original._limit), Admin(original.Admin)
{

}

 void channel::add_user(int userId) { 
    Users.push_back(userId);
}

channel &channel::operator=(const channel &original)
{
	if (this != &original) {
            Name = original.Name;
            Owner = original.Owner;
            Users = original.Users;
            Key = original.Key;
            Topic = original.Topic;
            _limit = original._limit;
            Admin = original.Admin;
            // Operators = original.Operators;
        }
        return *this;
    }

void channel::broadcast(const std::string& message, std::map<int, client>& clients, int curr_client_fd)
{
    for (std::vector<int>::iterator it = Users.begin(); it != Users.end(); ++it)
    {
        if (*it == curr_client_fd)
            continue;
        clients[*it].write(*it, message);
    }
}


// void channel::remove_client(const client* clientToRemove)
// {
//     for (std::vector<client*>::iterator it = clients.begin(); it != clients.end();)
//     {
//         if (*it == clientToRemove)
//         {
//             it = clients.erase(it);
//             break;
//         }
//         else
//         {
//             ++it;
//         }
//     }
// }

bool channel::is_member(int fd) const {
    if (std::find(Users.begin(), Users.end(), fd) != Users.end() ||
        this->is_admin(fd) || Owner == fd) {
        return true;
    }
    return false;
}

bool channel::is_admin(int fd) const {
    for (std::vector<int>::const_iterator it = Admin.begin(); it != Admin.end(); ++it) {
        if (*it == fd) {
            return true;
        }
    }
    return false;
}

bool channel::is_operator(int userId) const {
  return this->Operators.count(userId) != 0;
}

channel* channel::get_channel_by_name(const std::string& channelName, const std::vector<channel*>& channels) {
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->get_name() == channelName) {
            return channels[i];
        }
    }
    return NULL;
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

// std::vector<int>& channel::get_operators() {
//     return Operators;
// }

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

void channel::add_operator(int userId)
{
  this->Operators.insert(userId);
}

void channel::remove_user(int userId)
{
    std::vector<int>::iterator it = std::find(Users.begin(), Users.end(), userId);

    if (it == Users.end())
        return;
    Users.erase(it);
}

void channel::set_limit(int limit)
{
    _limit = limit;
}

channel::~channel()
{
	std::cout << "Destrctor" << std::endl;
}

// {'i'}
void channel::change_invite_only_mode(std::string& mode) {
  switch (mode) {
    case "+i":
      this->mode.insert('i');
      break;
    default:
      this->mode.erase('i');
      break;
  }  
}

void channel::change_topic_mode(std::string& mode) {
  switch (mode) {
    case "+t":
      this->mode.insert('t');
      break;
    default:
      this->mode.erase('t');
      break;
  }  
}

bool channel::change_key_mode(std::vector<std::string>& args, std::string& mode, int fd) {
 switch (mode) {
   case "+k":
     if (args.size() < 3) {
        ft_response(fd, "ERR_NEEDMOREPARAMS");
        return false;
     }
     this->mode.insert('k');
     this->Key = args[2];
     break;
  default:
    this->mode.erase('k');
    this->key = "";
 } 
 return true;
}

bool channel::change_operator_mode(std::vector<std::string>& args, std::string& mode, int fd) {
  if (args.size() < 3) {
    ft_response(fd, "ERR_NEEDMOREPARAMS");
    return false;
  } 
  // check if the user exist
  // check if the user is a member
  switch (mode)
    case "+o":
      this->Operators.insert(userFd);
      break;
    default:
      this->Operators.erase(userFd);
  }
  return true;
}

bool channel::change_limit_mode(std::vector<std::string>& args, std::string& mode) {
  switch (mode) {
    case "+l":
        // you can add a check if the number is valid
       if (args.size() < 3) {
          ft_response(fd, "ERR_NEEDMOREPARAMS");
          return false;
       }
      this->mode.insert('l');
      this->_limit = atoi(args[2]);
      break;
    default:
      this->mode.erase('l');
      this->_limit = 0;
  } 
  return true;
}
