#include "client.hpp"
#include "channel.hpp"

//santax: WHOIS <target> <nickname>

 bool client::is_authorized_for_whois() const {
        // Implémentation simplifiée : toujours autorisé
        return true;
    }

void client::send_to_server(const std::string& message) const {
        // Simule l'envoi d'un message au serveur IRC
        std::cout << "Envoi au serveur IRC : " << message << std::endl;
    }

std::string client::wait_for_response() const {
        // Simule l'attente d'une réponse du serveur IRC
        return "RPL_WHOISUSER " + nickname + " :Username is " + nickname;
    }

void client::process_whois_response(const std::string& response) const {
        // Traite et interprète la réponse du serveur IRC à la commande WHOIS
        std::cout << "Réponse du serveur IRC : " << response << std::endl;
    }

void client::send_whois(const std::string& target, const std::string& nickname) {
    if (!is_authorized_for_whois()) {
            std::cout << "ERR_NOPRIVILEGES " << nickname << " :Vous n'êtes pas autorisé à exécuter la commande WHOIS." << std::endl;
            return;
        }

        // Construit la requête WHOIS avec le pseudo cible et le pseudo pour lequel les informations sont demandées
        std::string whoisRequest = "WHOIS " + target + " " + nickname;

        // Envoie la requête WHOIS au serveur IRC
        send_to_server(whoisRequest);

        // Attend la réponse du serveur IRC
        std::string serverResponse = wait_for_response();

        // Traite et interprète la réponse du serveur IRC
        process_whois_response(serverResponse);
    }

void whois(client* client, const std::vector<std::string>& args){
        if (args.size() < 1) {
            client->write("ERR_NONICKNAMEGIVEN " + client->getNickname());
            return;
        }

        std::string target;
        std::string nickname;

        if (args.size() == 1) {
            target = client->getNickname();
            nickname = args[0];
        } else {
            target = args[0];
            nickname = args[1];
        }

        client->send_whois(target, nickname);
}
