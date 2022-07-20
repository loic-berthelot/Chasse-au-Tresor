#pragma once
#include "General.hpp"
#include "Ramassable.hpp"

class Inventaire {
	sf::Vector2f taille;
	sf::RectangleShape sprite;
	sf::Texture textureSprite;
	sf::RectangleShape rectangle;
	sf::Font police;
	sf::Text imageTexte;
	sf::CircleShape piece;
	sf::Texture texturePiece;
	std::vector<Ramassable*> ramassables;
	int tailleCases = 50;
	int places = 48;
	int monnaie = 3;
public:
	Inventaire(sf::Vector2f _taille) {
		taille = _taille;
		sprite.setSize(taille);
		sf::Image image;
		image.loadFromFile("images/textures/inventaire.png");
		textureSprite.loadFromImage(image);
		sprite.setTexture(&texture);

		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color(200, 200, 200));
		rectangle.setOutlineThickness(2);
		rectangle.setSize(sf::Vector2f(tailleCases, tailleCases));

		police.loadFromFile("polices/arial_narrow_7.ttf");
		imageTexte.setFont(police);
		imageTexte.setString(std::to_string(monnaie));
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color(255, 255, 0));

		p
	}
	void afficher(sf::RenderWindow* fenetre, sf::Vector2f position);
	void ajouterRamassable(Ramassable* ramassable);
	void retirerRamassable(std::string nom);
	bool contient(std::string nom);
	int getMonnaie();
	void ajouterMonnaie(int valeur);
	bool acheter(int valeur);
};