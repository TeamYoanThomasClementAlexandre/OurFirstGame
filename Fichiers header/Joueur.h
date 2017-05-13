#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include <string>
#include<vector>
#include"Personnage.h"

class Joueur
{
private:
	std::string login;
	

public:
	std::vector<Personnage>tabPersonnage;
	Joueur(std::string login0);
	~Joueur();
};







#endif