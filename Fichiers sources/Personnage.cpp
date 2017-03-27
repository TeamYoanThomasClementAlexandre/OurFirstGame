#include "..\\Fichiers header\Personnage.h"
Personnage::Personnage(std::string typeConstr){
	this->type = typeConstr;
	if (type == "archer") {
		this->degat = 40;
		this->armure = 0;
		this->deplacement = 2;
		this->deplacementRestante = this->deplacement;
		this->range = 3;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
	if (type == "paladin") {
		this->degat = 40;
		this->armure = 20;
		this->deplacement = 4;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 100;
		this->vieRestante = this->vie;

	}
	if (type == "epeiste") {
		this->degat = 50;
		this->armure = 20;
		this->deplacement = 2;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
	if (type == "lancier") {
		this->degat = 40;
		this->armure = 20;
		this->deplacement = 3;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
}
Personnage::Personnage() {

}
void Personnage::setCarac(){
}
