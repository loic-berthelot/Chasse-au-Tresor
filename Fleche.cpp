#include "Fleche.hpp"

std::string Fleche::interactionSouris(sf::Vector2i souris, bool clic) {
	if (Objet::interactionSouris(souris, clic)) return suivant;
	return "";
}