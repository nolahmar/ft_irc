#include "command.hpp"
#include "client.hpp"
#include "server.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>



//Sure, let's break down the ft_response function in detail, explaining each part of the code. 
//This function is used to send a formatted response message to a client over a network socket,
//typically in an IRC (Internet Relay Chat) context

void ft_response(int fd, const char* message)
{   
	std::cout << "message: " << message;
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
//std::vector<channel *> &channels  std::map< int ,client> &clients ==> * baash tbe9aa by refrence ila tbedelaat chnnel katbedel ta end client hiit inside client kin channels

void command::excute(const std::string& command,const std::vector<std::string>& parameters,std::map< int ,client> &clients, int fd, std::string password,std::vector<channel *> &channels)
{

		if (clients[fd].is_registered() == "none" && command != "/pass")
		{
			ft_response(fd, "You should enter the passwotrd");
				return ;
		}

		if(clients[fd].is_registered() != "registed"  && command != "/user" && command != "/pass")
		{	
			ft_response(fd, "YOu are not registred yet");
			return ;
		}

        if (command == "/join") 
		{
            // JOIN command: Join a channel
            if (parameters.size() >= 1) 
			{
                ft_join(parameters,clients,fd,channels);
            } else 
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "JOIN")).c_str());
            }
        } 
		else if (command == "/KICK")
		 {
            // KICK command: Kick a user from a channel
            if (parameters.size() >= 2) 
			{
               //PASS command successful: Client registered/ 
				ft_kick(parameters, clients,fd,channels);
            } else 
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "KICK")).c_str());
            }
        } else if (command == "/Quite")
		 {
            // Quite command: Quite a user to a channel
            
               ft_Quit(parameters,clients,fd, channels);
           
        } else if (command == "/user")
		 {
            // MODE command: Change the mode of a channel
            if (parameters.size() >= 4) 
			{
                ft_user(parameters,clients,fd);

            } else {

				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "USER")).c_str());      
		 }
        }else if(command == "/pass")
		{
			if(parameters.size() >=1)
			{
				// std::cout << "and dkhelt l execute and i choose pass" << std::endl;
				ft_pass(parameters,clients,fd,password);

			}else
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PASS")).c_str());
			}
		}else if(command == "/Nick")
		{
			if(parameters.size() >= 1)
			{
				ft_nick(parameters,clients,fd);
			}else
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "NICK")).c_str());
			}
		}else if(command == "/Topic")
		{
			
			ft_topic(parameters,clients,fd);

		}
		else if (command == "/PRIVMSG")
	{
        ft_privmsg(parameters, clients, fd);
    }
	else if (command == "/NOTICE")
	{
        ft_notice(parameters, clients, fd);
    }
	else if (command == "/PART")
	{
        ft_part(parameters, clients, fd);
    }
	else if (command == "/INVITE")
	{
        invite(fd, parameters, clients, channels);
    }
	else if (command == "/MODE")
	{
        mode(clients, parameters, channels, fd);
    }
	else if (command == "/PING")
	{
		ping(parameters, clients, fd);
	}
	else if (command == "/PONG")
	{
		pong(clients, fd);
	}
	//else if (commans)
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
			ft_response(fd, std::string(ERR_ALREADYREGISTERED(clients[fd].get_nickname())).c_str());
			return;
		}
		else if (it->second.get_username() == parametres[0] && it->first != fd) 
		{ 
			// deja most3mal => is already used"
			ft_response(fd, std::string(ERR_ALREADYREGISTERED(clients[fd].get_nickname())).c_str());
			
			return;        	
		}
	}


	it = clients.find(fd);
	
	if(it != clients.end())
	{
		clients[fd].set_username(parametres[0]);
		clients[fd].set_hostname(parametres[1]);
		;
		clients[fd].set_servername(parametres[2]);
		std::string realname;
		for(size_t i = 3 ; i < parametres.size() ; i++)	
			realname += parametres[i];
	
		clients[fd].set_realname(parametres[3]);
		clients[fd].set_registered("registed");
		ft_response(fd, "You are succesdful registred.");
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
	client& sender = clients[fd];

	if (parametres.empty())  
	{
		//std::cerr << "Error : No nickname provided ." << std::endl;
		ft_response(fd, std::string(ERR_NONICKNAMEGIVEN(sender.get_nickname())).c_str());
		return;
	}

	std::map< int ,client>::iterator it;
	for(it = clients.begin() ; it != clients.end() ;++it)
	{
		if(it->second.get_nickname() == parametres[0] && it->first != fd)
		{
			//std::cout << "nickname '" << parametres[0] << "' is already nickname " << std::endl;
			 ft_response(fd, std::string(ERR_NICKNAMEINUSE(sender.get_nickname())).c_str());   //this nickname deja use (mestkhdm)
            	return; 
		}
	}
	
	//client->set_nickname(parametres[0]);
	if(!isValidNickname(parametres[0]))
	{
			//std::cout << "nickname '" << parametres[0] << "' is invalid " << std::endl;
			ft_response(fd, std::string(ERR_ERRONEUSNICKNAME(sender.get_nickname(), parametres[0])).c_str());
			return;
	}

	it = clients.find(fd);  // find retourn an iterator to the first occurrence  of the value in the range if is found
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
	 client& sender = clients[fd];
	if (parametres.empty()) // dakhl pass mais medkhl hta parameter werha 
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "PASS")).c_str());
		return;
	}

	if(clients[fd].is_registered() == "/pass") // register ou 3awd dar cmd pass
	{	
		ft_response(fd, std::string(ERR_ALREADYREGISTERED(sender.get_nickname())).c_str());
        return;
	}

	if (parametres[0] == pass) // 
	{
		clients[fd].set_registered("pass");
		ft_response(fd,"PASS command successful: Client registered");
    } else
	{
	   ft_response(fd,"ERR_PASSWDMISMATCH "); // dakhl cmd pass mais pass ghlat mechi nafs kalma li fi server  non moutchd
    }
}

