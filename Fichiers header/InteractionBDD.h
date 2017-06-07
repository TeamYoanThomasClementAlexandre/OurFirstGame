#ifndef __INTERACTIONBDD_H__
#define __INTERACTIONBDD_H__

#include <winsock.h>
#include<vector>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string>

//pour le rand
#include <cstdlib>
#include <time.h>
using namespace std;


class InteractionBDD
{
private:
	InteractionBDD();
	~InteractionBDD();
	MYSQL mysql;
	static InteractionBDD *bdd;
	
public:
	

	static InteractionBDD* Ini();
	int requeteParCol(string joueur,string nomTable,string nomCol,string classe);
	int* getCarac(string joueur, string classe);
	vector<vector<string>> getEquipement(string joueur);
	vector<vector <string>> InteractionBDD::getEquipementEquiped(string joueur, string classe);
	bool exist(string joueur2);
	string getUrl(string joueur, string classe);
	void setEquipementOnChar(string nomEquipement, string typeEquipement, string joueur, string classe);
	void setXP(int nombre, string joueur, string classe);
	string* dropEquipement(string joueur);
};

#endif

