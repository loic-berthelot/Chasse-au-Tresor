#include "Objet.hpp"

sf::Sprite Objet::getSprite() { return sprite; }

void Objet::creerSprite(std::string adresse) {
	sf::Image image;
	image.loadFromFile(adresse);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sf::FloatRect taille = sprite.getGlobalBounds();
	rayon = std::max(taille.width, taille.height) / 2 * coefTaille;
	sprite.setOrigin(taille.width/2, taille.height/2);
}

void Objet::adapterEchelle(sf::Vector2f echelle) {
	sprite.setPosition(sf::Vector2f(position.x * echelle.x, position.y * echelle.y));
}

bool Objet::interactionSouris(sf::Vector2i souris, bool clic) {
	if (distance(sprite.getPosition(), souris) < rayon) {
		sprite.setScale(1.05 * coefTaille, 1.05 * coefTaille);
		if (clic) return true;
	}
	else {
		sprite.setScale(coefTaille, coefTaille);
	}
	return false;
}

void Objet::setCoefTaille(float _coefTaille) {
	coefTaille = _coefTaille;
}

void Objet::setPosition(sf::Vector2f _position) {
	sprite.setPosition(_position);
}

sf::Sprite Objet::retournerSprite() {
	return sprite;
}