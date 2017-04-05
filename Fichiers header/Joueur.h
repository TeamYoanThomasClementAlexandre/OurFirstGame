#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "..\\Fichiers header\Personnage.h"
class Joueur
{
public:
	Joueur();
	string pseudo;
	Personnage* p;
	Personnage* p_placer;
	int personnage_placer;
	~Joueur();
};

#endif