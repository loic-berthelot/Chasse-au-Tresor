#include "Decor.hpp"

Quete* Decor::interactionSouris(sf::Vector2i souris, bool clic) {
	if (Objet::interactionSouris(souris, clic)) return quete;
	return nullptr;
}

std::string Decor::getNom() {
	return nom;
}

std::string Decor::getDescription() {
	return nom + ", " + nomQuete + ", " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(rotation) + ", " + std::to_string(coefTaille);
}