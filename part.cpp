#include "client.hpp"
#include "channel.hpp"

//santax: PART <channel> <reason>
void channel::remove_user(client* client) {
    std::vector<client *>::iterator it = std::find(Users.begin(), Users.end(), client);
    if (it != Users.end()) {
        Users.erase(it);
    }
}

void part(client* client, const std::vector<std::string>& args) {
        if (args.empty()) {
            client->write("ERR_NEEDMOREPARAMS " + client->getNickname() + " PART");
            return;
        }

        for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)  {
            const std::string& channelName = *it;
            channel* chan = chan->getChannel();
            if (!chan) {
                client->write("ERR_NOSUCHCHANNEL " + client->getNickname() + " " + channelName);
                continue;
            }

            if (!chan->is_member(client)) {
                client->write("ERR_NOTONCHANNEL " + client->getNickname() + " " + channelName);
                continue;
            }

            chan->remove_user(client);
            client->write("Vous avez quitté le canal " + channelName);
        }
    }