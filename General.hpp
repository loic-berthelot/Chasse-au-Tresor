#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

float norme(sf::Vector2f v);

float distance(sf::Vector2f v1, sf::Vector2f v2);
float distance(sf::Vector2f v1, sf::Vector2i v2);

bool pointDansRectangle(sf::Vector2f point, sf::FloatRect rectangle);