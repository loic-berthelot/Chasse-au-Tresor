#include "Inventaire.hpp"

void Inventaire::afficher(sf::RenderWindow* fenetre, sf::Vector2f position) {
	sprite.setPosition(position);
	fenetre->draw(sprite);
	for (int i = 0; i < 80; i++) {
		rectangle.setPosition(sf::Vector2f(position.x+10+ (tailleCases + 7) *(i%4), position.y+10+ (tailleCases + 7) *std::floor(i/4)));
		fenetre->draw(rectangle);
		Ramassable* ramassable;
		if (i < ramassables.size()) {
			ramassable = ramassables[i];
			ramassable->setPosition(sf::Vector2f(position.x + 10 + tailleCases/2 + (tailleCases+7) * (i % 4), position.y + 10 + tailleCases / 2 +(tailleCases + 7) * std::floor(i / 4)));
			fenetre->draw(ramassable->retournerSprite());
		}
	}
}

void Inventaire::ajouterRamassable(Ramassable* ramassable) {
	ramassable->formaterCase(tailleCases);
	ramassables.push_back(ramassable);
}

void Inventaire::retirerRamassable(Ramassable* ramassable) {
	for (int i = 0; i < ramassables.size(); i++) {
		if (ramassables[i] == ramassable) ramassables.erase(ramassables.begin() + i);
	}
}