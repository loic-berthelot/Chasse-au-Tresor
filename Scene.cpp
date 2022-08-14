#include "Scene.hpp"
#include <iostream>
#include <fstream>

extern std::vector<Scene*> scenes;
extern Inventaire* inventaire;

Scene* getScene(std::string nom) {
	for (int i = 0; i < scenes.size(); i++) {
		if (scenes[i]->getNom() == nom) return scenes[i];
	}
	return nullptr;
}

void Scene::afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle) {
	for (int i = 0; i < fleches.size(); i++) fleches[i]->afficher(fenetre);
	for (int i = 0; i < ramassables.size(); i++) ramassables[i]->afficher(fenetre);
	for (int i = 0; i < decors.size(); i++)	decors[i]->afficher(fenetre);
	if (quete != nullptr) quete->afficher(fenetre);
}

void Scene::executerAlgorithme(std::string nom) {
	std::ifstream flux("ressources/algorithmes/"+nom + ".txt");
	std::string ligne, mot, role;
	bool guillemets;
	int indiceBloc, indiceMot;
	std::string tableau[10];
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
						if (indiceBloc == 0) {
							if (role == "fermer_quete") quete = nullptr;
						} else if (indiceBloc == 1) {
							if (role == "progression") {
								progression->ajouterClee(tableau[0]);
							} else if (role == "condition_objet") {
								if (not inventaire->contient(tableau[0])) return;
							} else if (role == "condition_saisie") {
								if (progression->getValeur(tableau[0]) != tableau[1]) return;
							} else if (role == "ajouter_fleche") {
								getScene(tableau[0])->ajouterFleche(new Fleche(tableau[1], sf::Vector2f(std::stof(tableau[2]), std::stof(tableau[3])), std::stoi(tableau[4]), std::stof(tableau[5]), tableau[6]));
								progression->ajouterClee(ligne);
							} else if (role == "retirer_decor") {
								getScene(tableau[0])->retirerDecor(tableau[1]);
								progression->ajouterClee(ligne);
							} else if (role == "retirer_inventaire") {
								inventaire->retirerRamassable(tableau[0]);
							}
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
}

Scene* Scene::interactionContenu(sf::Vector2i souris, bool clic, Inventaire* inventaire, sf::Event* evenementTexte) {
	Decor* decor;
	if (quete == nullptr) {
		Quete* _quete;
		for (int i = 0; i < decors.size(); i++) {
			decor = decors[i];
			_quete = decor->interactionSouris(souris, clic);
			if (_quete != nullptr) quete = _quete;
		}
		Ramassable* ramassable;
		for (int i = 0; i < ramassables.size(); i++) {
			ramassable = ramassables[i];
			if (ramassable->interactionSouris(souris, clic)) {
				retirerRamassable(ramassable);
				if (ramassable->estMonnaie()) inventaire->ajouterMonnaie(1);
				else inventaire->ajouterRamassable(ramassable);
			}
		}
		Scene* suivant;
		for (int i = 0; i < fleches.size(); i++) {
			suivant = getScene(fleches[i]->interactionSouris(souris, clic));
			if (suivant != nullptr) {
				return suivant;
			}
		}
	}
	else {
		std::string resultat = quete->interactionSouris(souris, clic, evenementTexte);
		if (resultat != "") {
			if (resultat == "fermer") quete = nullptr;
			else executerAlgorithme(resultat);
		}
	}
	return this;
}

std::string Scene::getNom() { return nom; }

void Scene::ajouterFleche(Fleche* fleche) {
	fleches.push_back(fleche);
}

void Scene::ajouterRamassable(Ramassable* ramassable) {
	ramassables.push_back(ramassable);
}

void Scene::retirerRamassable(Ramassable* ramassable) {
	for (int i = 0; i < ramassables.size(); i++) {
		if (ramassables[i] == ramassable) ramassables.erase(ramassables.begin() + i);
	}
}

void Scene::ajouterDecor(Decor* decor) {
	decors.push_back(decor);
}

void Scene::retirerDecor(std::string nom) {
	for (int i = 0; i < decors.size(); i++) {
		if (decors[i]->getNom() == nom) {
			decors.erase(decors.begin() + i);
			return;
		}
	}
}

void Scene::ajouterQuete(Quete* _quete) {
	quete = _quete;
}

std::string Scene::getMusique() {
	return musique;
}