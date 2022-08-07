#pragma once
#include "General.hpp"
#include "BarreSaisie.hpp"

class Quete {
	std::string nom;
	std::string texte;
	std::vector<Bouton*> boutons;
	Bouton* boutonFermer;
	sf::Vector2f position;
	sf::RectangleShape sprite;
	sf::Font police;
	sf::Text imageTexte;
public:
	void ajouterBouton(Bouton* bouton);
	Quete(std::string _nom, std::string _texte, sf::Vector2f dimensionsFenetre) {
		nom = _nom;
		texte = _texte;
		boutonFermer = new Bouton("fermer", "fermer", sf::Vector2f(35, 35));
		ajouterBouton(boutonFermer);
		sprite.setFillColor(sf::Color(255, 200, 95));
		sprite.setSize(sf::Vector2f(dimensionsFenetre.x-350, dimensionsFenetre.y-100));
		sprite.setOutlineColor(sf::Color(200, 200, 200));
		sprite.setOutlineThickness(2);
		position = sf::Vector2f(50, 50);
		sprite.setPosition(position);
		sf::FloatRect dimensionsSprite = sprite.getGlobalBounds();
		if (nom == "fantome") {
			ajouterBouton(new Bouton("fantome", "texte1", sf::Vector2f(60, dimensionsSprite.height - 35), "Bouh !"));
			ajouterBouton(new BarreSaisie("barreFantome", sf::Vector2f(250, 200), sf::Vector2f(400, 50)));
		}
		police.loadFromFile("ressources/polices/arial_narrow_7.ttf");
		imageTexte.setFont(police);
		imageTexte.setString(texte);
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color(40, 40, 40));
		imageTexte.setPosition(sf::Vector2f(position.x+10, position.y+50));
	}
	void afficher(sf::RenderWindow * fenetre);
	std::string interactionSouris(sf::Vector2i souris, bool clic, sf::Event* evenementTexte);
	std::string getTexte(std::string _nom);
};