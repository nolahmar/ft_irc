#include "client.hpp"
#include "channel.hpp"

void sendMessageToServer(const std::string& message) {
        // Simule l'envoi du message au serveur IRC
        std::cout << "Envoi au serveur IRC : " << message << std::endl;
}

void cap(const std::string& subcommand, const std::string& capabilities) {
        std::string message = "CAP " + subcommand;
        if (!capabilities.empty()) {
            message += " :" + capabilities;
        }
        sendMessageToServer(message);
    }
