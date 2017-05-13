#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef CARACEQUIP_H
#define CARACEQUIP_H

class CaracEquip : public sf::RectangleShape {

public:	
	CaracEquip(float width,float height);
	void draw(sf::RenderWindow &fen);
	~CaracEquip();
	static CaracEquip* ini(float width,float height);
	void setAttributs(std::string* carac);
	

private:
	sf::Text description[5];
	sf::Text attributs[6];
	sf::Font police;
	static CaracEquip *view;
	int tailleAttributs;
};


#endif  
