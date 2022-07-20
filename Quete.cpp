#include "Quete.hpp"


void Quete::ajouterBouton(Bouton* bouton) {
	boutons.push_back(bouton);
}

void Quete::afficher(sf::RenderWindow * fenetre) {
	fenetre->draw(sprite);
	fenetre->draw(imageTexte);
	for (int i = 0; i < boutons.size(); i++) {
		boutons[i]->afficher(fenetre, position);
	}
}

std::string Quete::interactionSouris(sf::Vector2i souris, bool clic) {
	Bouton* bouton;
	for (int i = 0; i < boutons.size(); i++) {
		bouton = boutons[i];
		if (bouton->interactionSouris(souris, clic)) return bouton->getNom();
	}
	return "";
}