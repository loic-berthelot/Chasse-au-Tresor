#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scene.hpp"
#include "Fleche.hpp"
#include "Ramassable.hpp"
#include "Inventaire.hpp"
#include "Decor.hpp"
#include "Quete.hpp"
#include <filesystem>

int largeurFenetre = 1280;
int hauteurFenetre = 1024;
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
int clicFenetre;

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
		else if (scene->getMusique() != "") {
			musique.openFromFile("ressources/sons/"+scene->getMusique());
			musique.play();
		}
	}
}

void initialisation() {
	musique.setLoop(true);
	progression = new Progression();
	largeurInventaire = 250;
	fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor", sf::Style::Fullscreen);
	inventaire = new Inventaire(sf::Vector2f(largeurInventaire, hauteurFenetre));

	boutonSon = new Bouton("son", "sonOn", sf::Vector2f(30, 30));

	std::string nom;
	Scene* depart = nullptr;
	for (const auto& file : std::filesystem::directory_iterator("./ressources/scenes")) {
		nom = file.path().string();
		nom = nom.substr(20, nom.size() - 24);
		if (nom == "depart") depart = new Scene(nom);
		else new Scene(nom);
	}
	chargerScene(depart);
	clicFenetre = 0;
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
		fenetre.draw(sprite);
		Scene* _scene = scene->interactionContenu(souris, clic, inventaire, evenementTexte);
		chargerScene(_scene);
		scene->afficherContenu(&fenetre, echelle);
		inventaire->afficher(&fenetre, sf::Vector2f(largeurFenetre - largeurInventaire, 0));
		boutonSon->afficher(&fenetre, sf::Vector2f(0,0));
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
		fenetre.display();
		fenetre.clear();
		sauvegarder("sauvegarde1");
	}
	return 0;
}