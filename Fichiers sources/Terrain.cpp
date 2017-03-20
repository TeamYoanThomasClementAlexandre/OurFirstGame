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
