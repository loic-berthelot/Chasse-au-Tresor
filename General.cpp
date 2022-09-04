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

std::vector<std::string> lireFichier(std::string adresse) {
	std::ifstream flux(adresse);
	std::string ligne;
	std::vector<std::string> lignes;
	if (flux) {
		while (std::getline(flux, ligne)) lignes.push_back(ligne);
	}
	return lignes;
}

std::vector<std::vector<std::string>> lireLigne(std::string ligne) {
	std::string mot;
	std::vector<std::string> bloc;
	std::vector<std::vector<std::string>> mots;
	bool guillemets = false;
	ligne += ':';
	for (int i = 0; i < ligne.length(); i++) {
		if ((ligne[i] == ':' or ligne[i] == ',') and not guillemets) {
			while (mot[mot.length() - 1] == ' ' and mot.length() > 0) mot = mot.substr(0, mot.length() - 1);
			bloc.push_back(mot);
			if (ligne[i] == ':') {
				mots.push_back(bloc);
				bloc.clear();
			}
			mot = "";
		}
		else if (ligne[i] == '"') guillemets = not guillemets;
		else if (ligne[i] != ' ' or mot.length() > 0) mot += ligne[i];
	}
	return mots;
}

std::string modifierChaine(std::string chaine, std::string motif_a, std::string motif_b) {
	std::string chaine2 = "";
	bool trouve;
	for (int i = 0; i < chaine.size(); i++) {
		trouve = true;
		for (int j = 0; j < motif_a.size(); j++) {
			if (i + j >= chaine.size()) {
				trouve = false;
				break;
			}
			if (chaine[i + j] != motif_a[j]) {
				trouve = false;
				break;
			}
		}
		if (trouve) {
			i += motif_a.size() - 1;
			chaine2 += motif_b;
		}
		else chaine2 += chaine[i];
	}
	return chaine2;
}