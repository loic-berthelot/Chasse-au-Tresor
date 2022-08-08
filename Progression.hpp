#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


class Scene;

class Progression {
	std::vector<std::string> variables;
	std::vector<std::string> valeurs;
	std::vector<std::string> clees;
	std::vector<bool> utilisees;
	bool nouveautes;
public:
	Progression() {
		nouveautes = false;
	}
	void setValeur(std::string variable, std::string valeur);
	std::string getValeur(std::string variable);
	void activerClee(std::string clee);
	void utiliserClee(std::string clee);
	bool cleeActive(std::string clee);
	bool comporteNouveautes();
	void setNouveautes(bool n);
};
