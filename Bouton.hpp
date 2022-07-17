#pragma once
#include "General.hpp"

class Bouton {
	sf::Sprite sprite;
	sf::Vector2f positionRelative;
	sf::Texture texture;
	std::string nom;
	std::string texte;
	sf::Text imageTexte;
	sf::Font police;
public:
	Bouton(std::string _nom, sf::Vector2f _positionRelative, std::string _texte="") {
		nom = _nom;
		texte = _texte;
		positionRelative = _positionRelative;
		sf::Image image;
		image.loadFromFile("images/boutons/"+nom+".png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sf::FloatRect dimensions = sprite.getGlobalBounds();
		sprite.setOrigin(dimensions.width / 2, dimensions.height / 2);
		police.loadFromFile("polices/arial_narrow_7.ttf");
		imageTexte.setFont(police);
		imageTexte.setString(texte);
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color::Red);
	}
	void afficher(sf::RenderWindow * fenetre, sf::Vector2f position);
	bool interactionSouris(sf::Vector2i souris, bool clic);
};