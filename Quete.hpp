#pragma once
#include "General.hpp"
#include "BarreSaisie.hpp"

extern int largeurFenetre;
extern int hauteurFenetre;

class Quete {
	std::string nom;
	std::string texte;
	std::vector<Bouton*> boutons;
	std::vector<sf::Text> textes;
	Bouton* boutonFermer;
	sf::Vector2f position;
	sf::RectangleShape sprite;
	sf::Font police;
public:
	void ajouterBouton(Bouton* bouton);
	Quete(std::string _nom) {
		nom = _nom;
		police.loadFromFile("ressources/polices/arial_narrow_7.ttf");
		sf::Text imageTexte;
		imageTexte.setFont(police);
		imageTexte.setCharacterSize(24);
		imageTexte.setFillColor(sf::Color(40, 40, 40));
		std::vector<std::string> lignes = lireFichier("ressources/quetes/" + nom + ".txt");
		std::vector<std::vector<std::string>> mots;
		std::string role;
		for (int i = 0; i < lignes.size(); i++) {
			mots = lireLigne(lignes[i]);
			role = mots[0][0];
			if (role == "texte") {
				imageTexte.setString(mots[1][0]);
				imageTexte.setPosition(sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2])));
				textes.push_back(imageTexte);
			} else if (role == "saisie") {
				boutons.push_back(new BarreSaisie(mots[1][0], sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2])), sf::Vector2f(std::stof(mots[1][3]), std::stof(mots[1][4]))));
			}
			else if (role == "bouton") {
				if (mots[1].size() < 5) boutons.push_back(new Bouton(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3]))));
				else boutons.push_back(new Bouton(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3])), mots[1][4]));
			}				
		}
		boutonFermer = new Bouton("fermer", "fermer", sf::Vector2f(35, 35));
		ajouterBouton(boutonFermer);
		sprite.setFillColor(sf::Color(255, 200, 95));
		sprite.setSize(sf::Vector2f(largeurFenetre-350, hauteurFenetre-100));
		sprite.setOutlineColor(sf::Color(200, 200, 200));
		sprite.setOutlineThickness(2);
		position = sf::Vector2f(50, 50);
		sprite.setPosition(position);
		sf::FloatRect dimensionsSprite = sprite.getGlobalBounds();
	}
	void afficher(sf::RenderWindow * fenetre);
	std::string interactionSouris(sf::Vector2i souris, bool clic, sf::Event* evenementTexte);
	std::string getTexte(std::string _nom);
};