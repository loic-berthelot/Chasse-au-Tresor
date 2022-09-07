#pragma once
#include "Bouton.hpp"

class BarreSaisie : public Bouton {
	bool selectionne;
	sf::RectangleShape sprite;
public:
	BarreSaisie(std::string _nom, sf::Vector2f _positionRelative, sf::Vector2f dimensions) {
		nom = _nom;
		texte = "";
		type = "barreSaisie";
		positionRelative = _positionRelative;
		sprite.setSize(dimensions);
		sprite.setOrigin(dimensions.x / 2, dimensions.y / 2);
		sprite.setFillColor(sf::Color::Black);
		sprite.setOutlineColor(sf::Color::White);
		imageTexte.setFont(police);
		imageTexte.setString(texte);
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color::White);
		etatClic = 0;
		selectionne = false;
	}
	virtual void reagirEntree(sf::Event* evenement);
	virtual void selectionner(bool selection);
	virtual bool interactionSouris(sf::Vector2i souris, bool clic);
	virtual void afficher(sf::RenderWindow* fenetre, sf::Vector2f position, sf::Vector2f dimensionsCadre = sf::Vector2f(0,0));
};