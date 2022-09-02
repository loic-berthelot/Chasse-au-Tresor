#pragma once
#include "General.hpp"

class Objet {
protected:
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Texture texture;
	float rayon, coefTaille, rotation;
	std::string nom;
	int etatClic = 0;
public:
	Objet() {}
	void creerSprite(std::string adresse);
	sf::Sprite getSprite();
	void adapterEchelle(sf::Vector2f echelle);
	bool interactionSouris(sf::Vector2i souris, bool clic);
	void setCoefTaille(float _coefTaille);
	void setPosition(sf::Vector2f _position);
	void afficher(sf::RenderWindow* fenetre);
	std::string getNom();
	sf::Vector2f getPosition();
	sf::Sprite retournerSprite();
};