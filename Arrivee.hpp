#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Arrivee {
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
public:
	Arrivee() {
		sf::Image image;
		image.loadFromFile("ressources/images/divers/arrivee.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sf::FloatRect dimensions = sprite.getGlobalBounds();
		sprite.setOrigin(sf::Vector2f(dimensions.width / 2, dimensions.height / 2));
	}
	void afficher(sf::RenderWindow* fenetre);
	void deplacer(sf::Vector2f _position);
};