void command::ft_topic(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd)
{
	client& sender = clients[fd];
	if (parametres.empty())
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "TOPIC")).c_str()); 
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

			} else if (std::find((*it)->getadmin().begin(), (*it)->getadmin().end(), fd) != (*it)->getadmin().end() || (*it)->getOwner() == fd) // membre and admin change sjt
			{
				(*it)->set_topic(parametres[1]);
				// std::cout << "Topic of this channel is changed to: " << (*it)->Topic << std::endl;
				std::string msg = "Topic of channel " + (*it)->get_name() + "is changed to " + parametres[1]; // send msg ga3 membres  tabdl
				ft_msg(*it, msg); // send msg gam membr li fdk channel
				return;
			}
			else if(parametres.size() > 1)  // member fiha but its not admins
			{

				//std::cout << "You Dont have permission to change the Topic: " << std::endl; 
				ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(sender.get_nickname(), channelName)).c_str());
				return;
			}
		}
	}
	
	// is not joined to the channel
	if(!joinedChannel)
	{
		ft_response(fd, std::string(ERR_NOTONCHANNEL(sender.get_nickname(), channelName)).c_str());
    		return;
	}
}


// // Command: JOIN
// // Parameters: <channel>{,<channel>} [<key>{,<key>}]
// // Alt Params: 0

