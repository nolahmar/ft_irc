#include "client.hpp"
#include "channel.hpp"

//santax: INVITE <nickname> <channel>

void client::invite_to_channel(client* invitedClient, channel* channel) {
    if (!channel) {
        write("ERR_NOSUCHCHANNEL " + nickname + " " + channel->getName());
        return;
    }

    if (!channel->is_member(this)) {
        write("ERR_NOTONCHANNEL " + nickname + " " + channel->getName());
        return;
    }

    if (channel->is_member(invitedClient)) {
        write("ERR_USERONCHANNEL " + nickname + " " + channel->getName());
        return;
    }
    // Envoyer un message d'invitation à l'utilisateur invité
    invitedClient->write("INVITE " + nickname + " " + channel->getName());
    invitedClient->join_channel(channel);

    // Envoyer un message de confirmation à l'utilisateur qui a envoyé l'invitation
    write("RPL_INVITING " + channel->getName());
}

void invite(client* sender, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        sender->write("ERR_NEEDMOREPARAMS " + sender->getNickname() + " INVITE");
        return;
    }

    std::string invitedNickname = args[0];
    std::string channelName = args[1];

    client* invitedClient = sender->getClient(invitedNickname);

    if (!invitedClient) {
        sender->write("ERR_NOSUCHNICK " + sender->getNickname() + " " + invitedNickname);
        return;
    }

    channel* chan = chan->getChannel();
    if (!chan) {
        sender->write("ERR_NOSUCHCHANNEL " + sender->getNickname() + " " + channelName);
        return;
    }

    sender->invite_to_channel(invitedClient, chan);
}