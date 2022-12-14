#include "Objet.hpp"

extern int largeurFenetre;
extern int hauteurFenetre;
extern int largeurInventaire;

sf::Sprite Objet::getSprite() { return sprite; }

void Objet::creerSprite(std::string adresse) {
	sf::Image image;
	image.loadFromFile(adresse);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sf::FloatRect taille = sprite.getGlobalBounds();
	rayon = std::max(taille.width, taille.height) / 2 * coefTaille;
	sprite.setOrigin(taille.width/2, taille.height/2);
}

void Objet::adapterEchelle(sf::Vector2f echelle) {
	sprite.setPosition(sf::Vector2f(position.x * echelle.x, position.y * echelle.y));
}

bool Objet::interactionSouris(sf::Vector2i souris, bool clic) {
	if (pointDansRectangle(sf::Vector2f(souris.x, souris.y), sprite.getGlobalBounds())) sprite.setScale(1.05 * proportions.x * coefTaille, 1.05 * proportions.y * coefTaille);
	else sprite.setScale(proportions.x * coefTaille, proportions.y * coefTaille);
	progressionEtatsClic(etatClic, clic, distance(sprite.getPosition(), souris) < rayon);
	return etatClic == 3;
}

void Objet::setCoefTaille(float _coefTaille) {
	coefTaille = _coefTaille;
}

void Objet::setPosition(sf::Vector2f _position) {
	sprite.setPosition(_position);
}

void Objet::afficher(sf::RenderWindow* fenetre) {
	sprite.setPosition(sf::Vector2f(position.x * (largeurFenetre-largeurInventaire), (1-position.y) * hauteurFenetre));
	fenetre->draw(sprite);
}

std::string Objet::getNom() {
	return nom;
}

sf::Vector2f Objet::getPosition() {
	return position;
}

sf::Sprite Objet::retournerSprite() {
	return sprite;
}

void Objet::redimensionner(sf::Vector2f _proportions) {
	proportions = _proportions;
	sprite.setScale(sf::Vector2f(proportions.x * coefTaille, proportions.y * coefTaille));
}