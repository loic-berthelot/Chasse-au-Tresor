#pragma once
#include "Objet.hpp"

class Ramassable : public Objet {
public:
	Ramassable(std::string _nom, sf::Vector2f _position=sf::Vector2f(0,0), int angle = 0, float _coefTaille = 1) {
		position = _position;
		coefTaille = _coefTaille;
		sprite.setRotation(angle);
		nom = _nom;
		creerSprite("images/ramassables/" + nom + ".png");
	}
	void formaterCase(int tailleCases);
};