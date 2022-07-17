#include "Fleche.hpp"
#include "General.hpp"


Scene* Fleche::interactionSouris(sf::Vector2i souris, bool clic) {
	if (Objet::interactionSouris(souris, clic)) return suivant;
	return nullptr;
}