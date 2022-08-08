#pragma once
#include "Progression.hpp"
#include <fstream>

extern Progression* progression;
extern std::vector<Scene*> scenes;

float norme(sf::Vector2f v);
float distance(sf::Vector2f v1, sf::Vector2f v2);
float distance(sf::Vector2f v1, sf::Vector2i v2);

bool pointDansRectangle(sf::Vector2f point, sf::FloatRect rectangle);

void progressionEtatsClic(int& etat, bool clic, bool touche);
