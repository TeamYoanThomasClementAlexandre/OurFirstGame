#ifndef __JOUEURYOAN_H__
#define __JOUEURYOAN_H__

#include "..\\Fichiers header\PersonnageYoan.h"
class JoueurYoan
{
public:
	JoueurYoan(); // Constructeur 
	string pseudo;  // rien � en dire
	PersonnageYoan* p; // personnage de bases du joueur
	PersonnageYoan* p_placer; // liste des perso positionner (choisies)
	int personnage_placer; // combien de perso plac�
	int selected; // quelle perso est selectionn� par le Joueur
	~JoueurYoan(); // Destructeur 
};

#endif