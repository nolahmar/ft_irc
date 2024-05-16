#include "client.hpp"
#include "channel.hpp"

//santax: PART <channel> <reason>

void channel::remove_user(client* client) {
    for (size_t i = 0; i < Users.size(); ++i) {
        if (Users[i] == client) {
            Users.erase(Users.begin() + i);
            break;
        }
    }
}

void part(client* client, std::vector<channel*>& allChannels, const std::vector<std::string>& args) {
    if (args.empty()) {
        client->write("ERR_NEEDMOREPARAMS " + client->getNickname() + " PART");
        return;
    }

    for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
        const std::string& channelName = *it;
        bool foundChannel = false;
        for (std::vector<channel*>::iterator chan_it = allChannels.begin(); chan_it != allChannels.end(); ++chan_it) {
            channel* chan = *chan_it;
            if (chan->getName() == channelName) {
                foundChannel = true;
                if (!chan->is_member(client)) {
                    client->write("ERR_NOTONCHANNEL " + client->getNickname() + " " + channelName);
                } else {
                    chan->remove_user(client);
                    client->write("Vous avez quitté le canal " + channelName);
                }
                break;
            }
        }
        if (!foundChannel) {
            client->write("ERR_NOSUCHCHANNEL " + client->getNickname() + " " + channelName);
        }
    }
}
