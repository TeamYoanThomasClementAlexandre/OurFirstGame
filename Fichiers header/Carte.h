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

	void getCasesForDeplacementRecursifNord(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp,int mobi_de_base, int indice);
	void getCasesForDeplacementRecursifSud(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);
	void getCasesForDeplacementRecursifEst(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);
	void getCasesForDeplacementRecursifOuest(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);

	void getCasesForDeplacementRecursifNordOuest(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);
	void getCasesForDeplacementRecursifNordEst(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);
	void getCasesForDeplacementRecursifSudOuest(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);
	void getCasesForDeplacementRecursifSudEst(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice);


	void getCasesForCombatRecursifNord(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);
	void getCasesForCombatRecursifSud(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);
	void getCasesForCombatRecursifEst(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);
	void getCasesForCombatRecursifOuest(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);

	void getCasesForCombatRecursifNordOuest(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);
	void getCasesForCombatRecursifNordEst(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);
	void getCasesForCombatRecursifSudOuest(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);
	void getCasesForCombatRecursifSudEst(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice);


	void getCasesForDeplacement(sf::Vector2u* vec,sf::Vector2u caseDepart,int mobi);
};

#endif
