#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Scene;
class Quete;

class Progression {
	std::vector<std::string> variables;
	std::vector<std::string> valeurs;
	std::vector<std::string> clees;
public:
	Progression() {
	}
	void setValeur(std::string variable, std::string valeur);
	std::string getValeur(std::string variable);
	void ajouterClee(std::string clee);
	bool contientClee(std::string clee);
	int tailleClees();
	std::string nomClee(int index);
};
