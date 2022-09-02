#include "Scene.hpp"

extern std::vector<Scene*> scenes;
extern Inventaire* inventaire;
extern Quete* quete = nullptr;

Scene* getScene(std::string nom) {
	for (int i = 0; i < scenes.size(); i++) {
		if (scenes[i]->getNom() == nom) return scenes[i];
	}
	return nullptr;
}

int calculerReference(std::vector<std::string> _lignes, int ligneActuelle, std::string deplacement) {
	if (deplacement[0] == '@') {
		std::vector<std::string> lignes = _lignes;
		for (int i = 0; i < lignes.size(); i++) {
			if (lireLigne(lignes[i])[0][0] == deplacement) return i;
		}
		return 0;
	}
	if (deplacement[0] == '+') return ligneActuelle + std::stoi(deplacement.substr(1, deplacement.size() - 1));
	if (deplacement[0] == '-') return ligneActuelle - std::stoi(deplacement.substr(1, deplacement.size() - 1));
	return std::stoi(deplacement) - 1;
}

bool verifierCondition(std::string ligne) {
	std::vector<std::vector<std::string>> mots = lireLigne(ligne);
	std::string role;
	if (mots[0][0][0] == '@') role = mots[0][1];
	else role = mots[0][0];
	if (role == "_ramassable") return inventaire->contient(mots[1][0]);
	if (role == "_saisie") return progression->getValeur(mots[1][0]) == mots[1][1];
	if (role == "_monnaie") return inventaire->getMonnaie() >= std::stoi(mots[1][0]);
}

void executerLigne(std::string ligne) {
	std::vector<std::vector<std::string>> mots;
	std::string role, nomScene;
	mots = lireLigne(ligne);
	if (mots.size() > 0) {
		nomScene = "";
		if (mots[0][0][0] == '@') {
			role = mots[0][1];
			if (mots[0].size() >= 3) nomScene = mots[0][2];
		}
		else {
			role = mots[0][0];
			if (mots[0].size() >= 2) nomScene = mots[0][1];
		}
		if (nomScene != "") getScene(nomScene)->executerLigne(ligne, true);
	}
}

void executerAlgorithme(std::vector<std::string> _lignes) {
	std::vector<std::string> lignes = _lignes;
	std::vector<std::vector<std::string>> mots;
	std::string role, nomScene;
	int i, i2;
	i = 0;
	while (0 <= i and i < lignes.size()) {
		mots = lireLigne(lignes[i]);
		i2 = i + 1;
		nomScene = "";
		if (mots[0][0][0] == '@') role = mots[0][1];
		else role = mots[0][0];
		if (role == "fermer_quete") {
			quete = nullptr;
		}
		else if (role == "si") {
			if (verifierCondition(lignes[calculerReference(_lignes, i, mots[1][0])])) i2 = calculerReference(_lignes, i, mots[2][0]);
			else i2 = calculerReference(_lignes, i, mots[3][0]);
		}
		else if (role == "si_non") {
			if (not verifierCondition(lignes[calculerReference(_lignes, i, mots[1][0])])) i2 = calculerReference(_lignes, i, mots[2][0]);
			else i2 = calculerReference(_lignes, i, mots[3][0]);
		}
		else if (role == "si_et") {
			bool condition = true;
			int k = 0;
			while (condition and k < mots[1].size()) {
				if (not verifierCondition(lignes[calculerReference(_lignes, i, mots[1][k])])) condition = false;
				k++;
			}
			if (condition) i2 = calculerReference(_lignes, i, mots[2][0]);
			else i2 = calculerReference(_lignes, i, mots[3][0]);
		}
		else if (role == "si_ou") {
			bool condition = false;
			int k = 0;
			while (not condition and k < mots[1].size()) {
				if (verifierCondition(lignes[calculerReference(_lignes, i, mots[1][k])])) condition = true;
				k++;
			}
			if (condition) i2 = calculerReference(_lignes, i, mots[2][0]);
			else i2 = calculerReference(_lignes, i, mots[3][0]);
		}
		else if (role == "executer") {
			executerAlgorithme(mots[1][0]);
		}
		else if (role == "aller") {
			i2 = std::stoi(mots[1][0]);
		}
		else executerLigne(lignes[i]);
		i = i2;
	}
}

