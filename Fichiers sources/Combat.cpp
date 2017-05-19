#include "..\Fichiers header\Combat.h"



Combat::Combat()
{
}


Combat::~Combat()
{
}

void Combat::simulationCombat(PersonnageYoan* attaquant, PersonnageYoan* victime, Carte c) {
	int* tab_attaquant = new int[3];
	tab_attaquant = attaquant->getNewCaracwithCase(c);
	int* tab_victime = new int[3];
	tab_victime = victime->getNewCaracwithCase(c);

	if (coupCritique()) {
		victime->vieRestante = victime->vieRestante - tab_attaquant[1];
		//printf("coup critique, il ignore la defense HUHEUE");
	}
	else
		victime->vieRestante=victime->vieRestante-(tab_attaquant[1]- tab_victime[0]);
		//printf(" la vie du personnage attaqué est de %d", victime->vieRestante);
		
}
bool Combat::coupCritique() {
	int echec = 0;
	echec = rand() % 50+1;
	//printf("%d\n", echec);
	if(echec==50)// il crit like a boss
		return true;
	else
		return false;
}