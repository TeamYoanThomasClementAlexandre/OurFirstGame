#include "..\\Fichiers header\\Case.h"
#include "..\\Fichiers header\\Terrain.h"
#include <SFML/Graphics.hpp>

Case::Case(sf::Sprite s,int cost,int vie,int range,int degat,int armure)
{
	this->sprite = s;
	this->who = -1;
	this->pmCost = cost;
	this->vie = vie;
	this->range = range;
	this->degat = degat;
	this->armure = armure;

}


std::string Case::getRealString(char c) {
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

Case::~Case()
{
}
