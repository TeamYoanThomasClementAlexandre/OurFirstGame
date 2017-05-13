#include "..\\Fichiers header\PersonnageYoan.h"
PersonnageYoan::PersonnageYoan(std::string typeConstr){
	this->type = typeConstr;

	char* s = new char[10];
	memset(s, 0, 10);
	sprintf_s(s, 10, "%00d%00d%00d\0", 0, 0, 0);
	this->position.x = -1;
	this->position.y = -1;
	this->id = s;
	this->vitesse_dattaque = 1;
	if (type == "constr") {
		this->degat = -1;
		this->armure = -1;
		this->deplacement = -1;
		this->deplacementRestante = this->deplacement;
		this->range = -1;
		this->vie = -1;
		this->vieRestante = -1;

	}

	if (type == "Archer") {
		this->degat = 40;
		this->armure = 0;
		this->deplacement = 2;
		this->deplacementRestante = this->deplacement;
		this->range = 3;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
	if (type == "Paladin") {
		this->degat = 40;
		this->armure = 20;
		this->deplacement = 4;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 100;
		this->vieRestante = this->vie;

	}
	if (type == "Epeiste") {
		this->degat = 50;
		this->armure = 20;
		this->deplacement = 2;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
	if (type == "Lancier") {
		this->degat = 40;
		this->armure = 20;
		this->deplacement = 3;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
}
std::string PersonnageYoan::afficher() {
	std::string s = this->type +
		"        " + std::to_string(this->vieRestante) + "/" + std::to_string(this->vie) +
		"    " + std::to_string(this->deplacementRestante) + "/" + std::to_string(this->deplacement) +
		"  " + std::to_string(this->degat) +
		"   " + std::to_string(this->armure) +
		"         " + std::to_string(this->range);

	return s;
}
PersonnageYoan::PersonnageYoan() {

}
void PersonnageYoan::setCarac(){
}
