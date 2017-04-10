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


	Terrain::~Terrain()
	{
	}
