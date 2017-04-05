#include "..\Fichiers header\BlendModee.h"


BlendModee::BlendModee(std::map<char*, sf::Vector2u*,char_cmp>* dicoConstr){
	this->dico = dicoConstr;
}
BlendModee::BlendModee() {
}
BlendModee::~BlendModee()
{
}
