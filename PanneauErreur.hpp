#pragma once
#include "General.hpp"

extern sf::Font police;

class PanneauErreur {
	std::string texte;
	sf::Text imageTexte;
	sf::RectangleShape rectangle;
	sf::Vector2f position;
public:
	PanneauErreur(sf::Vector2f _position) {
		position = _position;
		imageTexte.setPosition(sf::Vector2f(position.x + 20, position.y + 20));
		imageTexte.setFont(police);
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color::White);
		rectangle.setPosition(sf::Vector2f(position));
		rectangle.setSize(sf::Vector2f(500, 200));
		rectangle.setFillColor(sf::Color::Black);
	}
	void changerTexte(std::string _texte);
	void afficher(sf::RenderWindow * fenetre);
	void fermer();
};