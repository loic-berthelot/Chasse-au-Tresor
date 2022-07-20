#include "Inventaire.hpp"

void Inventaire::afficher(sf::RenderWindow* fenetre, sf::Vector2f position) {
	sprite.setPosition(position);
	fenetre->draw(sprite);
	imageTexte.setPosition(sf::Vector2f(position.x+80, position.y+10));
	fenetre->draw(imageTexte);
	for (int i = 0; i < places; i++) {
		rectangle.setPosition(sf::Vector2f(position.x+10+ (tailleCases + 7) *(i%4), position.y+80+ (tailleCases + 7) *std::floor(i/4)));
		fenetre->draw(rectangle);
		Ramassable* ramassable;
		if (i < ramassables.size()) {
			ramassable = ramassables[i];
			ramassable->setPosition(sf::Vector2f(position.x + 10 + tailleCases/2 + (tailleCases+7) * (i % 4), position.y + 80 + tailleCases / 2 +(tailleCases + 7) * std::floor(i / 4)));
			fenetre->draw(ramassable->retournerSprite());
		}
	}
}

void Inventaire::ajouterRamassable(Ramassable* ramassable) {
	ramassable->formaterCase(tailleCases);
	ramassables.push_back(ramassable);
}

void Inventaire::retirerRamassable(std::string nom) {
	for (int i = 0; i < ramassables.size(); i++) {
		if (ramassables[i]->getNom() == nom) ramassables.erase(ramassables.begin() + i);
	}
}

bool Inventaire::contient(std::string nom) {
	for (int i = 0; i < ramassables.size(); i++) {
		if (ramassables[i]->getNom() == nom) return true;
	}
	return false;
}

int Inventaire::getMonnaie() {
	return monnaie;
}

void Inventaire::ajouterMonnaie(int valeur) {
	monnaie += valeur;
}

bool Inventaire::acheter(int valeur) {
	if (valeur > monnaie) return false;
	monnaie -= valeur;
	return true;
}