#include <SFML/Graphics.hpp>
#include <iostream>
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
Quete* quete;
bool toucheEchapPressee = false;
bool pleinEcran = true;
int largeurInventaire;
Progression* progression;
std::vector<Scene*> scenes;

Scene* getScene(std::string nom) {
	for (int i = 0; i < scenes.size(); i++) {
		if (scenes[i]->getNom() == nom) return scenes[i];
	}
}

void chargerScene(Scene* _scene) {
	if (_scene != scene or progression->comporteNouveautes()) {
		scene = _scene;
		if (scene->getNom() == "scene2") {
			if (progression->cleeActive("fantome")) {
				scene->ajouterFleche(new Fleche(getScene("scene3"), sf::Vector2f(100, 250), -40));
				scene->retirerDecor("fantome");
				progression->utiliserClee("fantome");
			}
		} 
		progression->setNouveautes(false);

		image.loadFromFile("images/scenes/"+scene->getNom()+".png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sf::Vector2f taille = sf::Vector2f(texture.getSize().x, texture.getSize().y);
		echelle = sf::Vector2f((largeurFenetre-largeurInventaire)/taille.x, hauteurFenetre/taille.y);
		sprite.setScale(echelle.x, echelle.y);	
	}
}

void initialisation() {
	progression = new Progression();
	largeurInventaire = 250;
	fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor", sf::Style::Fullscreen);

	std::vector<Fleche*> fleches;

	Scene* scene1 = new Scene("scene1");
	Scene* scene2 = new Scene("scene2");
	Scene* scene3 = new Scene("scene3");
	Scene* scene4 = new Scene("scene4");
	scene1->ajouterFleche(new Fleche(scene2, sf::Vector2f(550, 400), 20));
	scene1->ajouterFleche(new Fleche(scene3, sf::Vector2f(100, 400), -50));
	scene2->ajouterFleche(new Fleche(scene1, sf::Vector2f(420, 420), 180, 1.5));
	scene3->ajouterFleche(new Fleche(scene1, sf::Vector2f(400, 500), 140));
	scene3->ajouterFleche(new Fleche(scene4, sf::Vector2f(600, 400), 0, 1, "loupe"));
	scene4->ajouterFleche(new Fleche(scene3, sf::Vector2f(50, 50), 0, 2, "croix1"));
	scene4->ajouterRamassable(new Ramassable("baton", sf::Vector2f(400, 400)));
	scene2->ajouterDecor(new Decor("fantome", sf::Vector2f(200, 400), sf::Vector2f(largeurFenetre, hauteurFenetre)));
	chargerScene(scene1);

	inventaire = new Inventaire(sf::Vector2f(largeurInventaire, hauteurFenetre));
}

int main() { 
	initialisation();
	
	fenetre.setPosition(sf::Vector2i(0, 0));
	fenetre.setFramerateLimit(60);
	sf::Event event;
	while (true) {
		while (fenetre.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				fenetre.close();
				return 0;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					if (not toucheEchapPressee) {
						toucheEchapPressee = true;
						if (pleinEcran) fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor");
						else fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Chasse au Trésor", sf::Style::Fullscreen);
						pleinEcran = not pleinEcran;
					}
				}
			} 
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape) toucheEchapPressee = false;
			}
		}
		sf::Vector2i souris = sf::Mouse::getPosition(fenetre);
		bool clic = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		fenetre.draw(sprite);
		Scene* _scene = scene->interactionContenu(souris, clic, inventaire);
		chargerScene(_scene);
		scene->afficherContenu(&fenetre, echelle);
		inventaire->afficher(&fenetre, sf::Vector2f(largeurFenetre - largeurInventaire, 0));
		fenetre.display();
		fenetre.clear();
	}
	return 0;
}