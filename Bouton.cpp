#include "Bouton.hpp"

void Bouton::afficher(sf::RenderWindow* fenetre, sf::Vector2f position) {
	sprite.setPosition(sf::Vector2f(positionRelative.x + position.x, positionRelative.y + position.y));
	fenetre->draw(sprite);
	sf::FloatRect dimensionsSprite = sprite.getGlobalBounds();
	sf::FloatRect dimensionsTexte = imageTexte.getGlobalBounds();
	imageTexte.setPosition(sf::Vector2f(dimensionsSprite.left+(dimensionsSprite.width-dimensionsTexte.width)/2, dimensionsSprite.top + (dimensionsSprite.height - dimensionsTexte.height) / 2));
	fenetre->draw(imageTexte);
}

bool Bouton::interactionSouris(sf::Vector2i souris, bool clic) {
	if (pointDansRectangle(sf::Vector2f(souris.x, souris.y), sprite.getGlobalBounds())) {
		sprite.setScale(1.05, 1.05);
		if (clic) return true;
	}
	else {
		sprite.setScale(1, 1);
	}
	return false;
}