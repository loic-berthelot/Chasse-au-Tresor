#pragma once
#include "Progression.hpp"
#include <fstream>

extern Progression* progression;
extern std::vector<Scene*> scenes;
extern std::vector<Quete*> quetes;
extern std::string numeroVersion;
extern sf::Font police;
extern std::string erreurFichier;
extern int erreurLigne;

float norme(sf::Vector2f v);
float distance(sf::Vector2f v1, sf::Vector2f v2);
float distance(sf::Vector2f v1, sf::Vector2i v2);

bool pointDansRectangle(sf::Vector2f point, sf::FloatRect rectangle);

void progressionEtatsClic(int& etat, bool clic, bool touche);

std::string modifierChaine(std::string chaine, std::string motif_a, std::string motif_b);

std::vector<std::string> lireFichier(std::string adresse);
std::vector<std::vector<std::string>> lireLigne(std::string ligne);