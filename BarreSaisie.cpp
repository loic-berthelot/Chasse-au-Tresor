#include "BarreSaisie.hpp"

void BarreSaisie::reagirEntree(sf::Event* evenement){
	if (not selectionne) return;
	if (evenement == nullptr) return;
	std::string _texte = getTexte();
	if (evenement->text.unicode == 8) changerTexte(texte.substr(0, _texte.length() - 1));
	else if (sprite.getGlobalBounds().width-imageTexte.getGlobalBounds().width>20) changerTexte(_texte + static_cast<char>(evenement->text.unicode));
}

void BarreSaisie::selectionner(bool selection) {
	selectionne = selection;
	if (selection) sprite.setOutlineThickness(2);
	else sprite.setOutlineThickness(0);
}

bool BarreSaisie::interactionSouris(sf::Vector2i souris, bool clic) {
	if (pointDansRectangle(sf::Vector2f(souris.x, souris.y), sprite.getGlobalBounds())) sprite.setScale(1.02, 1);
	else sprite.setScale(1, 1);
	progressionEtatsClic(etatClic, clic, pointDansRectangle(sf::Vector2f(souris.x, souris.y), sprite.getGlobalBounds()));
	return (etatClic == 3);
}

void BarreSaisie::afficher(sf::RenderWindow* fenetre, sf::Vector2f position) {
	sprite.setPosition(sf::Vector2f(positionRelative.x + position.x, positionRelative.y + position.y));
	fenetre->draw(sprite);
	sf::FloatRect dimensionsSprite = sprite.getGlobalBounds();
	sf::FloatRect dimensionsTexte = imageTexte.getGlobalBounds();
	imageTexte.setPosition(sf::Vector2f(dimensionsSprite.left + (dimensionsSprite.width - dimensionsTexte.width) / 2, dimensionsSprite.top + 10));
	fenetre->draw(imageTexte);
}