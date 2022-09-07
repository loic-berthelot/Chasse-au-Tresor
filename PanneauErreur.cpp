#pragma once
#include "PanneauErreur.hpp"

void PanneauErreur::changerTexte(std::string _texte) {
	texte = _texte;
	imageTexte.setString(texte);
}

void PanneauErreur::afficher(sf::RenderWindow * fenetre) {
	if (texte != "") {
		fenetre->draw(rectangle);
		fenetre->draw(imageTexte);
	}
}

void PanneauErreur::fermer() {
	texte = "";
}