#include "Inventaire.hpp"

void Inventaire::afficher(sf::RenderWindow* fenetre, sf::Vector2f position) {
	sprite.setPosition(position);
	fenetre->draw(sprite);
	piece.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
	fenetre->draw(piece);
	imageTexte.setPosition(sf::Vector2f(position.x+80, position.y+10));
	fenetre->draw(imageTexte);
	Ramassable* ramassable;	
	for (int i = 0; i < places; i++) {
		rectangle.setPosition(sf::Vector2f(position.x+10+ (tailleCases + 7) *(i%4), position.y+80+ (tailleCases + 7) *std::floor(i/4)));
		fenetre->draw(rectangle);
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

void Inventaire::setMonnaie(int _monnaie) {
	monnaie = _monnaie;
	imageTexte.setString(std::to_string(monnaie));
}

void Inventaire::ajouterMonnaie(int valeur) {
	monnaie += valeur;
	imageTexte.setString(std::to_string(monnaie));
}

bool Inventaire::acheter(int valeur) {
	if (valeur > monnaie) return false;
	monnaie -= valeur;
	imageTexte.setString(std::to_string(monnaie));
	return true;
}

int Inventaire::taillePlaces() {
	return ramassables.size();
}

std::string Inventaire::nomRamassable(int index) {
	return ramassables[index]->getNom();;
}