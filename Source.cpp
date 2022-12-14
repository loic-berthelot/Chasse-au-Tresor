#include <SFML/Audio.hpp>
#include "Scene.hpp"
#include "Fleche.hpp"
#include "Ramassable.hpp"
#include "Inventaire.hpp"
#include "Decor.hpp"
#include "Quete.hpp"
#include "Carte.hpp"
#include "PanneauErreur.hpp"
#include <filesystem>
#include "arrivee.hpp"

int largeurFenetre, hauteurFenetre;
sf::RenderWindow fenetre;
sf::Image image;
sf::Sprite sprite;
sf::Texture texture;
Scene* scene = nullptr;
sf::Vector2f echelle;
Inventaire* inventaire;
bool toucheEchapPressee = false;
bool pleinEcran = true;
bool parametresOuverts = false;
int largeurInventaire;
Progression* progression;
std::vector<Scene*> scenes;
std::vector<Quete*> quetes;
sf::Music musique;
Bouton* boutonNouvellePartie;
Bouton* boutonChargerPartie;
Bouton* boutonCredits;
Bouton* boutonAide;
Bouton* boutonQuitter;
Bouton* boutonRetourMenu;
Bouton* boutonJeuParametres;
Bouton* boutonPleinEcran;
Bouton* boutonSon;
Bouton* boutonSauvegarder;
Bouton* boutonJeuQuitter;
int clicFenetre;
Carte* carte;
std::string modeJeu;
sf::Text texte;
sf::Font police;
std::string numeroVersion = "0.2";
std::string erreurType, erreurFichier;
int erreurLigne;
PanneauErreur* panneauErreur;
sf::RectangleShape fondParametres;
sf::Event evenement;
sf::Event* evenementTexte;
bool visualisationErreurs = true;
sf::Vector2i souris;
bool clic;
Arrivee* arrivee;
int descentePanneauArrivee = 0;
bool victoire = false;
std::string nomDepart = "depart";

