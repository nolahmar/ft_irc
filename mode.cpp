#include "client.hpp"
#include "channel.hpp"

//santaxe: MODE <target> <mode>

std::vector<client*>& channel::getUsers() {
        return Users;
}


void channel::add_mode(char mode) {
    if (Modes.find(mode) == std::string::npos) {
        Modes += mode;
    }
}

void channel::remove_mode(char mode) {
        Modes.erase(std::remove(Modes.begin(), Modes.end(), mode), Modes.end());
}

const std::string& channel::getModes() const {
        return Modes;
}

void channel::remove_user(client* client) {
        Users.erase(std::remove(Users.begin(), Users.end(), client), Users.end());
}

void mode(client* client, channel* chan, const std::string& target, const std::string& modestring) {
    if (chan->getName() != target) {
        client->write("ERR_NOTONCHANNEL " + client->getNickname() + " " + target);
        return;
    }

    if (modestring.empty()) {
        client->write("RPL_CHANNELMODEIS " + chan->getName() + " " + chan->getModes());
        return;
    }

    bool add = false;
    for (size_t i = 0; i < modestring.size(); ++i) {
        char mode = modestring[i];
        if (mode == '+') {
            add = true;
        } else if (mode == '-') {
            add = false;
        } else {
            if (add) {
                chan->add_mode(mode);
            } else {
                chan->remove_mode(mode);
            }
        }
    }

    std::vector<client*>& users = chan->getUsers();
    for (size_t i = 0; i < users.size(); ++i) {
        client* user = users[i];
        user->write("MODE " + chan->getName() + " " + chan->getModes());
    }
}