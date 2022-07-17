#pragma once
#include "General.hpp"
#include "Bouton.hpp"

class Quete {
	std::string nom;
	std::string texte;
	std::vector<Bouton*> boutons;
	Bouton* boutonFermer;
	sf::Vector2f position;
	sf::RectangleShape sprite;
public:
	void ajouterBouton(Bouton* bouton);
	Quete(std::string _nom, std::string _texte, sf::IntRect dimensions) {
		nom = _nom;
		texte = _texte;
		boutonFermer = new Bouton("fermer", sf::Vector2f(35, 35));
		ajouterBouton(boutonFermer);
		sprite.setFillColor(sf::Color(255, 200, 95));
		sprite.setSize(sf::Vector2f(dimensions.width, dimensions.height));
		sprite.setOutlineColor(sf::Color(200, 200, 200));
		sprite.setOutlineThickness(2);
		position = sf::Vector2f(dimensions.left, dimensions.top);
		sprite.setPosition(position);
		if (nom == "fantome") {
			ajouterBouton(new Bouton("texte1", sf::Vector2f(60, dimensions.height-35), "Bouh !"));
		}
	}
	void afficher(sf::RenderWindow * fenetre);
	void interactionSouris(sf::Vector2i souris, bool clic);
};