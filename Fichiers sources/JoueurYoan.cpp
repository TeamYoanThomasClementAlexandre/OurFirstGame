#include "..\Fichiers header\JoueurYoan.h"


JoueurYoan::JoueurYoan()
{
	this->personnage_placer = 0;
	PersonnageYoan* p= new PersonnageYoan[4];
	this->p_placer = p;

	this->selected = -1;
}


JoueurYoan::~JoueurYoan()
{
}