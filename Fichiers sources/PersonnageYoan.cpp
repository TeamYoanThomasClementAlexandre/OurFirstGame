#include "..\\Fichiers header\PersonnageYoan.h"
#include "..\\Fichiers header\Personnage.h"
PersonnageYoan::PersonnageYoan(std::string typeConstr,Personnage tested){
	this->type = typeConstr;

	char* s = new char[10];
	memset(s, 0, 10);
	sprintf_s(s, 10, "%00d%00d%00d\0", 0, 0, 0);
	this->position.x = -1;
	this->position.y = -1;
	this->id = s;
	this->vitesse_dattaque = 1;
	this->isdead = false;
	this->level = -1;
	this->nbr_tue = 0 ;



	this->degat = tested.getDegat();
	this->armure = tested.getArmure();
	this->deplacement = tested.getMouvement();
	this->deplacementRestante = this->deplacement;
	if (type == "Archer") {
		this->range = 3;
	}else {
		this->range = 1;
	}
	this->vie = tested.getVie();
	this->vieRestante = this->vie;

	
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

int* PersonnageYoan::getNewCaracwithCase(Carte c) {
	int* tab = new int[3];
	if (this->isdead) {
		tab[0] = -1;
		tab[1] = -1;
		tab[2] = -1;
		return tab;
	}
	Case* casee=c.caseJeu[this->position.y][this->position.x];

	
	tab[0] = this->armure + casee->armure;
	tab[1] = this->degat + casee->degat;
	tab[2] = this->range;

	string typ = this->type;
	string typ2 = "Archer";
	if (typ == typ2) {
		tab[2] = this->range + casee->range;

	}
	
	return tab;

}
bool* PersonnageYoan::isChangeCarac(Carte c) {
	bool* tabb = new bool[3];

	if (this->isdead) {
		tabb[0] = false;
		tabb[1] = false;
		tabb[2] = false;
		return tabb;
	}
	Case* casee = c.caseJeu[this->position.y][this->position.x];
	int* tab = new int[3];

	tab[0] = this->armure + casee->armure;
	tab[1] = this->degat + casee->degat;
	tab[2] = this->range;

	string typ = this->type;
	string typ2 = "Archer";
	if (typ == typ2) {
		tab[2] = this->range + casee->range;

	}
	bool* b = new bool[3];

	for (int i = 0; i < 3; i++) {
		b[i] = false;
	}
	if (tab[0] != this->armure) {
		b[0] = true;
	}
	if (tab[1] != this->degat) {
		b[1] = true;
	}
	if (tab[2] != this->range) {
		b[2] = true;
	}

	return b;
}

int PersonnageYoan::getExperiencePersonnage(int nbr_tour,bool isWin) {
	int xp_sup = 5; // 10 xp donnée directement   (MAX = 90, MIN = 11)
	if (nbr_tour < 10) { 
		xp_sup+= nbr_tour*2;  // plus il y a de tour plus ya de l'xp
	}
	else {
		xp_sup += 20; // plus de 10 tour = 10 xp
	}
	if (isWin) {
		xp_sup += 10; // victoire = 20 xp
	}
	if (!isdead) {
		xp_sup += 5;
	}
	xp_sup += this->nbr_tue * 5; // chaque kill donne 10 xp 

	return xp_sup;

}

void PersonnageYoan::setCarac(){
}
