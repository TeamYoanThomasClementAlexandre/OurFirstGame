#include <string>   // pour std::string 
#include "..\Fichiers header\Terrain.h"

	// repr�sente le malus ou le bonus ajouter au unit�

	//int pdv; // point de vie
	//int pa; // point d'attaque
	//int pd; // point de d�placement
	//int port�e; // d'ou attaqu�
	//int agilit�; // taux d'esquive

	
	
	

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
