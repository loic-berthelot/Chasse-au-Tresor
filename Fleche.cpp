#include "Fleche.hpp"

std::string Fleche::interactionSouris(sf::Vector2i souris, bool clic) {
	if (Objet::interactionSouris(souris, clic)) return suivant;
	return "";
}
std::string Fleche::getDescription() {
	return suivant+", "+ nom + ", " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(rotation) + ", " + std::to_string(coefTaille);
}