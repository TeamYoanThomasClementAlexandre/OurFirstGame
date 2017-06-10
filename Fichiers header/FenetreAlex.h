#pragma once
#include <SFML/Graphics.hpp>
#include "GestionTroupes.h"
#include "ControlSouris.h"
#include "Inventaire.h"

#ifndef FENETREALEX_H
#define FENETREALEX_H

class FenetreAlex : public sf::RenderWindow {
	public:
		void game();
		FenetreAlex(int** carac,vector<vector<vector<string>>>* equipPerso, vector<vector<string>> itemInvent,int lvlClasse[4],int expClasse[4],float width,float height,string joueur);
		~FenetreAlex();

	private:
		string joueur;
		GestionTroupes *troupes;
		ControlSouris *control;
		int** carac;
};
	
#endif  
