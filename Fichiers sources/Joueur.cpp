#include "..\Fichiers header\Joueur.h"

Joueur::Joueur(std::string login0) {
	this->login = login0;
	this->tabPersonnage.push_back(Personnage("dragodia", "Archer"));
	this->tabPersonnage.push_back(Personnage("dragodia", "Lancier"));
	this->tabPersonnage.push_back(Personnage("dragodia", "Archer"));
	this->tabPersonnage.push_back(Personnage("dragodia", "Archer"));
	tabPersonnage[0].getArmure();
}
Joueur::~Joueur() {

}