void chargerScene(Scene* _scene) {
	if (_scene != scene) {
		scene = _scene;
		if(not image.loadFromFile("ressources/images/scenes/" + scene->getNom() + ".jpg")) {
			image.loadFromFile("ressources/images/scenes/" + scene->getNom() + ".png");
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sf::Vector2f taille = sf::Vector2f(texture.getSize().x, texture.getSize().y);
		echelle = sf::Vector2f((largeurFenetre-largeurInventaire)/taille.x, hauteurFenetre/taille.y);
		scene->setEchelle(echelle);
		sprite.setScale(echelle.x, echelle.y);
		
		if (scene->getMusique() == "stop") musique.stop();
		else if (scene->getMusique() != "" and musique.getStatus() != sf::Music::Playing) {
			if(musique.openFromFile("ressources/sons/" + scene->getMusique())) musique.play();		
		}
		if (scene->getCarte() != "") {
			carte->changerCarte(scene->getCarte());			
			carte->changerCurseur(scene->getPositionCurseur(), scene->getAngleCurseur());
		}
		if (scene->estArrivee()) {
			victoire = true;
		}
	}
}

void initialisation() {
	std::vector<std::string> lignes = lireFichier("ressources/parametres.txt");
	for (int i = 0; i < lignes.size(); i++) {
		std::vector<std::vector<std::string>> mots = lireLigne(lignes[i]);
		if (mots[0][0] == "depart") nomDepart = mots[1][0];
		else if (mots[0][0] == "police") police.loadFromFile("ressources/polices/"+mots[1][0]+".ttf");
	}

	musique.setLoop(true);
	progression = new Progression();
	largeurInventaire = 250;
	largeurFenetre = sf::VideoMode::getDesktopMode().width;// -100;
	hauteurFenetre = sf::VideoMode::getDesktopMode().height;// -100;
	fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Tr?sor", sf::Style::Fullscreen);
	inventaire = new Inventaire(sf::Vector2f(largeurInventaire, hauteurFenetre));
	texte.setFont(police);
	
	boutonNouvellePartie = new Bouton("menu_nouvelle_partie", "menu_nouvelle_partie", sf::Vector2f(0, 0));
	boutonChargerPartie = new Bouton("menu_charger_partie", "menu_charger_partie", sf::Vector2f(0, 0));
	boutonCredits = new Bouton("menu_credits", "menu_credits", sf::Vector2f(0, 0));
	boutonAide = new Bouton("menu_aide", "menu_aide", sf::Vector2f(0, 0));
	boutonQuitter = new Bouton("menu_quitter", "menu_quitter", sf::Vector2f(0, 0));
	boutonRetourMenu = new Bouton("retour_menu", "retour_menu", sf::Vector2f(0, 0));
	boutonJeuParametres = new Bouton("jeuParametres", "parametres", sf::Vector2f(35, 35));
	boutonPleinEcran = new Bouton("plein_ecran", "boutonJeu", sf::Vector2f(85, 150), "Plein Ecran");
	boutonSon = new Bouton("son", "boutonJeu", sf::Vector2f(85, 210), "Son : On");
	boutonSauvegarder = new Bouton("sauvegarder", "boutonJeu", sf::Vector2f(85, 270), "Sauvegarder");
	boutonJeuQuitter = new Bouton("jeuQuitter", "boutonJeu", sf::Vector2f(85, 330), "Quitter");
	fondParametres.setFillColor(sf::Color(100, 100, 100));
	fondParametres.setSize(sf::Vector2f(200, 400));
	carte = new Carte();
	clicFenetre = 0;
	modeJeu = "menu";
	erreurType = "";
	panneauErreur = new PanneauErreur(sf::Vector2f(largeurFenetre/2 - 250, hauteurFenetre / 2 - 100));
	arrivee = new Arrivee();
}

void preparerScenes(bool remplir) {
	std::string nom;
	for (const auto& file : std::filesystem::directory_iterator("./ressources/scenes")) {
		nom = file.path().string();
		nom = nom.substr(20, nom.size() - 24);
		new Scene(nom, remplir);
	}
	for (const auto& file : std::filesystem::directory_iterator("./ressources/quetes")) {
		nom = file.path().string();
		nom = nom.substr(20, nom.size() - 24);
		new Quete(nom);
	}
}

void sauvegarder(std::string fichier) {
	std::ofstream flux("sauvegardes/"+fichier+".txt");
	flux << inventaire->getMonnaie() << std::endl;
	flux << inventaire->taillePlaces() << std::endl;
	for (int i = 0; i < inventaire->taillePlaces(); i++) flux << inventaire->nomRamassable(i) << std::endl;
	flux << scene->getNom() << std::endl;
	flux<< scenes.size()<<std::endl;
	for (int i = 0; i < scenes.size(); i++) {
		flux << scenes[i]->tailleFleches()+ scenes[i]->tailleRamassables() + scenes[i]->tailleDecors() << std::endl;
		for (int j = 0; j < scenes[i]->tailleFleches(); j++) flux << scenes[i]->getDescription("fleche", j)<<std::endl;
		for (int j = 0; j < scenes[i]->tailleRamassables(); j++) flux << scenes[i]->getDescription("ramassable", j) << std::endl;
		for (int j = 0; j < scenes[i]->tailleDecors(); j++) flux << scenes[i]->getDescription("decor", j) << std::endl;
	}
	flux << progression->nombreVariables() << std::endl;
	for (int i = 0; i < progression->nombreVariables(); i++) flux << progression->getVariable(i) << "\n" << progression->getValeur(i) << "\n";
}

void chargerSauvegarde(std::string fichier) {
	int indexLigne, x, y;
	std::vector<std::string> lignes = lireFichier("sauvegardes/" + fichier + ".txt");
	inventaire->setMonnaie(std::stoi(lignes[0]));
	indexLigne = 1;
	x = std::stoi(lignes[indexLigne]);	
	while (x > 0) {
		indexLigne++;
		inventaire->ajouterRamassable(new Ramassable(lignes[indexLigne]));
		x--;
	}
	indexLigne++;
	chargerScene(getScene(lignes[indexLigne]));
	indexLigne++;
	x = std::stoi(lignes[indexLigne]);
	while (x > 0) {
		indexLigne++;
		y = std::stoi(lignes[indexLigne]);
		while (y > 0) {
			indexLigne++;
			executerLigne(lignes[indexLigne]);
			y--;
		}
		x--;
	}
	indexLigne++;
	x = std::stoi(lignes[indexLigne]);
	while (x > 0) {
		progression->setValeur(lignes[indexLigne+1], lignes[indexLigne+2]);
		indexLigne+=2;
		x--;
	}
}

bool executerFrame() {
	if (modeJeu == "menu") {
		fenetre.clear(sf::Color(150, 50, 0));
		boutonNouvellePartie->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 - 300));
		boutonChargerPartie->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 - 150));
		boutonCredits->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2));
		boutonAide->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 + 150));
		boutonQuitter->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 + 300));
		if (boutonNouvellePartie->interactionSouris(souris, clic)) {
			preparerScenes(true);
			chargerScene(getScene(nomDepart));
			modeJeu = "jeu";
		}
		if (boutonChargerPartie->interactionSouris(souris, clic)) {
			preparerScenes(false);
			chargerScene(getScene("depart"));
			chargerSauvegarde("sauvegarde1");
			modeJeu = "jeu";
		}
		if (boutonCredits->interactionSouris(souris, clic)) {
			modeJeu = "credits";
		}
		if (boutonAide->interactionSouris(souris, clic)) {
			modeJeu = "aide";
		}
		if (boutonQuitter->interactionSouris(souris, clic)) {
			fenetre.close();
			return false;
		}
		texte.setFillColor(sf::Color::White);
		texte.setPosition(sf::Vector2f(10, hauteurFenetre - 35));
		texte.setCharacterSize(20);
		texte.setString("Version : " + numeroVersion);
		fenetre.draw(texte);
	}
	else if (modeJeu == "credits" or modeJeu == "aide") {
		fenetre.clear(sf::Color(150, 50, 0));
		boutonRetourMenu->afficher(&fenetre, sf::Vector2f(50, 50));
		if (boutonRetourMenu->interactionSouris(souris, clic)) modeJeu = "menu";
		texte.setFillColor(sf::Color::White);
		texte.setPosition(sf::Vector2f(80, 80));
		texte.setCharacterSize(35);
		if (modeJeu == "credits") {
			texte.setString("Code : Lo?c Berthelot");
			fenetre.draw(texte);
			texte.setCharacterSize(28);
			texte.setPosition(sf::Vector2f(80, 180));
			std::string contenuTexte = "";
			std::vector<std::string> lignes = lireFichier("ressources/credits.txt");
			for (int i = 0; i < lignes.size(); i++) contenuTexte += lignes[i] + "\n";
			texte.setString(contenuTexte);
			fenetre.draw(texte);
		}
		else {
			texte.setString("Les instructions pour creer le jeu se trouvent dans le fichier lisez-moi.odt \ndans le dossier ressources.");
			fenetre.draw(texte);
		}
	}
	else if (modeJeu == "jeu") {
		fenetre.clear();
		fenetre.draw(sprite);
		Scene* _scene = scene->interactionContenu(souris, clic, inventaire, evenementTexte);
		chargerScene(_scene);
		scene->afficherContenu(&fenetre, echelle);
		inventaire->afficher(&fenetre, sf::Vector2f(largeurFenetre - largeurInventaire, 0));
		if (boutonJeuParametres->interactionSouris(souris, clic)) parametresOuverts = not parametresOuverts;
		if (parametresOuverts) {
			fenetre.draw(fondParametres);
			boutonPleinEcran->afficher(&fenetre, sf::Vector2f(0, 0));
			boutonSon->afficher(&fenetre, sf::Vector2f(0, 0));
			boutonSauvegarder->afficher(&fenetre, sf::Vector2f(0, 0));
			boutonJeuQuitter->afficher(&fenetre, sf::Vector2f(0, 0));
			if (boutonPleinEcran->interactionSouris(souris, clic)) {
				if (pleinEcran) fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Tr?sor");
				else fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Tr?sor", sf::Style::Fullscreen);
				pleinEcran = not pleinEcran;
			}
			if (boutonSon->interactionSouris(souris, clic)) {
				if (boutonSon->getTexte() == "Son : On") {
					boutonSon->changerTexte("Son : Off");
					musique.setVolume(0);
				}
				else {
					boutonSon->changerTexte("Son : On");
					musique.setVolume(100);
				}
			}
			if (boutonSauvegarder->interactionSouris(souris, clic)) {
				sauvegarder("sauvegarde1");
			}
			if (boutonJeuQuitter->interactionSouris(souris, clic)) {
				fenetre.close();
				return false;
			}
		}
		boutonJeuParametres->afficher(&fenetre, sf::Vector2f(0, 0));
		carte->afficher(&fenetre);
		if (victoire) {
			if (descentePanneauArrivee < hauteurFenetre/2) descentePanneauArrivee += 8;
			arrivee->deplacer(sf::Vector2f(largeurFenetre/2-largeurInventaire/2, descentePanneauArrivee));
			arrivee->afficher(&fenetre);
		}
	}
	panneauErreur->afficher(&fenetre);
	return true;	
}

