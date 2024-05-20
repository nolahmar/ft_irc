#include "command.hpp"
#include "client.hpp"
#include "server.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>

void ft_response(int fd, const char* message)
{   
    // Example of sending an IRC response back to the client
    char response[512]; // Assuming maximum response length is 512 characters
    snprintf(response, sizeof(response), ":%s %s\r\n", "SERVER", message);
    send(fd, response, strlen(response), 0);
}

// std::string	command::welcomemsg(void)
// {
// 	std::string welcome = RED;
// 	welcome.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
// 	welcome.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
// 	welcome.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
// 	welcome.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
// 	welcome.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
// 	welcome.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
// 	welcome.append(BLUE);
// 	welcome.append("You need to login so you can start chatting OR you can send HELP to see how :) \n");
// 	welcome.append(RESET);
// 	return (welcome);
// };





// hana 3la ha std::cout << GREEN <<  "data: ======>> "  << BD << std::string(buffer, bytesReceived) << std::endl;sb kola function achnow kadkhl
// fi prameter dilha

void command::excute(const std::string& command,const std::vector<std::string>& parameters,std::map< int ,client> &clients,int fd,std::string password,std::vector<channel *> &channels)
{

		if (clients[fd].is_registered() == "none" && command != "pass")
		{
			ft_response(fd, "You should enter the passwotrd");
				return ;
		}

		if(clients[fd].is_registered() != "registed"  && command != "user" && command != "pass")
		{	
			ft_response(fd, "YOu are not registred yet");
			return ;
		}

        if (command == "JOIN") 
		{
            // JOIN command: Join a channel
            if (parameters.size() >= 1) 
			{
                ft_join(parameters,clients,fd,channels);
            } else 
			{
				ft_response(fd,"ERR_NEEDMOREPARAMS"); 
            }
        } else if (command == "KICK")
		 {
            // KICK command: Kick a user from a channel
            if (parameters.size() >= 2) 
			{
               //PASS command successful: Client registered/ 
				ft_kick(parameters, clients,fd,channels);
            } else 
			{
				ft_response(fd,"ERR_NEEDMOREPARAMS"); 
            }
        } else if (command == "Quite")
		 {
            // Quite command: Quite a user to a channel
            
               ft_Quit(parameters,clients,fd, channels);
           
        } else if (command == "user")
		 {
            // MODE command: Change the mode of a channel
            if (parameters.size() >= 4) 
			{
                ft_user(parameters,clients,fd);

            } else {

				ft_response(fd,"ERR_NEEDMOREPARAMS");      
		 }
        }else if(command == "pass")
		{
			if(parameters.size() >=1)
			{
				// std::cout << "and dkhelt l execute and i choose pass" << std::endl;
				ft_pass(parameters,clients,fd,password);

			}else
			{
				ft_response(fd,"ERR_NEEDMOREPARAMS");
			}
		}else if(command == "Nick")
		{
			if(parameters.size() >= 1)
			{
				ft_nick(parameters,clients,fd);
			}else
			{
				ft_response(fd,"ERR_NEEDMOREPARAMS");
			}
		}else if(command == "Topic")
		{
			
			ft_topic(parameters,clients,fd);

		}
		else if (command == "PRIVMSG")
	{
        ft_privmsg(parameters, clients, fd);
    }
	else if (command == "NOTICE")
	{
        ft_notice(parameters, clients, fd);
    }
	else if (command == "PING")
	{
        ft_ping(parameters, clients, fd);
    }
	else if (command == "PART")
	{
        ft_part(parameters, clients, fd);
    }
	else if (command == "KILL")
	{
        ft_kill(nullptr, clients, fd, "No reason given");
    }
	else if (command == "CAP")
	{
        cap(parameters[0], parameters[1], fd);
    }
	else if (command == "INVITE")
	{
        invite(fd, parameters, clients, channels);
    }
	else if (command == "MODE")
	{
        mode(parameters, clients, channels, fd);
    }
	else
		{
				ft_response(fd,"Unknown command: "); 
        }
}

