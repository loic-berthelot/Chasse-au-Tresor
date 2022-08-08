#pragma once
#include "Objet.hpp"
#include "Quete.hpp"

class Decor : public Objet {
	Quete* quete;
public:
	Decor(std::string _nom, std::string nomQuete, sf::Vector2f _position, int angle = 0, float _coefTaille = 1) {
		nom = _nom;
		position = _position;
		coefTaille = _coefTaille;
		sprite.setRotation(angle);
		creerSprite("ressources/images/decors/" + nom + ".png");
		sprite.setScale(coefTaille, coefTaille);
		quete = new Quete(nomQuete);
	}
	Quete* interactionSouris(sf::Vector2i souris, bool clic);
	std::string getNom();
};