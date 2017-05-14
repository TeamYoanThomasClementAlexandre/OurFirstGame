#include "..\Fichiers header\Combat.h"



Combat::Combat()
{
}


Combat::~Combat()
{
}

void Combat::simulationCombat(PersonnageYoan* attaquant, PersonnageYoan* victime) {
	if (coupCritique()) {
		victime->vieRestante = victime->vieRestante - attaquant->degat;
		printf("coup critique, il ignore la defense HUHEUE");
	}
	else
		victime->vieRestante=victime->vieRestante-(attaquant->degat- attaquant->armure);
		printf(" la vie du personnage attaqué est de %d", victime->vieRestante);
		
}
bool Combat::coupCritique() {
	int echec = 0;
	echec = rand() % 50+1;
	printf("%d\n", echec);
	if(echec==50)// il crit like a boss
		return true;
	else
		return false;
}