#pragma once
#include <SFML/Graphics.hpp>
#include "..//Fichiers header/CaseEquip.h"
#include "CaracEquip.h"
#include <iostream>

#ifndef INVENTAIRE_H
#define INVENTAIRE_H


class Inventaire {

public:	
	Inventaire(float ratioX, float ratioY);
	void draw(sf::RenderWindow &fen);
	void onMouse(float x,float y);
	void update(int classe);
	void setItems(std::vector<std::vector<std::string>> itemInvent);
	void setPosition(float x, float y);
	~Inventaire();
	static const int Largeur = 13;
	static const int Hauteur = 5;	

private:
	sf::VertexArray inventaire;
	float ratioX;
	float ratioY;
	CaseEquip* cases[Largeur][Hauteur];
	CaracEquip* viewCarac;
	bool viewC;
	std::vector<std::vector<std::string>> itemInvent;
};


#endif  
