#include "client.hpp"
#include "channel.hpp"

//santaxe: KILL <nickname> <comment>

void client::quit_network(client* client, const std::string& reason) const {
    for (std::vector<channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        channel* channel = *it;
        channel->remove_user(client);
    }
    std::cout << "ERROR: Closing Link: <servername> (Killed by operator (" << reason << "))" << std::endl;
}

void kill(client* operatorClient, client* targetClient, const std::string& reason) {
        if (!targetClient) {
            operatorClient->write("ERR_NOSUCHSERVER " + operatorClient->getNickname());
            return;
        }
        std::string killer = operatorClient->getNickname();
        std::string killMessage = "Killed by operator (" + killer + "): " + reason;
        targetClient->quit_network(operatorClient, reason);
    }