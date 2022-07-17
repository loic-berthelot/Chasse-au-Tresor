#include "Scene.hpp"
#include <iostream>

void Scene::afficherContenu(sf::RenderWindow* fenetre, sf::Vector2f echelle) {
	for (int i = 0; i < fleches.size(); i++) {
		fleches[i]->adapterEchelle(echelle);
		fenetre->draw(fleches[i]->getSprite());
	}
	for (int i = 0; i < ramassables.size(); i++) {
		ramassables[i]->adapterEchelle(echelle);
		fenetre->draw(ramassables[i]->getSprite());
	}
	for (int i = 0; i < decors.size(); i++) {
		decors[i]->adapterEchelle(echelle);
		fenetre->draw(decors[i]->getSprite());
	}
	if (quete != nullptr) quete->afficher(fenetre);
}

Scene* Scene::interactionContenu(sf::Vector2i souris, bool clic, Inventaire* inventaire) {
	if (quete != nullptr) quete->interactionSouris(souris, clic);
	Decor* decor;
	Quete* _quete;
	for (int i = 0; i < decors.size(); i++) {
		decor = decors[i];
		_quete = decor->interactionSouris(souris, clic);
		if (_quete != nullptr) {
			quete = _quete;
		}
	}
	Ramassable* ramassable;
	for (int i = 0; i < ramassables.size(); i++) {
		ramassable = ramassables[i];
		if (ramassable->interactionSouris(souris, clic)) {
			retirerRamassable(ramassable);
			inventaire->ajouterRamassable(ramassable);
		}
	}
	Scene* suivant;
	for (int i = 0; i < fleches.size(); i++) {
		suivant = fleches[i]->interactionSouris(souris, clic);
		if (suivant != nullptr) return suivant;
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

void Scene::ajouterQuete(Quete* _quete) {
	quete = _quete;
}