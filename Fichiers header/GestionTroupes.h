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
	bool onMouse(float x, float y);
	int setSelected(float x, float y);
	void setCarac(int** carac);
	void setEquipement(std::vector<std::vector<std::vector<std::string>>>* equipPerso);
	void setEquipementSelected(CaseEquip* equipement);
	void GestionTroupes::updateItems();
	void delEquipementSelected();
	Inventaire** getInventaire();
	void setLvlClasses(int* lvl);
	void setExpClasses(int* exp);
	std::string** GestionTroupes::getSaveTab();

private:
	sf::Sprite choix[4];	
	sf::Sprite persoChoix;	
	sf::Sprite logo;
	sf::Sprite back;
	sf::Texture textureBack[2];
	sf::Texture textLogo;
	sf::Texture textureChoix[8];
	sf::Texture texturePerso;
	int lvlClasse[4];
	int expClasse[4];
	int choixSelected;
	Inventaire *inventaire;
	Carac *caracteristique;
	int** carac;
	CaseEquip *equip[3];
	BarreExp *exp;
	CaracEquip* viewCarac;
	bool affichageView;
	int caseOnMouse;
	std::string** saveTab;
	std::vector<std::vector<std::vector<std::string>>>* equipPerso;	
};


#endif  