int searchUserInsideChannel(int fd, channel channelS)
{
	std::vector<int> test = channelS.get_Users();
	// for(size_t i = 0; i < test.size() ; i++ )
	// {
	// 	std::cout << "users ===> " << test[i] << "====" << std::endl;
	// }

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
	client& sender = clients[fd];

	if (parametres.empty()) // join apres medkhl walo
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "JOIN")).c_str());
		return;
	}
		std::istringstream iss2;

    if (parametres.size() > 1)  // splite lkey
	{
        iss2.str(parametres[1]);
	}

    std::string buffer;
    std::istringstream iss(parametres[0]); // istringstream  red in string  input 
	while (std::getline(iss,buffer,','))
	{	
		std::vector<channel *>::iterator it;
		std::cout <<"buffer ==>" << buffer << std::endl;
		for (it = channels.begin(); it != channels.end() ;++it)
		{
			std::cout << "channels name ==>" << (*it)->get_name()<< std::endl;
			if ((*it)->get_name()== buffer && searchUserInsideChannel(fd,**it))
			{
				 //std::cout<< "channel  ==>" << searchUserInsideChannel(fd,**it) << "&& fd ==>" << fd <<std::endl;
				// ft_response(fd, "ERR_INVITEONLYCHAN"); // 1 2 3 user  deja kan !!!!!
				ft_response(fd, std::string(ERR_INVITEONLYCHAN(clients[fd].get_nickname(), buffer)).c_str());
				break;
			}
			else if((*it)->get_name()== buffer) 
			{
				buffer = "";
				if(parametres.size() > 1)  // check key dakh key
				{
					std::istringstream iss1(parametres[1]); // key 
					getline(iss1,buffer,',');
				}
				if((*it)->get_key().empty() ||(!(*it)->get_key().empty() && (*it)->get_key() == buffer)) // check get_name = channel=> check channel ila maknch 3andha key ou la 3andha key get_key == buffer(,))
				{
					(*it)->addUser(fd); // add the user to the channel
					clients[fd].channels.push_back(&(*(*it))); // chanl dil client
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

					ft_response(fd, std::string(ERR_BADCHANNELKEY(clients[fd].get_nickname(), (*it)->get_name())).c_str()); // key ghlat
					break;
				}
				}
			}
			if(it == channels.end())  // ila wslt end makntch channel create
			{
				std::string key = ""; // 
				if(parametres.size() > 1)
				{
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
	}
			// create channel that not exist 
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
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "KICK")).c_str());
		return;
	}
	std::istringstream iss1;

    if (parametres.size() > 2) // commet
	{
        iss1.str(parametres[2]);
	}
	std::string channel_name = parametres[0];
	channel *channelOfUsers; //poiner 3la dik channel
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
	if(i == channels.size()) // i wslt end makch channel
	{
		ft_response(fd, std::string(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), channel_name)).c_str()); // channls not found
		return ;
	}

	std::string user_to_kick = parametres[1];
	std::string comment;
	std::string buffer;
	
	int check = searchUserInsideChannel(fd, *channelOfUsers);
	if(check == 0)
	{
		ft_response(fd, std::string(ERR_NOTONCHANNEL(clients[fd].get_nickname(), channel_name)).c_str()); // mejon channll
		return ;
	}
	else if(check == 1)
	{
		ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(clients[fd].get_nickname(), channel_name)).c_str()); // user fik channle membre
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
					channelOfUsers->get_Users().erase(it); // supprime file descrptor dilow (client)
				}
			}
			else
			{
			 	it = std::find(channelOfUsers->getadmin().begin(), channelOfUsers->getadmin().end(), found);
				if (it != channelOfUsers->getadmin().end()) {
					channelOfUsers->getadmin().erase(it); // supprim file descptor 
				}}
				for(size_t i = 0; i < clients[found].channels.size(); i++) {
					if(clients[found].channels[i]->get_name() == channel_name)
					{
						clients[found].channels.erase(clients[found].channels.begin() + i); // suppprim channel li 3and client
						break;
					}}
					std::string buffer1; // commnt
					if(parametres.size() > 2)
					{
						std::getline(iss1, buffer1, ',');
					}
					
						std::string msg = clients[found].get_username()  + "has been removed from " +channelOfUsers->get_name() + ":" + buffer1;
						ft_msg(channelOfUsers,msg);

					}

		else if(found != -1 && searchResult) { 
			ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(clients[fd].get_nickname(), channel_name)).c_str()); // admin bagha ikhrji owner
			return;
		}
		else {
			ft_response(fd, std::string(ERR_USERNOTINCHANNEL(clients[fd].get_nickname(), buffer, channel_name)).c_str()); // user maknch fi channel
				return;
		}
	}
}

// delete men map dil client 
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
						(*chanIt)->set_Owner(-1); // -1 channel not owner
					}

				//checkExist => 1 vector kanheet fiih koula fd dial chi user deje seft lih msg bli khouna khrej
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


// kankhrjow men server  (irc) quit men challel kaml ya3n dik channel
// supprim men ga3 li channel li kantmow dak server