command::command()
{

}

// stntax: USER <username> <hostname> <servername> <realname>

//Command: USER  Parameters: <username> 0 * <realname>

void command::ft_user(std::vector<std::string> parametres ,std::map< int ,client> &clients,int fd)
{
	std::map< int ,client>::iterator it;

	for (it = clients.begin(); it != clients.end() ; ++it)
	{
		if(it->first == fd && it->second.is_registered() == "registed")
		{
			ft_response(fd,"you are logged before");
			return;
		}
		else if (it->second.get_username() == parametres[0] && it->first != fd) 
		{
			// deja most3mal => is already used"

			ft_response(fd,"ERR_ALREADYREGISTERED");
			
			return;        	
		}
	}

	it = clients.find(fd);
	if(it != clients.end())
	{
		clients[fd].set_username(parametres[0]);
		clients[fd].set_hostname(parametres[1]);
		clients[fd].set_realname(parametres[2]);
		std::string realname;
		for(size_t i = 3 ; i < parametres.size() ; i++)	
			realname += parametres[i];
	
		clients[fd].set_nickname(parametres[3]);
		clients[fd].set_registered("registed");

		std::cout << "user details : " << std::endl;
		std::cout << "nickname: " << clients[fd].get_nickname() << std::endl;
		std::cout << "hostname: " << clients[fd].get_username() << std::endl;
		std::cout << "realname: " << clients[fd].get_realname() << std::endl;
		std::cout << "hostname: " <<clients[fd].get_hostname() << std::endl;
	}
}


int  isValidNickname(const std::string& nickname) 
{
    // Check if the nickname contains only allowed characters
    for (size_t i = 0; i < nickname.size(); i++) {
        char c = nickname[i];
        // Allowed characters
        if (!(isalnum(c) || c == '[' || c == ']' || c == '{' || c == '}' || c == '|' || c == '\\')) 
		{
            return false;
        }
    }
	return true;
}

// Command: NICK  Parameters: <nickname>
// => nickname

void command::ft_nick(std::vector<std::string> parametres ,std::map< int ,client> &clients ,int fd)
{
	if(parametres.empty())
	{
		//std::cerr << "Error : No nickname provided ." << std::endl;
		ft_response(fd,"ERR_NONICKNAMEGIVEN");
		return;
	}

	std::map< int ,client>::iterator it;
	for(it = clients.begin() ; it != clients.end() ;++it)
	{
		if(it->second.get_nickname() == parametres[0])
		{
			//std::cout << "nickname '" << parametres[0] << "' is already nickname " << std::endl;
			ft_response(fd,"ERR_NICKNAMEINUSE");
            	return; 
		}
	}
	
	//client->set_nickname(parametres[0]);
	if(!isValidNickname(parametres[0]))
	{
			//std::cout << "nickname '" << parametres[0] << "' is invalid " << std::endl;
			ft_response(fd,"ERR_ERRONEUSNICKNAME");
			return;
	}

	it = clients.find(fd);
	if(it!= clients.end())
	{
		it->second.set_nickname(parametres[0]);

			ft_response(fd,"Nickname set successfully for client ");

		//std::cout << "Nickname set successfully for client " << fd <<std::endl;
	}
}

void ft_msg(channel* channelOfUsers, const std::string& msg) 
{
    std::vector<int> users = channelOfUsers->get_Users();
    for (size_t i = 0; i < users.size(); ++i) 
	{
        ft_response(users[i], msg.c_str());
    }

    users = channelOfUsers->getadmin();

    for (size_t i = 0; i < users.size(); ++i) 
	{
        ft_response(users[i], msg.c_str());
    }

    if (channelOfUsers->getOwner() != -1)
	{
        ft_response(channelOfUsers->getOwner(), msg.c_str());
    }
}
// Command: PASS ft_kick
//Parameters: <password>