int main() { 
	initialisation();
	fenetre.setPosition(sf::Vector2i(0, 0));
	fenetre.setFramerateLimit(60);
	while (true) {
		evenementTexte = nullptr;
		while (fenetre.pollEvent(evenement)) {
			if (evenement.type == sf::Event::Closed) {
				fenetre.close();
				return 0;
			}
			if (evenement.type == sf::Event::KeyPressed) {
				if (evenement.key.code == sf::Keyboard::Escape) {
					if (not toucheEchapPressee) {
						toucheEchapPressee = true;
						if (pleinEcran) fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Tr?sor");
						else fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Tr?sor", sf::Style::Fullscreen);
						pleinEcran = not pleinEcran;
					}
				}
				else if (evenement.key.code == sf::Keyboard::X) {
					panneauErreur->fermer();
				}
			}
			if (evenement.type == sf::Event::KeyReleased) {
				if (evenement.key.code == sf::Keyboard::Escape) toucheEchapPressee = false;
			}
			if (evenement.type == sf::Event::TextEntered) evenementTexte = &evenement;
		}
		souris = sf::Mouse::getPosition(fenetre);
		clic = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		progressionEtatsClic(clicFenetre, clic, true);
		if (visualisationErreurs) {
			try {
				if (not executerFrame()) return 0;
			}
			catch (std::exception e) {
				panneauErreur->changerTexte((std::string)e.what() + "\n" + erreurFichier + "\nLigne : " + std::to_string(erreurLigne + 1) + "\n\n\nFermer : touche X ");
			}
		}
		else executerFrame();
		fenetre.display();
	}
	return 0;
}