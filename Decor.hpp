#pragma once
#include "Objet.hpp"
#include "Quete.hpp"

class Decor : public Objet {
	Quete* quete;
public:
	Decor(std::string _nom, sf::Vector2f _position, int angle = 0, float _coefTaille = 1) {
		nom = _nom;
		position = _position;
		coefTaille = _coefTaille;
		sprite.setRotation(angle);
		creerSprite("images/decors/" + nom + ".png");
		sprite.setScale(coefTaille, coefTaille);
		if (nom == "fantome") {
			quete = new Quete("fantome", "Je suis un fantome.", sf::IntRect(100, 100, 500, 500));
		}
	}
	Quete* interactionSouris(sf::Vector2i souris, bool clic);
};