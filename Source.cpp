#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scene.hpp"
#include "Fleche.hpp"
#include "Ramassable.hpp"
#include "Inventaire.hpp"
#include "Decor.hpp"
#include "Quete.hpp"

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
	if (_scene != scene or progression->comporteNouveautes()) {
		scene = _scene;
		progression->setNouveautes(false);

		image.loadFromFile("ressources/images/scenes/"+scene->getNom()+".png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sf::Vector2f taille = sf::Vector2f(texture.getSize().x, texture.getSize().y);
		echelle = sf::Vector2f((largeurFenetre-largeurInventaire)/taille.x, hauteurFenetre/taille.y);
		sprite.setScale(echelle.x, echelle.y);	
	}
}

void initialisation() {
	musique.openFromFile("ressources/sounds/swan_lake.ogg");
	musique.play();
	musique.setLoop(true);

	progression = new Progression();
	largeurInventaire = 250;
	fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor", sf::Style::Fullscreen);
	inventaire = new Inventaire(sf::Vector2f(largeurInventaire, hauteurFenetre));

	boutonSon = new Bouton("son", "sonOn", sf::Vector2f(30, 30));

	Scene* depart = new Scene("depart");
	Scene* scene1 = new Scene("maison");
	Scene* scene2 = new Scene("ponton");
	Scene* scene3 = new Scene("herbe");
	
	chargerScene(depart);
	clicFenetre = 0;
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
	}
	return 0;
}