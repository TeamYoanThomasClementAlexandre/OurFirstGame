#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GestionTroupes.h"
#include "Inventaire.h"
#include "InteractionBDD.h"


#ifndef CONTROLSOURIS_H
#define CONTROLSOURIS_H


class ControlSouris {
public:
	ControlSouris();
	int gererChoix(GestionTroupes *troupes,sf::RenderWindow &fen, sf::Event evenement,string joueur);
	void gererInventaire(Inventaire *inventaire, GestionTroupes *troupes, sf::RenderWindow &fen, sf::Event evenement);
	~ControlSouris();
};

#endif  