#include "Progression.hpp"
#include <iostream>

void Progression::setValeur(std::string variable, std::string valeur) {
	for (int i = 0; i < variables.size(); i++) {
		if (variable == variables[i]) {
			valeurs[i] = valeur;
			return;
		}
	}
	variables.push_back(variable);
	valeurs.push_back(valeur);
}

std::string Progression::getValeur(std::string variable) {
	for (int i = 0; i < variables.size(); i++) {
		if (variable == variables[i]) return valeurs[i];
	}
	return "";
}

void Progression::activerClee(std::string clee) {
	clees.push_back(clee);
	utilisees.push_back(false);
	nouveautes = true;
}

void Progression::utiliserClee(std::string clee) {
	for (int i = 0; i < clees.size(); i++) {
		if (clee == clees[i]) utilisees[i] = true;
	}
}

bool Progression::cleeActive(std::string clee) {
	for (int i = 0; i < clees.size(); i++) {
		if (clee == clees[i]) return true;
	}
	return false;
}

bool Progression::comporteNouveautes() {
	return nouveautes;
}

void Progression::setNouveautes(bool n) {
	nouveautes = n;
}