#include "..\\Fichiers header\Personnage.h"


Personnage::Personnage(string nomJoueur0,string typePersonnage0){
	this->interactionBDD= InteractionBDD::Ini();
	this->nomJoueur = nomJoueur0;
	this->typePersonnage = typePersonnage0;
	this->InitialisationCarac();
}

void Personnage::InitialisationCarac() { 
	int i;
	int *tableauCarac =interactionBDD->getCarac(nomJoueur, typePersonnage);
	
	this->degat = tableauCarac[0];
	printf("mes dommages sont de %d\n",this->degat );

	this->vie = tableauCarac[1];
	printf("mes vies sont de %d\n", this->vie);

	this->mouvement = tableauCarac[2];
	printf("mes mouvements sont de %d\n", this->mouvement);

	this->armure = tableauCarac[3];
	printf("mes armures sont de %d\n", this->armure);

	printf("\n\n");
}
int Personnage::getMouvement(){
	return this->mouvement;
}
int Personnage::getArmure() {
	interactionBDD->getEquipement("dragodia");
	return this->armure;
}
int Personnage::getDegat() {
	return this->degat;
}
int Personnage::getVie() {
	return this->vie;
}