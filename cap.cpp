#include "client.hpp"
#include "channel.hpp"

//santax: CAP <subcommand> <capabilities>

void send_message_to_server(const std::string& message) {
        std::cout << "Envoi au serveur IRC : " << message << std::endl;
}

void cap(const std::string& subcommand, const std::string& capabilities) {
    std::string message = "CAP " + subcommand;

    if (subcommand == "REQ" || subcommand == "ACK" || subcommand == "NAK") {
        if (!capabilities.empty()) {
            message += " :" + capabilities;
        }
    }
    else if (subcommand == "LS") {
    } 
    else {
        std::cerr << "Sous-commande inconnue : " << subcommand << std::endl;
        return;
    }

    send_message_to_server(message);
}