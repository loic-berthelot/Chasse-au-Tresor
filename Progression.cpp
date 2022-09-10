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

std::string Progression::getVariable(int indice) {
	return variables[indice];
}

std::string Progression::getValeur(int indice) {
	return valeurs[indice];
}

std::string Progression::getValeur(std::string variable) {
	for (int i = 0; i < variables.size(); i++) {
		if (variable == variables[i]) return valeurs[i];
	}
	return "";
}

int Progression::nombreVariables() {
	return variables.size();
}