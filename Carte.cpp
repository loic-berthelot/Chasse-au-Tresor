#include "Carte.hpp"

void Carte::changerCarte(std::string _nom) {
	nom = _nom;
	sf::Image image;
	image.loadFromFile("ressources/images/cartes/" + nom);
	textureSprite.loadFromImage(image);
	sprite.setTexture(textureSprite);
	sf::FloatRect tailleOriginale = sprite.getLocalBounds();
	sf::Vector2f echelle = sf::Vector2f(taille.x / tailleOriginale.width, taille.y / tailleOriginale.height);
	sprite.setScale(echelle.x, echelle.y);
}

void Carte::changerCurseur(sf::Vector2f _position, float _angle) {
	positionCurseur = sf::Vector2f(_position.x, 1-_position.y);
	angleCurseur = _angle;
}

void Carte::afficher(sf::RenderWindow* fenetre) {
	if (nom != "") {
		fenetre->draw(sprite);
		curseur.setPosition(sf::Vector2f(positionSprite.x+positionCurseur.x*taille.x, positionSprite.y+positionCurseur.y*taille.y));
		curseur.setRotation(angleCurseur);
		fenetre->draw(curseur);
	}
}