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
int largeurInventaire;
Progression* progression;
std::vector<Scene*> scenes;
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

void preparerMenu() {
	modeJeu = "menu";
}

void chargerScene(Scene* _scene) {
	if (_scene != scene) {
		scene = _scene;
		image.loadFromFile("ressources/images/scenes/"+scene->getNom()+".png");
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

	boutonSon = new Bouton("son", "sonOn", sf::Vector2f(30, 30));
	boutonNouvellePartie = new Bouton("menu_nouvelle_partie", "menu_nouvelle_partie", sf::Vector2f(0, 0));
	boutonChargerPartie = new Bouton("menu_charger_partie", "menu_charger_partie", sf::Vector2f(0, 0));
	boutonCredits = new Bouton("menu_credits", "menu_credits", sf::Vector2f(0, 0));
	boutonAide = new Bouton("menu_aide", "menu_aide", sf::Vector2f(0, 0));
	boutonQuitter = new Bouton("menu_quitter", "menu_quitter", sf::Vector2f(0, 0));
	boutonRetourMenu = new Bouton("retour_menu", "retour_menu", sf::Vector2f(0, 0));

	std::string nom;
	for (const auto& file : std::filesystem::directory_iterator("./ressources/scenes")) {
		nom = file.path().string();
		nom = nom.substr(20, nom.size() - 24);
		new Scene(nom);
	}
	carte = new Carte();
	clicFenetre = 0;
	preparerMenu();
}

void sauvegarder(std::string fichier) {
	std::ofstream flux("sauvegardes/"+fichier+".txt");
	flux << inventaire->taillePlaces() << std::endl;
	for (int i = 0; i < inventaire->taillePlaces(); i++) flux << inventaire->nomRamassable(i) << std::endl;
	flux << progression->tailleClees() << std::endl;
	for (int i = 0; i < progression->tailleClees(); i++) flux << progression->nomClee(i) << std::endl;
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
				chargerScene(getScene("depart"));
				modeJeu = "jeu";
			}
			if (boutonChargerPartie->interactionSouris(souris, clic)) {
				chargerScene(getScene("depart"));
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
		}
		else if (modeJeu == "credits" or modeJeu == "aide") {
			fenetre.clear(sf::Color(150, 50, 0));
			boutonRetourMenu->afficher(&fenetre, sf::Vector2f(50, 50));
			if (boutonRetourMenu->interactionSouris(souris, clic)) modeJeu = "menu";
			if (modeJeu == "credits") {

			}
			else {

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
			sauvegarder("sauvegarde1");
		}
		fenetre.display();
	}
	return 0;
}