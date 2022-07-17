#pragma once
#include "General.hpp"
#include "Ramassable.hpp"

class Inventaire {
	sf::Vector2f taille;
	sf::RectangleShape sprite;
	sf::RectangleShape rectangle;
	sf::Texture texture;
	std::vector<Ramassable*> ramassables;
	int tailleCases = 50;
public:
	Inventaire(sf::Vector2f _taille) {
		taille = _taille;
		sprite.setSize(taille);
		sf::Image image;
		image.loadFromFile("images/textures/inventaire.png");
		texture.loadFromImage(image);
		sprite.setTexture(&texture);

		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color(200, 200, 200));
		rectangle.setOutlineThickness(2);
		rectangle.setSize(sf::Vector2f(tailleCases, tailleCases));
	}
	void afficher(sf::RenderWindow* fenetre, sf::Vector2f position);
	void ajouterRamassable(Ramassable* ramassable);
	void retirerRamassable(Ramassable* ramassable);
};