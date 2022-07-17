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