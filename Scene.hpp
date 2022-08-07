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
		if (flux) {
			while (std::getline(flux, ligne)) {
				mot = "";
				indiceBloc = 0;
				indiceMot = 0;
				ligne += ':';
				for (int i = 0; i < ligne.length(); i++) {
					if (ligne[i] == ':' or ligne[i] == ',') {
						while (mot [mot.length()-1] == ' ') mot = mot.substr(0, mot.length() - 1);
						if (indiceBloc == 0) {
							role = mot;
						} else {
							if (role == "fleche") {
								std::cout << "fleche";
								ajouterFleche(new Fleche("maison", sf::Vector2f(550, 400), 20));
							}
						}
						mot = "";
						if (ligne[i] == ':') {
							indiceBloc++;
							indiceMot = 0;
						}
						else {
							indiceMot++;
						}
					}
					else if (ligne[i] != ' ' or mot.length() > 0)  mot += ligne[i];
				}
			}
		}
	}
	void afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle);
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