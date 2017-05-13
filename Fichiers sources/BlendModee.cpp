#include "..\Fichiers header\BlendModee.h"


BlendModee::BlendModee(std::map<char*, sf::Vector2u*,char_cmp>* dicoConstr, std::map<char*, PersonnageYoan*, char_cmp>* dicoConstrIJ){
	this->dico = dicoConstr;
	this->dicoPersonnagesIJ = dicoConstrIJ;
}
BlendModee::BlendModee() {
}
BlendModee::~BlendModee()
{
}
