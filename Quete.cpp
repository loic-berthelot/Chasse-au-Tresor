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

std::string Quete::interactionSouris(sf::Vector2i souris, bool clic, sf::Event* evenementTexte) {
	Bouton* bouton;
	for (int i = 0; i < boutons.size(); i++) {
		bouton = boutons[i];
		bool boutonClique = bouton->interactionSouris(souris, clic);
		if (boutonClique) bouton->selectionner(true);
		else if (clic) bouton->selectionner(false);
		bouton->reagirEntree(evenementTexte);
		if (boutonClique) return bouton->getNom();
	}
	return "";
}

std::string Quete::getTexte(std::string _nom) {
	Bouton* bouton;
	for (int i = 0; i < boutons.size(); i++) {
		bouton = boutons[i];
		if (bouton->getNom() == _nom) return bouton->getTexte();
	}
	return "";
}
