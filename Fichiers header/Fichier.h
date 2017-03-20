#ifndef __FICHIER_H__
#define __FICHIER_H__

#include <string>
#define MAXI 16
#define MAXJ 34

class Fichier
{
	char Terrain[100]; //contient les 100 caractètes pour chaque case

public:
	Fichier();
	~Fichier();

	int read(std::string s, std::string texture[MAXJ][MAXI]);
};

#endif
