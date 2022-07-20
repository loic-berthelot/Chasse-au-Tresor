#include "General.hpp"

float norme(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

float distance(sf::Vector2f v1, sf::Vector2f v2) {
	return norme(sf::Vector2f(v1.x - v2.x, v1.y - v2.y));
}
float distance(sf::Vector2f v1, sf::Vector2i v2) {
	return norme(sf::Vector2f(v1.x - v2.x, v1.y - v2.y));
}

bool pointDansRectangle(sf::Vector2f point, sf::FloatRect rectangle) {
	if (point.x < rectangle.left or point.y < rectangle.top) return false;
	return point.x < rectangle.left + rectangle.width and point.y < rectangle.top + rectangle.height;
}

void progressionEtatsClic(int& etat, bool clic, bool touche) {
	if (etat == 0) {
		if (touche and not clic) etat = 1;
	}
	else if (etat == 1) {
		if (touche) {
			if (clic) etat = 2;
		} else etat = 0;
	}
	else if (etat == 2) {
		if (touche) {
			if (not clic) etat = 3;
		} else etat = 0;
	}
	else if (etat == 3) {
		if (touche) etat = 1;
		else etat = 0;
	}
}