void command::ft_pass(std::vector<std::string> parametres ,std::map< int ,client> &clients ,int fd ,std::string pass)
{
	if (parametres.empty())
	{
		ft_response(fd,"ERR_NEEDMOREPARAMS");
		return;
	}

	if(clients[fd].is_registered() == "pass")
	{	
		ft_response(fd,"ERR_ALREADYREGISTERED");
        return;
	}

	if (parametres[0] == pass)
	{
		clients[fd].set_registered("pass");
		ft_response(fd,"PASS command successful: Client registered");
    } else
	{
	   ft_response(fd,"ERR_PASSWDMISMATCH ");
    }
}

void command::ft_topic(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd)
{
	if (parametres.empty())
	{
		ft_response(fd,"ERR_NEEDMOREPARAMS"); 
			return;
	}

	std::string channelName;
	std::string newTopic;

	if (parametres.size() >= 1)
	{
		channelName = parametres[0];
	}

	if (parametres.size() >= 2)
	{
		newTopic = parametres[1];
	}

	// Check if the client is joined to the channel
	bool joinedChannel = false;
	std::vector<channel*>::iterator it;
	for (it = clients[fd].channels.begin(); it != clients[fd].channels.end(); ++it)
	{
			//std::cout << "im heeeeeeeeeeereeeeeeeeeee topic 1" << (*it)->get_name() << std::endl;
		if ((*it)->get_name() == parametres[0])
		{
			joinedChannel = true;
			if (parametres.size() == 1) 
			{
				// std::cout << "Topic in this channel: " << (*it)->Topic << std::endl;
				std::string str= "Topic in this channel: " +  (*it)->get_Topic();
				ft_response(fd,str.c_str());
				break;
			//if (std::find((*it)->Admin.begin(), (*it)->Admin.end(), fd) != (*it)->Admin.end() || (*it)->Owner() == fd)

			} else if (std::find((*it)->getadmin().begin(), (*it)->getadmin().end(), fd) != (*it)->getadmin().end() || (*it)->getOwner() == fd) 
			{

				(*it)->set_topic(parametres[1]);
				// std::cout << "Topic of this channel is changed to: " << (*it)->Topic << std::endl;
				std::vector<int> users = (*it)->get_Users();
				std::string names;
				std::string msg = "Topic of channel " + (*it)->get_name() + "is changed to " + parametres[1];
				ft_msg(*it, msg);
				return;
			}
			else if(parametres.size() > 1)
			{

				//std::cout << "You Dont have permission to change the Topic: " << std::endl;
				ft_response(fd,"ERR_CHANOPRIVSNEEDED"); 
				return;
			}
		}
	}
	// is not joined to the channel
	if(!joinedChannel)
	{
		ft_response(fd,"ERR_NOTONCHANNEL"); 
    		return;
	}
}


// // Command: JOIN
// // Parameters: <channel>{,<channel>} [<key>{,<key>}]
// // Alt Params: 0

int searchUserInsideChannel(int fd, channel channelS)
{
	std::vector<int> test = channelS.get_Users();
	for(size_t i = 0; i < test.size() ; i++ )
	{
		std::cout << "users ===> " << test[i] << "====" << std::endl;
	}
	std::cout << "fd ==>"<< fd << channelS.getOwner() << std::endl;
	if (std::find(test.begin(), test.end(), fd) != test.end())
		return 1;

	test = channelS.getadmin();

	if(std::find(test.begin(), test.end(), fd) != test.end())
		return 2;
	if(fd == channelS.getOwner())
		return 3;
	return 0;
}

