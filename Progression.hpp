#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Scene;
class Quete;

class Progression {
	std::vector<std::string> variables;
	std::vector<std::string> valeurs;
public:
	Progression() {
	}
	void setValeur(std::string variable, std::string valeur);
	std::string getVariable(int indice);
	std::string getValeur(int indice);
	std::string getValeur(std::string variable);
	int nombreVariables();
};
