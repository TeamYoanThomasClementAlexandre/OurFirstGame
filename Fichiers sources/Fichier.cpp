#include "..\Fichiers header\Fichier.h"
#include "..\Fichiers header\Terrain.h"
#include <iostream>
#include <fstream>

#define MAXI 16
#define MAXJ 34

Fichier::Fichier()
{
}

Fichier::~Fichier()
{
}

int Fichier::read(std::string fichier_name,std::string texture[MAXJ][MAXI]) {

	std::string contenu; 
	std::ifstream fichier(fichier_name, std::ios::in);  // on ouvre le fichier en lecture
	int i = 0;
	int j = 0;

	// si l'ouverture a réussi
	if (fichier)  
	{
		// déclaration d'une chaîne qui contiendra la ligne lue
		std::string ligne; // Une variable pour stocker les lignes lues

		while (j < MAXJ) //Tant qu'on n'est pas à la fin, on lit
		{
			getline(fichier, ligne);
			for (i = 0; i< MAXI; i++) {
				texture[j][i] = Terrain::getRealString(ligne[i]);
			}
			j++;
		}

		fichier.close();  // on ferme le fichier
		return 0;
	}
	else {
		// sinon
		std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
	}

	return -1;
}
