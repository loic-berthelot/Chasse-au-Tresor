#pragma once
#include "Objet.hpp"
#include "Quete.hpp"

class Decor : public Objet {
	Quete* quete;
	std::string nomQuete;
public:
	Decor(std::string _nom, std::string _nomQuete, sf::Vector2f _position, int _rotation = 0, float _coefTaille = 1) {
		nom = _nom;
		position = _position;
		coefTaille = _coefTaille;
		rotation = _rotation;
		sprite.setRotation(rotation);
		creerSprite("ressources/images/decors/" + nom + ".png");
		sprite.setScale(coefTaille, coefTaille);
		nomQuete = _nomQuete;
		quete = new Quete(nomQuete);
	}
	Quete* interactionSouris(sf::Vector2i souris, bool clic);
	std::string getNom();
	std::string getDescription();
};