void command::ft_join(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd ,std::vector<channel *> &channels)
{

	if (parametres.empty())
	{
		ft_response(fd, "ERR_NEEDMOREPARAMS");
		return;
	}
    std::string buffer;
    std::istringstream iss(parametres[0]);
	while (std::getline(iss,buffer,','))
	{	
		std::vector<channel *>::iterator it;
		for (it = channels.begin(); it != channels.end() ;++it)
		{
			if ((*it)->get_name()== parametres[0] && searchUserInsideChannel(fd,**it))
			{
				 std::cout<< "channel to join ==>" << searchUserInsideChannel(fd,**it) << "&& fd ==>" << fd <<std::endl;
				ft_response(fd, "ERR_INVITEONLYCHAN"); 
				return;
			}
			else if((*it)->get_name()== parametres[0])
			{
				buffer = "";
				if(parametres.size() > 1)
				{
   				std::istringstream iss1(parametres[1]);
				getline(iss1,buffer,',');
				}
				if((*it)->get_key().empty() ||(!(*it)->get_key().empty() && (*it)->get_key() == buffer)) // check get_name = channel=> check channel ila maknch 3andha key ou la 3andha key get_key == buffer(,))
				{
				
					(*it)->addUser(fd); // add the user to the channel
					clients[fd].channels.push_back(&(*(*it)));
					ft_response(fd, "You're succesfully joined the channel");
					std::vector<int> users = (*it)->get_Users();
					std::string names;
					for(size_t i = 0; i <  users.size(); i++)
					{
						names = " " + users[i]+clients[fd].get_username();
						std::string msg = clients[fd].get_username()  + " has joined the channel " + (*it)->get_name();
						ft_response(users[i],msg.c_str());
					}
					
					users = (*it)->getadmin();
					for (std::vector<int>::size_type i = 0; i < users.size(); i++)
					{
						names = " " + users[i]+clients[fd].get_username();
						std::string msg = clients[fd].get_username()  + " has joined the channel " + (*it)->get_name();

						ft_response(users[i], msg.c_str());
					}
						std::string msg = clients[fd].get_username()  + " has joined the channel " + (*it)->get_name();
						
						ft_response((*it)->getOwner(),msg.c_str());
							msg = "Welcome! You joined channel "+ (*it)->get_name() +  "w(*it)h topic:" + (*it)->get_Topic();
						ft_response(fd,msg.c_str() );
						msg = "Members of the channel:" + names;
						ft_response(fd, msg.c_str());
				}
				else{
					ft_response(fd, "ERR_BADCHANNELKEY"); 
					return;
				}
				}
			}
			}

			std::string key = "";
			if(parametres.size() > 1)
			{
    		std::istringstream iss2(parametres[1]);
			std::string buffer1;
			getline(iss2,buffer1,',');

			if (!buffer.empty())
				key = buffer1;
			}
			channel* newchannel = new channel(buffer, fd, "", key);
			channels.push_back(newchannel); 
			clients[fd].channels.push_back((newchannel));
			ft_response(fd, "created and joined");

}

int serch_by_name(std::map<int ,client> &clients ,const std::string& username)
{
	std::map< int ,client>::iterator it;

	for (it = clients.begin(); it != clients.end() ; ++it)
	{
		if (it->second.get_username() == username) 
		{
			return it->first;        	
		}
	}
	return -1;
}

//Command: KICK
//Parameters: <channel> <user> *( "," <user> ) [<comment>]

