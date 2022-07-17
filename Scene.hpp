#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Fleche.hpp"
#include "Ramassable.hpp"
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
	}
	Scene(std::string _nom, Fleche* fleche) {
		nom = _nom;
		fleches.clear();
		fleches.push_back(fleche);
	}
	Scene(std::string _nom) {
		nom = _nom;
		fleches.clear();
	}
	void afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle);
	Scene* interactionContenu(sf::Vector2i souris, bool clic, Inventaire* inventaire);
	std::string getNom();
	void ajouterFleche(Fleche* fleche);
	void ajouterRamassable(Ramassable* ramassable);
	void retirerRamassable(Ramassable* ramassable);
	void ajouterDecor(Decor* decor);
	void ajouterQuete(Quete* _quete);
};