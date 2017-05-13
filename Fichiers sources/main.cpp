
#include <stdio.h>
#include<stdlib.h>
#include "..\\Fichiers header\Fenetre.h"
#include <iostream>
#include <fstream>


void lecture() {
	std::string login;
	std::ifstream fichier("testFileWriter.txt");
	if (fichier) 
	{
		fichier >> login;
		cout << login;
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}
}

int main()
{
	char commande[100] = "java -cp \"mariadb-client.jar;.\" Main";
	/*std::vector<Personnage>tabPersonnage;
	tabPersonnage.push_back(Personnage("dragodia","Archer"));
	tabPersonnage.push_back(Personnage("dragodia","Lancier"));
	tabPersonnage.push_back(Personnage("dragodia","Archer"));
	tabPersonnage.push_back(Personnage("dragodia","Archer"));

	/* on a cré les 4 personnages du joueur numéro 1 */
	system(commande);
	//Joueur j1 = Joueur("dragodia");
	// lancé le java ici !


	lecture();
	Fenetre test(960, 540,"dragodia");
	
	return 0;
}