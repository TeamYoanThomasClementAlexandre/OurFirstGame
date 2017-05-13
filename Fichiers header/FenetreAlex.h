#pragma once
#include <SFML/Graphics.hpp>
#include "GestionTroupes.h"
#include "ControlSouris.h"
#include "Inventaire.h"

#ifndef FENETREALEX_H
#define FENETREALEX_H
#define WIDTH 1920.f	
#define HEIGHT 1080.f

class FenetreAlex : public sf::RenderWindow {
	public:
		void game();
		void gestionTroupes();		
		FenetreAlex(int** carac,vector<vector<vector<string>>>* equipPerso, vector<vector<string>> itemInvent);
		~FenetreAlex();

	private:
		GestionTroupes *troupes;
		ControlSouris *control;
		int** carac;
};
	
#endif  
