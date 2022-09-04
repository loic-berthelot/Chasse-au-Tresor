#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scene.hpp"
#include "Fleche.hpp"
#include "Ramassable.hpp"
#include "Inventaire.hpp"
#include "Decor.hpp"
#include "Quete.hpp"
#include "Carte.hpp"
#include <filesystem>

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
Bouton* boutonSon;
Bouton* boutonNouvellePartie;
Bouton* boutonChargerPartie;
Bouton* boutonCredits;
Bouton* boutonAide;
Bouton* boutonQuitter;
Bouton* boutonRetourMenu;
int clicFenetre;
Carte* carte;
std::string modeJeu;
sf::Text texte;
sf::Font police;
std::string numeroVersion = "0.1";


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
		sprite.setScale(echelle.x, echelle.y);
		
		if (scene->getMusique() == "stop") musique.stop();
		else if (scene->getMusique() != "") {/// and musique.getStatus() == sf::Music::Playing) {
			std::cout << scene->getMusique();
			if(musique.openFromFile("ressources/sons/" + scene->getMusique())) musique.play();		
		}
		if (scene->getCarte() != "") {
			carte->changerCarte(scene->getCarte());			
			carte->changerCurseur(scene->getPositionCurseur(), scene->getAngleCurseur());
		}
	}
}

void initialisation() {
	musique.setLoop(true);
	progression = new Progression();
	largeurInventaire = 250;
	largeurFenetre = sf::VideoMode::getDesktopMode().width;
	hauteurFenetre = sf::VideoMode::getDesktopMode().height;
	fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor", sf::Style::Fullscreen);
	inventaire = new Inventaire(sf::Vector2f(largeurInventaire, hauteurFenetre));
	police.loadFromFile("ressources/polices/arial_narrow_7.ttf");
	texte.setFont(police);

	boutonSon = new Bouton("son", "sonOn", sf::Vector2f(30, 30));
	boutonNouvellePartie = new Bouton("menu_nouvelle_partie", "menu_nouvelle_partie", sf::Vector2f(0, 0));
	boutonChargerPartie = new Bouton("menu_charger_partie", "menu_charger_partie", sf::Vector2f(0, 0));
	boutonCredits = new Bouton("menu_credits", "menu_credits", sf::Vector2f(0, 0));
	boutonAide = new Bouton("menu_aide", "menu_aide", sf::Vector2f(0, 0));
	boutonQuitter = new Bouton("menu_quitter", "menu_quitter", sf::Vector2f(0, 0));
	boutonRetourMenu = new Bouton("retour_menu", "retour_menu", sf::Vector2f(0, 0));

	carte = new Carte();
	clicFenetre = 0;
	modeJeu = "menu";
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
}

int main() { 
	initialisation();
	fenetre.setPosition(sf::Vector2i(0, 0));
	fenetre.setFramerateLimit(60);
	sf::Event evenement;
	sf::Event* evenementTexte;
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
						if (pleinEcran) fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor");
						else fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor", sf::Style::Fullscreen);
						pleinEcran = not pleinEcran;
					}
				}
				else if (evenement.key.code == sf::Keyboard::S) {
					sauvegarder("sauvegarde1");
				}
			} 
			if (evenement.type == sf::Event::KeyReleased) {
				if (evenement.key.code == sf::Keyboard::Escape) toucheEchapPressee = false;
			}
			if (evenement.type == sf::Event::TextEntered) evenementTexte = &evenement;
		}
		sf::Vector2i souris = sf::Mouse::getPosition(fenetre);
		bool clic = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		progressionEtatsClic(clicFenetre, clic, true);
		
		if (modeJeu == "menu") {
			fenetre.clear(sf::Color(150, 50, 0));
			boutonNouvellePartie->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 - 300));
			boutonChargerPartie->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 - 150));
			boutonCredits->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2));
			boutonAide->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 + 150));
			boutonQuitter->afficher(&fenetre, sf::Vector2f(largeurFenetre / 2, hauteurFenetre / 2 + 300));
			if (boutonNouvellePartie->interactionSouris(souris, clic)) {
				preparerScenes(true);
				chargerScene(getScene("depart"));				
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
				return 0;
			}
			texte.setFillColor(sf::Color::White);
			texte.setPosition(sf::Vector2f(10, hauteurFenetre-35));
			texte.setCharacterSize(20);
			texte.setString("Version : "+numeroVersion);
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
				texte.setString("Code : Loïc Berthelot");
				fenetre.draw(texte);
				texte.setCharacterSize(28);
				texte.setPosition(sf::Vector2f(80, 180));
				std::string contenuTexte = "";
				std::vector<std::string> lignes = lireFichier("ressources/credits.txt");
				for (int i = 0; i < lignes.size(); i++) contenuTexte += lignes[i]+"\n";
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
			boutonSon->afficher(&fenetre, sf::Vector2f(0, 0));
			if (boutonSon->interactionSouris(souris, clic)) {
				if (boutonSon->getType() == "sonOn") {
					boutonSon->changerType("sonOff");
					musique.setVolume(0);
				}
				else {
					boutonSon->changerType("sonOn");
					musique.setVolume(100);
				}
			}
			carte->afficher(&fenetre);
		}
		fenetre.display();
	}
	return 0;
}