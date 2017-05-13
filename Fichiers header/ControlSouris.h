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
	void gererChoix(GestionTroupes *troupes,sf::RenderWindow &fen);
	void gererInventaire(Inventaire *inventaire, sf::RenderWindow &fen);
	~ControlSouris();
};

#endif  