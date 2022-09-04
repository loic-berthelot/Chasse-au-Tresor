#pragma once
#include "General.hpp"

extern int largeurFenetre;
extern int hauteurFenetre;

class Carte {
	sf::Sprite sprite;
	sf::Texture textureSprite;
	sf::Vector2f positionSprite;
	
	sf::Vector2f taille;
	sf::Sprite curseur;
	sf::Texture textureCurseur;
	sf::Vector2f positionCurseur;
	float angleCurseur;
public:
	std::string nom;
	void changerCarte(std::string _nom);
	void changerCurseur(sf::Vector2f _position, float _angle);
	Carte() {
		taille = sf::Vector2f(225, 135);
		positionSprite = sf::Vector2f(largeurFenetre - taille.x - 10, hauteurFenetre - taille.y - 10);
		sprite.setPosition(positionSprite);
		changerCarte("etang.png");
		sf::Image image;
		image.loadFromFile("ressources/images/divers/curseur.png");
		textureCurseur.loadFromImage(image);
		curseur.setTexture(textureCurseur);
		sf::FloatRect dimensionsCurseur = curseur.getGlobalBounds();
		curseur.setOrigin(sf::Vector2f(dimensionsCurseur.width / 2, dimensionsCurseur.height / 2));
		positionCurseur = sf::Vector2f(0.5, 0.5);
		angleCurseur = 0;
	}
	void afficher(sf::RenderWindow* fenetre);
};