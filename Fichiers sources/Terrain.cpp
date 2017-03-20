#include <string>   // pour std::string 
#include "..\Fichiers header\Terrain.h"

	// représente le malus ou le bonus ajouter au unité

	//int pdv; // point de vie
	//int pa; // point d'attaque
	//int pd; // point de déplacement
	//int portée; // d'ou attaqué
	//int agilité; // taux d'esquive

	
	
	

Terrain::Terrain(std::string s)
{
	this->types = s;
}
		/*Terrain::Terrain(const char* s)
		{
			this->types = s;
		}*/

std::string Terrain::getRealString(char c) {
	switch (c)
	{
	case 'p': { //plaine
		return "plaine";
	}
	case 'm': //montagne
	{
		return "montagne";
	}
	case 'e': //eau
	{
		return "eau";
	}
	case 'c': //chemin
	{
		return "chemin";
	}
	case 'd': //desert
	{
		return "desert";
	}
	case 'f': //foret
	{
		return "foret";
	}
	}
	return "";
}
	Terrain::~Terrain()
	{
	}
