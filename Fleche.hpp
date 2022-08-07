#pragma once
#include "General.hpp"
#include "Objet.hpp"

class Scene;

class Fleche : public Objet{
	std::string suivant;
public:
	Fleche(std::string _suivant, sf::Vector2f _position, int angle = 0, float _coefTaille = 1, std::string _nom = "fleche1") {
		suivant = _suivant;
		position = _position;
		coefTaille = _coefTaille;
		sprite.setRotation(angle);
		nom = _nom;
		creerSprite("ressources/images/fleches/"+nom+".png");
	}
	std::string interactionSouris(sf::Vector2i souris, bool clic);
};