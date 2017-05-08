#ifndef __FICHIER_H__
#define __FICHIER_H__

#include <string>
#define MAXI 11
#define MAXJ 12

class Fichier
{
	char Terrain[100]; //contient les 100 caractètes pour chaque case

public:
	Fichier();
	~Fichier();

	int read(std::string s, std::string texture[MAXJ][MAXI]);
};

#endif
