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
		std::ifstream flux("ressources/quetes/" + nom + ".txt");
		std::string ligne, mot, role;
		int indiceBloc, indiceMot;
		std::string tableau[10];
		bool guillemets;
		if (flux) {
			while (std::getline(flux, ligne)) {
				ligne += ':';
				mot = "";
				role = "";
				indiceBloc = 0;
				indiceMot = 0;
				guillemets = false;
				for (int i = 0; i < ligne.length(); i++) {
					if ((ligne[i] == ':' or ligne[i] == ',') and not guillemets) {
						while (mot[mot.length() - 1] == ' ') mot = mot.substr(0, mot.length() - 1);
						if (indiceBloc == 0) role = mot;
						else tableau[indiceMot] = mot;
						if (ligne[i] == ':') {
							if (role == "texte" and indiceBloc == 1) {
								imageTexte.setString(tableau[0]);
								imageTexte.setPosition(sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])));
								textes.push_back(imageTexte);
							} else if (role == "saisie" and indiceBloc == 1) {
								boutons.push_back(new BarreSaisie(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])), sf::Vector2f(std::stof(tableau[3]), std::stof(tableau[4]))));
							}
							else if (role == "bouton" and indiceBloc == 1) {
								if (indiceMot < 4) boutons.push_back(new Bouton(tableau[0], tableau[1], sf::Vector2f(std::stof(tableau[2]), std::stof(tableau[3]))));
								else boutons.push_back(new Bouton(tableau[0], tableau[1], sf::Vector2f(std::stof(tableau[2]), std::stof(tableau[3])), tableau[4]));
							}
							indiceBloc++;
							indiceMot = 0;
						}
						else if (ligne[i] == ',') indiceMot++;
						mot = "";
					}
					else if (ligne[i] == '"') guillemets = not guillemets;
					else if (ligne[i] != ' ' or mot.length() > 0) mot += ligne[i];
				}
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