void command::ft_kick(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd ,std::vector<channel *> &channels)
{

	if(parametres.size() < 2)
	{
		ft_response(fd, "ERR_NEEDMOREPARAMS");
		return;
	}

	std::string channel_name = parametres[0];
	channel *channelOfUsers;
	size_t i = 0;
	for(i = 0; i < channels.size(); i++)
	{
		if(channels[i]->get_name() == channel_name)
		{
			channelOfUsers = channels[i];
			break;
		}
	}
	int owner = 0;
	if(i == channels.size())
	{
		ft_response(fd, "ERR_NOSUCHCHANNEL");
		return ;
	}
	std::string user_to_kick = parametres[1];
	std::string comment;
	std::string buffer;
	
	int check = searchUserInsideChannel(fd, *channelOfUsers);
	if(check == 0)
	{
		ft_response(fd, "ERR_NOTONCHANNEL");
		return ;
	}
	else if(check == 1)
	{
		ft_response(fd, "ERR_CHANOPRIVSNEEDED");
		return ;
	}
	else if(check ==3){

		owner = 1;
	}
    std::istringstream iss(parametres[1]);
    while (std::getline(iss, buffer, ','))
    {
		int found = serch_by_name(clients, buffer);
		int searchResult = searchUserInsideChannel(found, *channelOfUsers);
		if(found != -1 && (searchResult == 1 || (searchResult ==2 && owner ==1) ))
		{
			std::vector<int>::iterator it;
			if(searchResult == 1)
			{

			 	it = std::find(channelOfUsers->get_Users().begin(), channelOfUsers->get_Users().end(), found);
				if (it != channelOfUsers->get_Users().end()) {
					channelOfUsers->get_Users().erase(it);
				}
			}
			else
			{
			 	it = std::find(channelOfUsers->getadmin().begin(), channelOfUsers->getadmin().end(), found);
				if (it != channelOfUsers->getadmin().end()) {
					channelOfUsers->getadmin().erase(it);
				}}
				for(size_t i = 0; i < clients[found].channels.size(); i++) {
					if(clients[found].channels[i]->get_name() == channel_name)
					{
						clients[found].channels.erase(clients[found].channels.begin() + i);
						break;
					}}
					std::string buffer1;
					if(parametres.size() > 2)
					{
						std::istringstream iss(parametres[2]);
						std::getline(iss, buffer1, ',');
					}
					
						std::string msg = clients[found].get_username()  + "has been removed from " +channelOfUsers->get_name() + ":" + buffer1;
						ft_msg(channelOfUsers,msg);

					}

		else if(found != -1 && searchResult) {
			ft_response(fd, "ERR_USERNOTINCHANNEL" );
			return;
		}
		else {
			ft_response(fd, "ERR_CHANOPRIVSNEEDED" );
			return;
		}
	}
}

void closeConnection(int fd, std::map<int, client>& clients)
{
    std::map<int, client>::iterator it = clients.find(fd);
    if (it != clients.end()) 
	{
        close(fd);
        clients.erase(it);
    }
}

void notifyClientsOfQuit(int fd, const std::string& quitReason, std::map<int, client>& clients, std::vector<channel *>& channels)
{
  std::vector<int> checkExist;
        for (std::vector<channel *>::iterator chanIt = channels.begin(); chanIt != channels.end(); ++chanIt) 
		{
			int check = searchUserInsideChannel(fd, **chanIt);
            if (check) 
			{
				std::vector<int>::iterator it;

				if(check == 1)
				{
				 	it = std::find((*chanIt)->get_Users().begin(), (*chanIt)->get_Users().end(), fd);
				if (it != (*chanIt)->get_Users().end()) {
					(*chanIt)->get_Users().erase(it);
				}
			}
			else if(check == 2)
			{
			 	it = std::find((*chanIt)->getadmin().begin(), (*chanIt)->getadmin().end(), fd);
				if (it != (*chanIt)->getadmin().end()) {
					(*chanIt)->getadmin().erase(it);
				}}
				else {
					(*chanIt)->set_Owner(-1);
				}
				std::string msg = clients[fd].get_username() + quitReason;
			
                std::vector<int> users = (*chanIt)->get_Users();
					for (size_t i = 0; i < users.size(); ++i) 
					{
						if(std::find(checkExist.begin(), checkExist.end(),users[i]) != checkExist.end())
							continue;
						ft_response(users[i], msg.c_str());
						checkExist.push_back(users[i]);
					}

					users = (*chanIt)->getadmin();

					for (size_t i = 0; i < users.size(); ++i) 
					{
						if(std::find(checkExist.begin(), checkExist.end(),users[i]) != checkExist.end())
							continue;
						ft_response(users[i], msg.c_str());
						checkExist.push_back(users[i]);

					}

					if ((*chanIt)->getOwner() != -1)
					{
						if(std::find(checkExist.begin(), checkExist.end(),(*chanIt)->getOwner()) != checkExist.end())
							continue;
						ft_response((*chanIt)->getOwner(), msg.c_str());
						checkExist.push_back((*chanIt)->getOwner());
					}
				}
    }
}


