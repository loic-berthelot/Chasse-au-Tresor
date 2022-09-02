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

Scene* getScene(std::string nom);
bool verifierCondition(std::string ligne);
int calculerReference(std::vector<std::string> _lignes, int ligneActuelle, std::string deplacement);
void executerLigne(std::string ligne);
void executerAlgorithme(std::vector<std::string> _lignes);
void executerAlgorithme(std::string nom);

class Scene {
	std::string nom;
	std::vector<Fleche*> fleches;
	std::vector<Ramassable*> ramassables;
	std::vector<Decor*> decors;
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string musique;
	std::string carte;
	sf::Vector2f positionCurseur;
	float angleCurseur;
public:
	void executerLigne(std::string ligne, bool remplir);
	void chargerFichier(std::string nom, bool remplir);
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
	Scene(std::string _nom, bool remplir) {
		nom = _nom;
		fleches.clear();
		scenes.push_back(this);
		chargerFichier(nom, remplir);
	}
	void afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle);
	Scene* interactionContenu(sf::Vector2i souris, bool clic, Inventaire* inventaire, sf::Event* evenementTexte);
	std::string getNom();
	void ajouterFleche(Fleche* fleche);
	void ajouterRamassable(Ramassable* ramassable);
	void retirerRamassable(Ramassable* ramassable);
	void retirerRamassable(std::string nom, sf::Vector2f position = sf::Vector2f(-1,-1));
	void ajouterDecor(Decor* decor);
	void retirerDecor(std::string nom);
	void ajouterQuete(Quete* _quete);
	std::string getMusique();
	sf::Vector2f getPositionCurseur();
	float getAngleCurseur();
	std::string getCarte();
	int tailleFleches();
	int tailleRamassables();
	int tailleDecors();
	std::string getDescription(std::string type, int indice);
};