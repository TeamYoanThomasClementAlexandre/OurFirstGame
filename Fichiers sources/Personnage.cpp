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

	this->vie = tableauCarac[1];

	this->mouvement = tableauCarac[2];

	this->armure = tableauCarac[3];

}
int Personnage::getMouvement(){
	return this->mouvement;
}
int Personnage::getArmure() {
	//interactionBDD->getEquipement("dragodia");
	return this->armure;
}
int Personnage::getDegat() {
	return this->degat;
}
int Personnage::getVie() {
	return this->vie;
}