// // Command: QUIT  
// // Parameters: [<reason>]

void command::ft_Quit(std::vector<std::string> parameters, std::map<int, client>& clients, int fd, std::vector<channel *>& channels)
{
    std::string quitReason;
    if (parameters.empty())
	{
    	quitReason = "Quit.";
    } else 
	{
    	quitReason = "Quit: " + parameters[0];
    }


    notifyClientsOfQuit(fd, quitReason, clients, channels);
    closeConnection(fd, clients);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sendErrorMessage(int fd, const std::string& errorMessage) {
    std::cout << "Sending error message to client with fd " << fd << ": " << errorMessage << std::endl;
}

void command::ft_privmsg(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        sendErrorMessage(fd, ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PRIVMSG"));
        return;
    }

    // Extraire la cible et le message
    std::string target = args.at(0);
    std::string message;

    for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
    {
        message.append(*it + " ");
    }

    if (message.at(0) == ':')
        message = message.substr(1);

    // Si le message est destiné à un canal
    if (target.at(0) == '#')
    {
        channel* chan = nullptr;
        std::vector<channel*> userChannels = clients[fd].get_channel();

        // Recherche du canal par son nom
        for (std::vector<channel*>::iterator it = userChannels.begin(); it != userChannels.end(); ++it)
        {
            channel* ch = *it;
            if (ch->get_name() == target)
            {
                chan = ch;
                break;
            }
        }

        // Canal non trouvé
        if (!chan)
        {
            sendErrorMessage(fd, ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target));
            return;
        }

        // Si le canal n'autorise pas les messages externes
        if (!chan->isExternalMessage())
        {
            // Vérifier si le client est dans le canal
            if (!chan->is_member(&clients[fd]))
            {
                sendErrorMessage(fd, ERR_CANNOTSENDTOCHAN(clients[fd].get_nickname(), target));
                return;
            }
        }

        // Diffuser le message au canal
        chan->broadcast(RPL_PRIVMSG(clients[fd].get_prefix(), target, message), &clients[fd]);
        return;
    }

    // Si le message est destiné à un autre client
    client* destClient = nullptr;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.get_nickname() == target)
        {
            destClient = &(it->second);
            break;
        }
    }

    if (destClient == nullptr)
    {
        sendErrorMessage(fd, ERR_NOSUCHNICK(clients[fd].get_nickname(), target));
        return;
    }

    // Envoyer le message au client destinataire
    destClient->write(RPL_PRIVMSG(clients[fd].get_prefix(), target, message));
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void command::ft_notice(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        sendErrorMessage(fd, ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PRIVMSG"));
        return;
    }

    // Extraire la cible et le message
    std::string target = args.at(0);
    std::string message;

    for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
    {
        message.append(*it + " ");
    }

    if (message.at(0) == ':')
        message = message.substr(1);

    // Si le message est destiné à un canal
    if (target.at(0) == '#')
    {
        channel* chan = nullptr;
        std::vector<channel*> userChannels = clients[fd].get_channel();

        // Recherche du canal par son nom
        for (std::vector<channel*>::iterator it = userChannels.begin(); it != userChannels.end(); ++it)
        {
            channel* ch = *it;
            if (ch->get_name() == target)
            {
                chan = ch;
                break;
            }
        }

        // Canal non trouvé
        if (!chan)
        {
            sendErrorMessage(fd, ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target));
            return;
        }

        // Si le canal n'autorise pas les messages externes
        if (!chan->isExternalMessage())
        {
            // Vérifier si le client est dans le canal
            if (!chan->is_member(&clients[fd]))
            {
                sendErrorMessage(fd, ERR_CANNOTSENDTOCHAN(clients[fd].get_nickname(), target));
                return;
            }
        }

        // Diffuser le message au canal
        chan->broadcast(RPL_NOTICE(clients[fd].get_prefix(), target, message), &clients[fd]);
        return;
    }

    // Si le message est destiné à un autre client
    client* destClient = nullptr;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.get_nickname() == target)
        {
            destClient = &(it->second);
            break;
        }
    }

    if (destClient == nullptr)
    {
        sendErrorMessage(fd, ERR_NOSUCHNICK(clients[fd].get_nickname(), target));
        return;
    }

    // Envoyer le message au client destinataire
    destClient->write(RPL_NOTICE(clients[fd].get_prefix(), target, message));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void command::ft_ping(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.empty())
    {
        sendErrorMessage(fd, ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PING"));
        return;
    }

    clients[fd].write(RPL_PING(clients[fd].get_prefix(), args.at(0)));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void command::ft_part(std::vector<std::string> args, std::map<int, client>& clients, int fd)
// {
//     if (args.empty()) 
//     {
//         sendErrorMessage(fd, ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PART"));
//         return;
//     }

//     std::string name = args[0];
//     channel* chan = nullptr;
//     std::vector<channel*> userChannels = clients[fd].get_channel();

//     // Recherche du canal par son nom
//     for (channel* ch : userChannels)
//     {
//         if (ch->get_name() == name)
//         {
//             chan = ch;
//             break;
//         }
//     }

//     if (!chan)
//     {
//         sendErrorMessage(fd, ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), name));
//         return;
//     }

//     clients[fd].quiter();
// }

void command::ft_part(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.empty()) 
    {
        sendErrorMessage(fd, ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PART"));
        return;
    }

    const std::vector<channel*>& userChannels = clients[fd].get_channel();

    for (size_t i = 0; i < args.size(); ++i) 
    {
        const std::string& channelName = args[i];
        bool foundChannel = false;

        // Recherche du canal dans les canaux du client
        for (size_t j = 0; j < userChannels.size(); ++j)
        {
            channel* chan = userChannels[j];
            if (chan->get_name() == channelName)
            {
                // Supprimer le client du canal
                chan->remove_client(&clients[fd]);
                // Marquer le canal comme trouvé
                foundChannel = true;
                break;
            }
        }

        // Si le canal n'est pas trouvé, envoyer un message d'erreur
        if (!foundChannel)
        {
            sendErrorMessage(fd, ERR_NOTONCHANNEL(clients[fd].get_nickname(), channelName));
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void command::ft_kill(client* operatorClient, std::map<int, client>& clients, int fd, const std::string& reason) {
    // Recherche du client cible
    std::map<int, client>::iterator it = clients.find(fd);
    client* targetClient = nullptr;
    if (it != clients.end()) {
        targetClient = &(it->second);
    }

    // Vérification de l'existence du client cible
    if (!targetClient) {
        operatorClient->write("ERR_NOSUCHSERVER " + operatorClient->get_nickname());
        return;
    }

    // Obtention du surnom de l'opérateur
    std::string killer = operatorClient->get_nickname();

    // Message de kill
    std::string killMessage = "Killed by operator (" + killer + "): " + reason;

    // Quitter le réseau pour le client cible
    targetClient->quit_network(clients, fd, reason);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_message_to_server(const std::string& message, int fd) {
    // Convertir la chaîne de caractères en un pointeur de caractères C pour l'appel système write
    const char* buffer = message.c_str();
    
    // Obtenir la longueur du message à envoyer
    size_t length = std::strlen(buffer);
    
    // Utiliser l'appel système write pour envoyer le message
    ssize_t bytes_written = write(fd, buffer, length);
    
    // Vérifier si l'écriture a réussi
    if (bytes_written == -1) {
        // Gérer l'erreur d'écriture
        std::cerr << "Erreur lors de l'envoi du message au serveur" << std::endl;
    } else {
        std::cout << "Message envoyé au serveur avec succès" << std::endl;
    }
}

void command::cap(const std::string& subcommand, const std::string& capabilities, int fd) {
    std::string message = "CAP " + subcommand;

    if (subcommand == "REQ" || subcommand == "ACK" || subcommand == "NAK") {
        if (!capabilities.empty()) {
            message += " :" + capabilities;
        }
    }
    else if (subcommand != "LS") {
        std::cerr << "Sous-commande inconnue : " << subcommand << std::endl;
        return;
    }

    send_message_to_server(message, fd);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void command::invite(int fd, const std::vector<std::string>& args, std::map<int, client>& clients, std::vector<channel*>& channels) {
    client& sender = clients[fd];

    if (args.size() < 2) {
        sender.write(ERR_NEEDMOREPARAMS(sender.get_nickname(), "INVITE"));
        return;
    }

    std::string invitedNickname = args[0];
    std::string channelName = args[1];

    // Trouver le client invité par son pseudo
    client* invitedClient = nullptr;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->second.get_nickname() == invitedNickname) {
            invitedClient = &(it->second);
            break;
        }
    }

    if (!invitedClient) {
        sender.write(ERR_NOSUCHNICK(sender.get_nickname(), invitedNickname));
        return;
    }

    // Trouver le canal par son nom
    channel* chan = nullptr;
    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        channel* ch = *it;
        if (ch->get_name() == channelName) {
            chan = ch;
            break;
        }
    }

    if (!chan) {
        sender.write(ERR_NOSUCHCHANNEL(sender.get_nickname(), channelName));
        return;
    }

    // Inviter le client au canal
    sender.invite_to_channel(invitedClient, chan);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void command::mode(std::vector<std::string> args, std::map<int, client>& clients, std::vector<channel*>& channels, int fd)
{
    // Handling errors
    if (args.size() < 2)
    {
        clients[fd].sendMessage(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "MODE"));
        return;
    }
    
    std::string target = args.at(0);
    channel* chan = nullptr;

    // Recherche du canal par nom
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->get_name() == target) {
            chan = channels[i];
            break;
        }
    }

    if (!chan)
    {
        clients[fd].sendMessage(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target));
        return;
    }

    if (std::find(chan->getadmin().begin(), chan->getadmin().end(), fd) == chan->getadmin().end())
    {
        clients[fd].sendMessage(ERR_CHANOPRIVSNEEDED(clients[fd].get_nickname(), target));
        return;
    }

    // Changing the mode
    int i = 0, p = 2;
    char c;
    
    while ((c = args[1][i]))
    {
        char prev_c = i > 0 ? args[1][i - 1] : '\0';
        bool active = prev_c == '+';

        switch (c) 
        {
            case 'n':
                chan->setExternalMessage(active);
                chan->broadcast(RPL_MODE(clients[fd].get_prefix(), chan->get_name(), (active ? "+n" : "-n"), ""), nullptr);
                break;
            case 'l':
                chan->set_limit(active ? std::stoi(args[p]) : 0);
                chan->broadcast(RPL_MODE(clients[fd].get_prefix(), chan->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")), nullptr);
                if (active) ++p;
                break;
            case 'k':
                chan->set_key(active ? args[p] : "");
                chan->broadcast(RPL_MODE(clients[fd].get_prefix(), chan->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")), nullptr);
                if (active) ++p;
                break;
            default:
                break;
        }
        ++i;
    }
}

command::~command()
{

}