void command::ft_Quit(std::vector<std::string> parameters, std::map<int, client>& clients, int fd, std::vector<channel *>& channels)
{
    std::string quitReason;
    if (parameters.empty())
	{
    	quitReason = "Quit.";
    } else 
	{
    	quitReason = "Quit: " + parameters[0];
		for(size_t i = 1 ; i < parameters.size() ; i++)	
			quitReason += parameters[i];
	
    }
    notifyClientsOfQuit(fd, quitReason, clients, channels);
    closeConnection(fd, clients);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_ckeak(std::string &nick, std::map<int, client>& clients)
{
	for(std::map<int, client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		//std::cout << it->second << std::endl;
		if (it->second.get_nickname() == nick)
		{
             return it->first;
		}
	}
	return 0;
}

//santaxe ---> PRIVMSG noni :hello
void command::ft_privmsg(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty() || args[1].at(0) != ':')
    {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PRIVMSG")).c_str());
        return;
    }

	args[1].erase(args[1].begin());
    // Extraire la cible et le message
    std::string target = args.at(0);
    std::string message;

    for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
		(it != (args.end() - 1)) ? message.append(*it + " ") : message.append(*it);
    // Si le message est destiné à un canal
    if (target.at(0) == '#')
    {
        channel* chan = NULL;

		target.erase(target.begin());
        // Recherche du canal par son nom
        for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
			chan = it->second.get_channel_by_name(target);
			if (chan)
				break;
        }

        // Canal non trouvé
        if (!chan)
        {
             ft_response(fd, std::string(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target)).c_str());
            return;
        }
		// std::cout << "\nClient ID: " << clients[fd].get_id() << std::endl;
		// Vérifier si le client est dans le canal
		if (!chan->is_member(fd))
		{
			ft_response(fd, std::string(ERR_CANNOTSENDTOCHAN(clients[fd].get_nickname(), target)).c_str());
			return;
		}

        // Diffuser le message au canal
        chan->broadcast(RPL_PRIVMSG(clients[fd].get_prefix(), target, message), clients, fd);
        return;
    }

    // Si le message est destiné à un autre client
    client* destClient = NULL;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.get_nickname() == target)
        {
            destClient = &(it->second);
            break;
        }
    }

    if (destClient == NULL)
    {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), target)).c_str());
        return;
    }

    // Envoyer le message au client destinataire
    destClient->write(ft_ckeak(args[0], clients), RPL_PRIVMSG(clients[fd].get_prefix(), target, message));
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void command::ft_notice(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
   if (args.size() < 2 || args[0].empty() || args[1].empty() || args[1].at(0) != ':')
    {
      ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PRIVMSG")).c_str());
        return;
    }

	args[1].erase(args[1].begin());
    // Extraire la cible et le message
    std::string target = args.at(0);
    std::string message;

    for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
		(it != (args.end() - 1)) ? message.append(*it + " ") : message.append(*it);
    // Si le message est destiné à un canal
    if (target.at(0) == '#')
    {
        channel* chan = NULL;

		target.erase(target.begin());
        // Recherche du canal par son nom
        for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
			chan = it->second.get_channel_by_name(target);
			if (chan)
				break;
        }

        // Canal non trouvé
        if (!chan)
        {
            ft_response(fd, std::string(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target)).c_str());
            return;
        }

		// Vérifier si le client est dans le canal
		if (!chan->is_member(fd))
		{
			ft_response(fd, std::string(ERR_CANNOTSENDTOCHAN(clients[fd].get_nickname(), target)).c_str());
			return;
		}

        // Diffuser le message au canal
        chan->broadcast(RPL_NOTICE(clients[fd].get_prefix(), target, message), clients, fd);
        return;
    }

    // Si le message est destiné à un autre client
    client* destClient = NULL;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.get_nickname() == target)
        {
            destClient = &(it->second);
            break;
        }
    }

    if (destClient == NULL)
    {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), target)).c_str());
        return;
    }

    // Envoyer le message au client destinataire
    destClient->write(ft_ckeak(args[0], clients), RPL_NOTICE(clients[fd].get_prefix(), target, message));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> split(std::string s)
{
	std::stringstream ss(s);
	std::vector<std::string> res;
	std::string tmp;
	
	while (std::getline(ss, tmp, ','))
		res.push_back(tmp);
	return res;
}

void remove_client_from_channel(client& target, channel *ch, int fd)
{
	ch->remove_user(fd);	
	target.remove_channel(ch);
}

void command::ft_part(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.empty()) 
    {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PART")).c_str());
        return;
    }
	std::vector<std::string> targetChannels = split(args[0]);
	// TODO: jion all messages
	std::string reason = args.size() > 1 ? args[1] : "";

	for (std::vector<std::string>::iterator ch_it = targetChannels.begin(); ch_it != targetChannels.end(); ++ch_it)
	{
		channel *ch = NULL;
		std::string nickname = clients[fd].get_nickname();

		// Check if channel exists and get its object
		for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
			ch = it->second.get_channel_by_name(*ch_it);
			if (ch)
				break;
        }

		if (!ch)
		{
			ft_response(fd, std::string(ERR_NOSUCHCHANNEL(nickname, *ch_it)).c_str());
			continue;
		}
		if (!ch->is_member(fd))
		{
			ft_response(fd, std::string(ERR_NOTONCHANNEL(nickname, *ch_it)).c_str());
			continue;
		}
		remove_client_from_channel(clients[fd], ch, fd);
		clients[fd].write(fd, RPL_PART(clients[fd].get_nickname(), *ch_it, reason));
		ch->broadcast(RPL_PART(clients[fd].get_nickname(), *ch_it, reason), clients, fd);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// NICK CHA
