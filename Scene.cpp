#include "Scene.hpp"

extern std::vector<Scene*> scenes;
extern Inventaire* inventaire;

Scene* getScene(std::string nom) {
	for (int i = 0; i < scenes.size(); i++) {
		if (scenes[i]->getNom() == nom) return scenes[i];
	}
	return nullptr;
}

void Scene::chargerFichier(std::string nom) {
	std::cout << "ok";
	musique = "";
	carte = "";
	std::vector<std::string> lignes = lireFichier("ressources/scenes/" + nom + ".txt");
	std::vector<std::vector<std::string>> mots;
	std::string role;
	for (int i = 0; i < lignes.size(); i++) {
		mots = lireLigne(lignes[i]);
		for (int j = 0; j < mots.size(); j++) {
			if (j == 0) role = mots[j][0];
			else if (j == 1) {
				if (role == "fleche") {
					if (mots[j].size() < 4) ajouterFleche(new Fleche(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2]))));
					else if (mots[j].size() < 5) ajouterFleche(new Fleche(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2])), std::stoi(mots[j][3])));
					else if (mots[j].size() < 6) ajouterFleche(new Fleche(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2])), std::stoi(mots[j][3]), std::stof(mots[j][4])));
					else ajouterFleche(new Fleche(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2])), std::stoi(mots[j][3]), std::stof(mots[j][4]), mots[j][5]));
				}
				else if (role == "ramassable" or role == "monnaie") {
					if (mots[j].size() < 2) ajouterRamassable(new Ramassable(mots[j][0]));
					else if (mots[j].size() < 4) ajouterRamassable(new Ramassable(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2]))));
					else if (mots[j].size() < 5) ajouterRamassable(new Ramassable(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2])), std::stof(mots[j][3])));
					else ajouterRamassable(new Ramassable(mots[j][0], sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2])), std::stof(mots[j][3]), std::stof(mots[j][4])));
				}
				else if (role == "decor") {
					if (mots[j].size() < 5) ajouterDecor(new Decor(mots[j][0], mots[j][1], sf::Vector2f(std::stof(mots[j][2]), std::stof(mots[j][3]))));
					else if (mots[j].size() < 6) ajouterDecor(new Decor(mots[j][0], mots[j][1], sf::Vector2f(std::stof(mots[j][2]), std::stof(mots[j][3])), std::stoi(mots[j][4])));
					else ajouterDecor(new Decor(mots[j][0], mots[j][1], sf::Vector2f(std::stof(mots[j][2]), std::stof(mots[j][3])), std::stoi(mots[j][4]), std::stof(mots[j][5])));
				}
				else if (role == "musique") {
					musique = mots[j][0];
				}
				else if (role == "position") {
					positionCurseur = sf::Vector2f(std::stof(mots[j][0]), std::stof(mots[j][1]));
				}
				else if (role == "carte") {
					carte = mots[j][0];
					positionCurseur = sf::Vector2f(std::stof(mots[j][1]), std::stof(mots[j][2]));
					angleCurseur = std::stof(mots[j][3]);
				}
			}
		}
	}
}

void Scene::afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle) {
	for (int i = 0; i < fleches.size(); i++) fleches[i]->afficher(fenetre);
	for (int i = 0; i < ramassables.size(); i++) ramassables[i]->afficher(fenetre);
	for (int i = 0; i < decors.size(); i++)	decors[i]->afficher(fenetre);
	if (quete != nullptr) quete->afficher(fenetre);
}

void Scene::executerAlgorithme(std::string nom) {
	std::vector<std::string> lignes = lireFichier("ressources/algorithmes/" + nom + ".txt");
	std::vector<std::vector<std::string>> mots;
	std::string role;
	for (int i = 0; i < lignes.size(); i++) {
		mots = lireLigne(lignes[i]);
		for (int j = 0; j < lignes[i].size(); j++) {
			if (j == 0) {
				role = mots[j][0];
				if (role == "fermer_quete") quete = nullptr;
			}
			else if (j == 1) {
				if (role == "progression") {
					progression->ajouterClee(mots[j][0]);
				}
				else if (role == "condition_objet") {
					if (not inventaire->contient(mots[j][0])) return;
				}
				else if (role == "condition_saisie") {
					if (progression->getValeur(mots[j][0]) != mots[j][1]) return;
				}
				else if (role == "ajouter_fleche") {
					getScene(mots[j][0])->ajouterFleche(new Fleche(mots[j][1], sf::Vector2f(std::stof(mots[j][2]), std::stof(mots[j][3])), std::stoi(mots[j][4]), std::stof(mots[j][5]), mots[j][6]));
					progression->ajouterClee(lignes[i]);
				}
				else if (role == "retirer_decor") {
					getScene(mots[j][0])->retirerDecor(mots[j][1]);
					progression->ajouterClee(lignes[i]);
				}
				else if (role == "retirer_inventaire") {
					inventaire->retirerRamassable(mots[j][0]);
				}
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

sf::Vector2f Scene::getPositionCurseur() {
	return positionCurseur;
}

float Scene::getAngleCurseur() {
	return angleCurseur;
}

std::string Scene::getCarte() {
	return carte;
}