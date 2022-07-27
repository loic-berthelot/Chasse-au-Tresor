#include "Ramassable.hpp"

void Ramassable::formaterCase(int tailleCases) {
	sf::FloatRect dimensions = sprite.getGlobalBounds();
	if (dimensions.width > dimensions.height) coefTaille *= 50/dimensions.width;
	else coefTaille *= 50/dimensions.height;
	sprite.setScale(coefTaille, coefTaille);
}

bool Ramassable::estMonnaie() {
	return monnaie;
}