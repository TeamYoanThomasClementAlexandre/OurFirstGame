#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "..\\Fichiers header\Personnage.h"
class Joueur
{
public:
	Joueur(); // Constructeur 
	string pseudo;  // rien � en dire
	Personnage* p; // personnage de bases du joueur
	Personnage* p_placer; // liste des perso positionner (choisies)
	int personnage_placer; // combien de perso plac�
	int selected; // quelle perso est selectionn� par le Joueur
	~Joueur(); // Destructeur 
};

#endif