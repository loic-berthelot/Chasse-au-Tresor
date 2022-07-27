#pragma once
#include "Ramassable.hpp"

class Monnaie : public Ramassable{
public:
	Monnaie(std::string _nom, sf::Vector2f _position = sf::Vector2f(0, 0), int angle = 0, float _coefTaille = 1) : Ramassable( _nom, _position, angle, _coefTaille) {
	}
	bool estMonnaie();
};