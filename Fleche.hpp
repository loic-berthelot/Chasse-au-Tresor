#pragma once
#include "General.hpp"
#include "Objet.hpp"

class Scene;

class Fleche : public Objet{
	std::string suivant;
public:
	Fleche(std::string _suivant, std::string _nom, sf::Vector2f _position, int _rotation = 0, float _coefTaille = 1) {
		suivant = _suivant;
		position = _position;
		coefTaille = _coefTaille;
		rotation = _rotation;
		sprite.setRotation(rotation);
		nom = _nom;
		creerSprite("ressources/images/fleches/"+nom+".png");
	}
	std::string interactionSouris(sf::Vector2i souris, bool clic);
	std::string getDescription();
};