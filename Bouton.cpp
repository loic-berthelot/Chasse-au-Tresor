#include "Bouton.hpp"

void Bouton::afficher(sf::RenderWindow* fenetre, sf::Vector2f _position, sf::Vector2f dimensionsCadre) {
	sf::FloatRect dimensionsSprite = sprite.getGlobalBounds();
	sf::Vector2f position(_position.x + positionRelative.x, _position.y + positionRelative.y);
	if (positionRelative.x < 0) position.x += dimensionsCadre.x;
	if (positionRelative.y < 0) position.y += dimensionsCadre.x;
	sprite.setPosition(position);
	dimensionsSprite = sprite.getGlobalBounds();
	fenetre->draw(sprite);
	sf::FloatRect dimensionsTexte = imageTexte.getGlobalBounds();
	imageTexte.setPosition(sf::Vector2f(dimensionsSprite.left+(dimensionsSprite.width-dimensionsTexte.width)/2, dimensionsSprite.top + (dimensionsSprite.height - 1.8*dimensionsTexte.height)/2));
	fenetre->draw(imageTexte);
}

bool Bouton::interactionSouris(sf::Vector2i souris, bool clic) {	
	if (pointDansRectangle(sf::Vector2f(souris.x, souris.y), sprite.getGlobalBounds())) sprite.setScale(1.05, 1.05);
	else sprite.setScale(1, 1);
	progressionEtatsClic(etatClic, clic, pointDansRectangle(sf::Vector2f(souris.x, souris.y), sprite.getGlobalBounds()));
	return (etatClic == 3);
}

std::string Bouton::getNom() {
	return nom;
}

std::string Bouton::getType() {
	return type;
}

std::string Bouton::getTexte() {
	return texte;
}

void Bouton::changerType(std::string _type) {
	type = _type;
	sf::Image image;
	image.loadFromFile("ressources/images/boutons/" + type + ".png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

void Bouton::changerTexte(std::string _texte) {
	texte = _texte;
	imageTexte.setString(texte);
}

void Bouton::selectionner(bool selection) {}
void Bouton::reagirEntree(sf::Event* evenement) {}