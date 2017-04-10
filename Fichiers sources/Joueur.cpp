#include "..\Fichiers header\Joueur.h"


Joueur::Joueur()
{
	this->personnage_placer = 0;
	Personnage* p= new Personnage[4];
	this->p_placer = p;

	this->selected = -1;
}


Joueur::~Joueur()
{
}