void command::invite(int fd, const std::vector<std::string>& args, std::map<int, client>& clients, std::vector<channel*>& channels) {
    client& sender = clients[fd];

    if (args.size() < 2) {
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "INVITE")).c_str());
        return;
    }

    std::string invitedNickname = args[0];
    std::string channelName = args[1];

    // Trouver le client invité par son pseudo !!! Merciiii
    std::map<int, client>::iterator invitedClientIt = clients.end();

    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->second.get_nickname() == invitedNickname) {
            invitedClientIt = it;
            break;
        }
    }

	// Check if no target user
    if (invitedClientIt == clients.end()) {
        ft_response(fd, std::string(ERR_NOSUCHNICK(sender.get_nickname(), invitedNickname)).c_str());
        return;
    }

    // Trouver le canal par son nom !!! Merciiiii
    std::vector<channel*>::iterator chanIt = channels.end();

    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->get_name() == channelName) {
            chanIt = it;
            break;
        }
    }

	// Check if no target channel
    if (chanIt == channels.end()) {
        ft_response(fd, std::string(ERR_NOSUCHCHANNEL(sender.get_nickname(), channelName)).c_str());
        return;
    }

	// Check if the sender is a member of the target channel
	if (!(*chanIt)->is_member(fd)) {
		ft_response(fd, std::string(ERR_NOTONCHANNEL(sender.get_nickname(), channelName)).c_str());
		return;
	}

	// Check if the target user is not already a member of the target channel
	if ((*chanIt)->is_member(invitedClientIt->first)) {
		ft_response(fd, std::string(ERR_USERONCHANNEL(sender.get_nickname(), channelName)).c_str());
		return;
	}
	 if ((*chanIt)->get_mode().count('i') != 0 && !(*chanIt)->is_operator(fd)) {
        ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(sender.get_nickname(), channelName)).c_str());
        return;
    }
    // Inviter le client au canal
    sender.invite_to_channel(fd, invitedClientIt, *chanIt);
}

void command::ping(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.empty())
    {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PING")).c_str());
        return;
    }

    std::string target = args[0];

    // Verify the client exists in the clients map
    if (clients.find(fd) == clients.end())
    {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), target)).c_str());
        return;
    }

    // Respond to the PING command
    clients[fd].write(fd, RPL_PING(clients[fd].get_prefix(), target));
}

void command::pong(std::map<int, client>& clients, int fd)
{

    // Vérifier que le client existe dans la map des clients
    if (clients.find(fd) == clients.end())
        return;

    // Répondre à la commande PONG
    clients[fd].write(fd, "PONG received");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void command::mode(std::map<int, client>& clients, std::vector<std::string> args, std::vector<channel*>& channels, int fd) {
    // Handling errors
	client& sender = clients[fd];
    if (args.size() < 2) {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str());
        return;
    }

    std::string target = args[0];
    channel* chan = NULL;

    // Recherche du canal par nom
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->get_name() == target) {
            chan = channels[i];
            break;
        }
    }

    if (!chan) {
        ft_response(fd, std::string(ERR_NOSUCHCHANNEL(sender.get_nickname(), target)).c_str());
        return;
    }

    // user is not an operator
    if (!chan->is_operator(fd) && !chan->is_admin(fd)) {
        ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(sender.get_nickname(), target)).c_str());
        return;
    }

    // Changing the mode
    std::string modeStr = args[1];

    if (modeStr == "+i" || modeStr == "-i") {
        chan->change_invite_only_mode(modeStr);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+t" || modeStr == "-t") {
        chan->change_topic_mode(modeStr);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+k" || modeStr == "-k") {
        if (args.size() < 3 && modeStr == "+k") {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str());
            return;
        }
        chan->change_key_mode(args, modeStr, fd);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+o" || modeStr == "-o") {
        if (args.size() < 3) {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str());
            return;
        }
        chan->change_operator_mode(clients, args, modeStr, fd);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+l" || modeStr == "-l") {
        if (args.size() < 3 && modeStr == "+l") {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str());
            return;
        }
        chan->change_limit_mode(args, modeStr, fd);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else 
        ft_response(fd, std::string(ERR_UNKNOWNMODE(sender.get_nickname(), modeStr)).c_str());
}

command::~command()
{

}
