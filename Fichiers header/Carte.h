#ifndef __CARTE_H__
#define __CARTE_H__

#include "Case.h"

class Carte
{	
public:
	Carte();
	sf::Vector2u getCasebyCoord(int x, int y,int max_x,int max_y,int dimx,int dimy);
	~Carte();

	Case*** caseJeu;

	void getCasesForDeplacement(sf::Vector2u* vec,sf::Vector2u caseDepart,int mobi);
};

#endif