void executerAlgorithme(std::string nom) {
	executerAlgorithme(lireFichier("ressources/algorithmes/" + nom + ".txt"));
}

void Scene::chargerFichier(std::string nom, bool remplir) {
	std::vector<std::string> lignes = lireFichier("ressources/scenes/" + nom + ".txt");
	for (int i = 0; i < lignes.size(); i++) {
		executerLigne(lignes[i], remplir);
	}
}

void Scene::executerLigne(std::string ligne, bool remplir) {
	musique = "";
	carte = "";
	std::vector<std::vector<std::string>> mots;
	std::string role;
	mots = lireLigne(ligne);
	if (mots[0][0][0] == '@') role = mots[0][1];
	else role = mots[0][0];
	if (remplir) {
		if (role == "fleche") {
			if (mots[1].size() < 5) ajouterFleche(new Fleche(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3]))));
			else if (mots[1].size() < 6) ajouterFleche(new Fleche(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3])), std::stoi(mots[1][4])));
			else ajouterFleche(new Fleche(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3])), std::stoi(mots[1][4]), stof(mots[1][5])));
		}
		else if (role == "ramassable" or role == "monnaie") {
			if (mots[1].size() < 2) ajouterRamassable(new Ramassable(mots[1][0]));
			else if (mots[1].size() < 4) ajouterRamassable(new Ramassable(mots[1][0], sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2]))));
			else if (mots[1].size() < 5) ajouterRamassable(new Ramassable(mots[1][0], sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2])), std::stof(mots[1][3])));
			else ajouterRamassable(new Ramassable(mots[1][0], sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2])), std::stof(mots[1][3]), std::stof(mots[1][4])));
		}
		else if (role == "decor") {
			if (mots[1].size() < 5) ajouterDecor(new Decor(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3]))));
			else if (mots[1].size() < 6) ajouterDecor(new Decor(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3])), std::stoi(mots[1][4])));
			else ajouterDecor(new Decor(mots[1][0], mots[1][1], sf::Vector2f(std::stof(mots[1][2]), std::stof(mots[1][3])), std::stoi(mots[1][4]), std::stof(mots[1][5])));
		}
	}
	if (role == "musique") {
		musique = mots[1][0];
	}
	else if (role == "carte") {
		carte = mots[1][0];
		positionCurseur = sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2]));
		angleCurseur = std::stof(mots[1][3]);
	}
	else if (role == "retirer_decor") {
		retirerDecor(mots[1][0]);
	}
	else if (role == "retirer_ramassable" or role == "retirer_monnaie") {
		if (mots[1].size() == 1) retirerRamassable(mots[0][1]);
		else retirerRamassable(mots[1][0], sf::Vector2f(std::stof(mots[1][1]), std::stof(mots[1][2])));
	}
	else if (role == "gagner_monnaie") {
		inventaire->ajouterMonnaie(std::stoi(mots[1][0]));
	}
	else if (role == "ajouter_inventaire") {
		inventaire->ajouterRamassable(new Ramassable(mots[1][0]));
	}
	else if (role == "retirer_inventaire") {
		std::cout<<"ok"<<std::endl;
		inventaire->retirerRamassable(mots[1][0]);
	}
}

void Scene::afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle) {
	for (int i = 0; i < fleches.size(); i++) fleches[i]->afficher(fenetre);
	for (int i = 0; i < ramassables.size(); i++) ramassables[i]->afficher(fenetre);
	for (int i = 0; i < decors.size(); i++)	decors[i]->afficher(fenetre);
	if (quete != nullptr) quete->afficher(fenetre);
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

void Scene::retirerRamassable(std::string nom, sf::Vector2f position) {
	for (int i = 0; i < ramassables.size(); i++) {
		if (ramassables[i]->getNom() == nom) {
			if (position.x == -1 or (position.x == ramassables[i]->getPosition().y and position.x == ramassables[i]->getPosition().y)) ramassables.erase(ramassables.begin() + i);
		}
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

int Scene::tailleFleches() {
	return fleches.size();
}

int Scene::tailleRamassables() {
	return ramassables.size();
}

int Scene::tailleDecors() {
	return decors.size();
}

std::string Scene::getDescription(std::string type, int indice) {
	if (type == "fleche") return fleches[indice]->getDescription();
	if (type == "ramassable") return ramassables[indice]->getDescription();
	if (type == "decor") return decors[indice]->getDescription();
}