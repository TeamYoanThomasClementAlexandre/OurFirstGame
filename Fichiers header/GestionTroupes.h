#pragma once
#include <SFML/Graphics.hpp>
#include "Inventaire.h"
#include "Carac.h"
#include "CaseEquip.h"
#include "BarreExp.h"
#include "CaracEquip.h"
#include <iostream>

#ifndef GESTIONTROUPES_H
#define GESTIONTROUPES_H

class GestionTroupes {

public:	
	GestionTroupes(float width, float height);
	~GestionTroupes();
	void draw(sf::RenderWindow &fen);
	void onMouse(float x, float y);
	void setSelected(float x, float y);
	void setCarac(int** carac);
	void setEquipement(std::vector<std::vector<std::vector<std::string>>>* equipPerso);
	void GestionTroupes::updateItems(int choixClasse);
	Inventaire** getInventaire();

private:
	sf::Sprite choix[4];	
	sf::Sprite persoChoix;	
	sf::Sprite logo;
	sf::Texture textLogo;
	sf::Texture textureChoix[8];
	sf::Texture texturePerso;
	int choixSelected;
	Inventaire *inventaire;
	Carac *caracteristique;
	int** carac;
	CaseEquip *equip[3];
	BarreExp *exp;
	CaracEquip* viewCarac;
	bool affichageView;
	std::vector<std::vector<std::vector<std::string>>>* equipPerso;	
};


#endif  
