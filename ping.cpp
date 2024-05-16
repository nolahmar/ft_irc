#include "client.hpp"
#include "channel.hpp"

//santax: PING <token>
void client::send_pong(const std::string& token) {
        write("PONG :" + token);
}

 void ping(client* client, const std::vector<std::string>& args) {
        if (args.size() < 1 || args[0].empty()) {
            client->write("ERR_NEEDMOREPARAMS " + client->getNickname() + " PING");
            return;
        }

        std::string token = args[0];
        client->send_pong(token);
 }
