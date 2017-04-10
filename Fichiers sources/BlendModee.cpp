#include "..\Fichiers header\BlendModee.h"


BlendModee::BlendModee(std::map<char*, sf::Vector2u*,char_cmp>* dicoConstr, std::map<char*, sf::Vector2u*, char_cmp>* dicoConstrIJ, std::map<char*, sf::Vector2u*, char_cmp>* dicoConstrXY){
	this->dico = dicoConstr;
	this->dicoPersonnagesIJ = dicoConstrIJ;
	this->dicoPersonnagesXY = dicoConstrXY;
}
BlendModee::BlendModee() {
}
BlendModee::~BlendModee()
{
}
