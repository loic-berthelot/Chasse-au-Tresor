#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Fleche.hpp"
#include "Ramassable.hpp"
#include "Monnaie.hpp"
#include "Inventaire.hpp"
#include "Decor.hpp"
#include "Quete.hpp"

class Scene {
	std::string nom;
	std::vector<Fleche*> fleches;
	std::vector<Ramassable*> ramassables;
	std::vector<Decor*> decors;
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
	Quete* quete = nullptr;
public:
	Scene(std::string _nom, std::vector<Fleche*> _fleches) {
		nom = _nom;
		fleches = _fleches;
		scenes.push_back(this);
	}
	Scene(std::string _nom, Fleche* fleche) {
		nom = _nom;
		fleches.clear();
		fleches.push_back(fleche);
		scenes.push_back(this);
	}
	Scene(std::string _nom) {
		nom = _nom;
		fleches.clear();
		scenes.push_back(this);
		std::ifstream flux("ressources/scenes/"+nom+".txt");
		std::string ligne, mot, role;
		int indiceBloc, indiceMot;
		std::string tableau[10];
		if (flux) {
			while (std::getline(flux, ligne)) {
				ligne += ':';
				mot = "";
				role = "";
				indiceBloc = 0;
				indiceMot = 0;				
				for (int i = 0; i < ligne.length(); i++) {
					if (ligne[i] == ':' or ligne[i] == ',') {
						while (mot [mot.length()-1] == ' ') mot = mot.substr(0, mot.length() - 1);
						if (indiceBloc == 0) role = mot;
						else tableau[indiceMot] = mot;
						if (ligne[i] == ':') {
							if (role == "fleche" and indiceBloc == 1) {
								if (indiceMot < 3) ajouterFleche(new Fleche(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2]))));
								else if (indiceMot < 4) ajouterFleche(new Fleche(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])), std::stoi(tableau[3])));
								else if (indiceMot < 5) ajouterFleche(new Fleche(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])), std::stoi(tableau[3]), std::stof(tableau[4])));
								else ajouterFleche(new Fleche(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])), std::stoi(tableau[3]), std::stof(tableau[4]), tableau[5]));
							} else if ((role == "ramassable" or role == "monnaie") and indiceBloc == 1) {
								if (indiceMot < 1) ajouterRamassable(new Ramassable(tableau[0]));
								else if (indiceMot < 3) ajouterRamassable(new Ramassable(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2]))));
								else if (indiceMot < 4) ajouterRamassable(new Ramassable(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])), std::stof(tableau[3])));
								else ajouterRamassable(new Ramassable(tableau[0], sf::Vector2f(std::stof(tableau[1]), std::stof(tableau[2])), std::stof(tableau[3]), std::stof(tableau[4])));
							} else if (role == "decor" and indiceBloc == 1) {
								if (indiceMot < 4) ajouterDecor(new Decor(tableau[0], tableau[1], sf::Vector2f(std::stof(tableau[2]), std::stof(tableau[3]))));
								else if (indiceMot < 5) ajouterDecor(new Decor(tableau[0], tableau[1], sf::Vector2f(std::stof(tableau[2]), std::stof(tableau[3])), std::stoi(tableau[4])));
								else ajouterDecor(new Decor(tableau[0], tableau[1], sf::Vector2f(std::stof(tableau[2]), std::stof(tableau[3])), std::stoi(tableau[4]), std::stof(tableau[5])));
							}
							indiceBloc++;
							indiceMot = 0;
						}
						else if (ligne[i] == ',') indiceMot++;
						mot = "";
					} else if (ligne[i] != ' ' or mot.length() > 0) mot += ligne[i];
				}
			}
		}
	}
	void afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle);
	void executerAlgorithme(std::string nom);
	Scene* interactionContenu(sf::Vector2i souris, bool clic, Inventaire* inventaire, sf::Event* evenementTexte);
	std::string getNom();
	void ajouterFleche(Fleche* fleche);
	void ajouterRamassable(Ramassable* ramassable);
	void retirerRamassable(Ramassable* ramassable);
	void ajouterMonnaie(Monnaie* monnaie);
	void retirerMonnaie(Monnaie* monnaie);
	void ajouterDecor(Decor* decor);
	void retirerDecor(std::string nom);
	void ajouterQuete(Quete* _quete);
};