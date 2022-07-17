#include "Decor.hpp"

Quete* Decor::interactionSouris(sf::Vector2i souris, bool clic) {
	if (Objet::interactionSouris(souris, clic)) return quete;
	return nullptr;
}