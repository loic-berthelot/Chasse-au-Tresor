#pragma once
#include "Objet.hpp"

class Ramassable : public Objet {
	bool monnaie;
public:
	Ramassable() {};
	Ramassable(std::string _nom, sf::Vector2f _position=sf::Vector2f(0,0), int _rotation = 0, float _coefTaille = 1) {
		position = _position;
		coefTaille = _coefTaille;
		rotation = _rotation;
		sprite.setRotation(rotation);
		nom = _nom;
		monnaie = (nom.substr(0, 7) == "monnaie");
		creerSprite("ressources/images/ramassables/" + nom + ".png");
	}
	void formaterCase(int tailleCases);
	bool estMonnaie();
	std::string getDescription();
};