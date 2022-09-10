#include "Arrivee.hpp"

void Arrivee::afficher(sf::RenderWindow* fenetre) {
	fenetre->draw(sprite);
}

void Arrivee::deplacer(sf::Vector2f _position) {
	position = _position;
	sprite.setPosition(position);
}