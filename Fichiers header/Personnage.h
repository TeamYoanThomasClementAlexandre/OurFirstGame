#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__
#include "..\Fichiers header\InteractionBDD.h"

class Personnage
{
private:
	int vie;
	int degat;
	int mouvement;
	int armure;

	string nomJoueur;
	string typePersonnage;

	InteractionBDD* interactionBDD;
	void Personnage::InitialisationCarac();

public:
	Personnage(string nomJoueur0,string typePersonnage0);
	int Personnage::getMouvement();
	int Personnage::getVie();
	int Personnage::getDegat();
	int Personnage::getArmure();
};







#endif
