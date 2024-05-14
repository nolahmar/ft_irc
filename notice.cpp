#include "client.hpp"
#include "channel.hpp"

//santax: NOTIC <target> <msg>

void channel::send_notice(const std::string& sender, const std::string& notice) const {
    std::cout << "Notice envoyé au canal " << Name << " par " << sender << " : " << notice << std::endl;
    for (std::vector<client*>::const_iterator it = Users.begin(); it != Users.end(); ++it) {
        (*it)->write(sender + " (notice) : " + notice);
    }
}

void notice(client* sender, const std::vector<std::string>& args) {
    if (args.size() < 2 || args[0].empty() || args[1].empty()) {
        sender->write("ERR_NEEDMOREPARAMS " + sender->getNickname() + " NOTICE");
        return;
    }

    std::string target = args[0];
    std::string notice = args[1];

    if (target[0] == '#') {
        channel* chan = chan->getChannel();
        if (!chan) {
            sender->write("ERR_NOSUCHCHANNEL " + sender->getNickname() + " " + target);
            return;
        }

        if (!chan->is_member(sender)) {
            sender->write("ERR_CANNOTSENDTOCHAN " + sender->getNickname() + " " + target);
            return;
        }

        chan->send_notice(sender->getNickname(), notice);
        return;
    }

    client* dest = sender->getClient(target);
    if (!dest) {
        sender->write("ERR_NOSUCHNICK " + sender->getNickname() + " " + target);
        return;
    }

    dest->write(":" + sender->getNickname() + " NOTICE " + dest->getNickname() + " :" + notice);
}
