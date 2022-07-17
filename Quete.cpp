#include "Quete.hpp"


void Quete::ajouterBouton(Bouton* bouton) {
	boutons.push_back(bouton);
}

void Quete::afficher(sf::RenderWindow * fenetre) {
	fenetre->draw(sprite);
	for (int i = 0; i < boutons.size(); i++) {
		boutons[i]->afficher(fenetre, position);
	}
}

void Quete::interactionSouris(sf::Vector2i souris, bool clic) {
	for (int i = 0; i < boutons.size(); i++) {
		boutons[i]->interactionSouris(souris, clic);
	}
}