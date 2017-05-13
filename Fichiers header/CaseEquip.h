#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef CASEEQUIP_H
#define CASEEQUIP_H

class CaseEquip : public sf::RectangleShape {

public:	
	CaseEquip(float width,float height,float posX, float posY);
	void draw(sf::RenderWindow &fen);
	void setEquipement(std::string url, std::string* carac);
	std::string* getCarac();
	void clean();
	~CaseEquip();	

private:
	sf::Texture image;
	sf::Sprite equipement;
	std::string caracEquip[6];
	bool cleanbool;
};


#endif  
