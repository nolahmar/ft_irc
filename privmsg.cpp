#include "channel.hpp"
#include "client.hpp"

//santax: PRIVMSG <target> <message>

void client::write(const std::string& message) const {
    std::cout << "Message envoyé à " << nickname << " : " << message << std::endl;
}

void channel::send_msg(const std::string& sender, const std::string& message, client* senderClient) const {
    std::cout << "Message envoyé au canal " << Name << " par " << sender << " : " << message << std::endl;
    for (size_t i = 0; i < Users.size(); ++i) {
        if (Users[i] != nullptr && Users[i] != senderClient) {
            Users[i]->write(sender + " : " + message);
        }
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

void privmsg(client* sender, const std::vector<std::string>& args){
    if (args.size() < 2 || args[0].empty() || args[1].empty()) {
        sender->write("ERR_NEEDMOREPARAMS " + sender->getNickname() + " PRIVMSG");
        return;
    }

    std::string target = args[0];
    std::string message = args[1];

    if (target[0] == '#') {
        channel currentChannel;
        channel* chan = currentChannel.getChannel();
        if (!chan) {
            sender->write("ERR_NOSUCHCHANNEL " + sender->getNickname() + " " + target);
            return;
        }

        if (!chan->is_member(sender)) {
            sender->write("ERR_CANNOTSENDTOCHAN " + sender->getNickname() + " " + target);
            return;
        }

        chan->send_msg(sender->getNickname(), message, sender);
        return;
    }

    client* dest = sender->getClient(target);
    if (!dest) {
        sender->write("ERR_NOSUCHNICK " + sender->getNickname() + " " + target);
        return;
    }

    dest->write(sender->getNickname() + " : " + message);
}
