#pragma once
#include "General.hpp"

class Bouton {
protected:
	sf::Sprite sprite;
	sf::Vector2f positionRelative;
	sf::Texture texture;
	std::string nom;
	std::string type;
	std::string texte;
	sf::Text imageTexte;
	sf::Font police;
	int etatClic;
public:
	Bouton() {}
	Bouton(std::string _nom, std::string _type, sf::Vector2f _positionRelative, std::string _texte="") {
		nom = _nom;
		texte = _texte;
		type = _type;
		positionRelative = _positionRelative;
		sf::Image image;
		image.loadFromFile("ressources/images/boutons/"+type+".png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sf::FloatRect dimensions = sprite.getGlobalBounds();
		sprite.setOrigin(dimensions.width / 2, dimensions.height / 2);
		police.loadFromFile("ressources/polices/arial_narrow_7.ttf");
		imageTexte.setFont(police);
		imageTexte.setString(texte);
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color::Black);
		etatClic = 0;
	}
	virtual void afficher(sf::RenderWindow * fenetre, sf::Vector2f position);
	virtual bool interactionSouris(sf::Vector2i souris, bool clic);
	std::string getNom();
	std::string getType();
	std::string getTexte();
	void changerType(std::string _type);
	void changerTexte(std::string _texte);
	virtual void selectionner(bool selection);
	virtual void reagirEntree(sf::Event* evenement);
};